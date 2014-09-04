/*
 *    testgate.c  ( List 6-6 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 6-6  コールゲート実験用プログラムtestgate
 *              [testgate.c  1/1] (page 217)
 */

#include <stdio.h>
#include <dos.h>
#include "proto.h"
#include "gate.h"
#include "int.h"
#include "task.h"

#define STACKSIZE 2048
unsigned char stack_os[STACKSIZE], stack_app[STACKSIZE];
unsigned short seltss_os, seltss_app;
unsigned short seltaskgate;
TSS tss_os, tss_app;
int m=0;

void (__far *SysCall)(int);

void OSMain(void);
void OS_DispCS(void);
int __far __pascal SysCallEntry(int);

void AppMain(void);
void App_DispCS(void);

void main(void)
{
    unsigned short selcseg, seldseg, selsseg, selgate;

    SetUpGDT();
    SetUpIDT(0);
    InitDisp();

    selcseg = AllocSel();
    SetSegDesc(selcseg, SegToLinier(seg.cs, 0), 0xffff,
        TypeCode, SmallSeg, 3);
    seldseg = AllocSel();
    SetSegDesc(seldseg, SegToLinier(seg.ds, 0), 0xffff,
        TypeData, SmallSeg, 3);
    selsseg = AllocSel();
    SetSegDesc(selsseg, SegToLinier(seg.ss, 0), 0,
        TypeStack, SmallSeg, 3);

    seltss_os = AllocSel();
    SetSegDesc(seltss_os,
               SegToLinier(seg.ds, (unsigned short) &tss_os),
                     (long) sizeof(TSS), TypeTSS, SmallSeg, 0);

    seltss_app = AllocSel();
    SetSegDesc(seltss_app,
               SegToLinier(seg.ds, (unsigned short) &tss_app),
                     (long) sizeof(TSS), TypeTSS, SmallSeg, 3);
    SetTSS( &tss_app, selcseg|3, seldseg,
                  AppMain, 0, stack_app+STACKSIZE,
                          selsseg|3, stack_os+STACKSIZE, 0x18);

    selgate = AllocSel();
    SetGateDesc(selgate, 0x08, (void (*)()) SysCallEntry,
                                           1, TypeCallGate, 3);
    seltaskgate = AllocSel();
    SetGateDesc(seltaskgate, seltss_os, 0,
                                           0, TypeTaskGate, 3);

    SysCall = (void __far *)
                            (((unsigned long)selgate<<16) + 0);

    RealToProto_I(0);
    ltr(seltss_os);

    OSMain();

    ProtoToReal_I();
}

void OSMain()
{
    DispStr(20,m,"calling from OS  (level 0)");
    OS_DispCS();

    SwitchTask(seltss_app);

    DispStr(20,m,"    returned to OS  (level 0) task");
}

void OS_DispCS()
{
    char str[64];
    struct SREGS seg;

    segread(&seg);
    sprintf(str, "cs:%04x", seg.cs);
    DispStr(60, m++, str);
}

int __far __pascal SysCallEntry(int function)
{
    int err = 0;

    switch(function) {
    case 1:
        OS_DispCS();
        break;

    default:
        DispStr(50, m++, "illegal function no.");
        err = -1;
        break;
    }
    return err;
}

void AppMain(void)
{
    DispStr(20,m++,"    starting App (level 3) task");
    DispStr(20,m,"calling from App (level 3)");
    App_DispCS();
    DispStr(20,m,"calling from App (level 3) (gate)");
    SysCall(1);

    SwitchTask(seltaskgate);
}

void App_DispCS(void)
{
    char str[64];
    struct SREGS seg;

    segread(&seg);
    sprintf(str, "cs:%04x", seg.cs);
    DispStr(60, m++, str);
}
