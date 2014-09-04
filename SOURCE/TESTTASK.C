/*
 *    testtask.c  ( List 8-6, 8-7, 8-8 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 8-6  例題プログラムで実行する3つのタスク――task1(),task2(),task3()
 *              [testtask.c  1/3] (page 286)
 */

#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include "proto.h"
#include "disp.h"
#include "task.h"
#include "int.h"

#define MAXTASKNUM 3
#define STACKSIZE 2048

TSS tss[MAXTASKNUM];
unsigned char stack[MAXTASKNUM-1][STACKSIZE];

unsigned int TaskList[3];
unsigned int SwitchCount;
unsigned int ticks=0;
unsigned int CurTask=0;
int testend=0;
void SetUpTSS(void);

void task1(void)
{
    int i=0, j;
    char buf[4];

    for (;;) {
        for (j=0;j<1000;j++) {
            sprintf(buf, "%d", j);
            DispStr(i, 11, buf);
            if (testend>=2)
                return;
        }
        DispStr(i,11,"   ");
        if (++i>70)
            i=0;
    }
}

void task2(void)
{
    int i=0, j;
    char buf[4];

    for (;;) {
        for (j=0;j<1000;j++) {
            sprintf(buf, "%d", j);
            DispStr(i, 12, buf);
        }
        DispStr(i,12,"   ");
        if (++i>70)
            i=0;
    }
}

void task3(void)
{
    int i=0, j;
    char buf[4];

    for (;;) {
        for (j=0;j<1000;j++) {
            sprintf(buf, "%d", j);
            DispStr(i, 13, buf);
        }
        DispStr(i,13,"   ");
        if (++i>70)
            i=0;
    }
}

/*
 *    List 8-7  定期的な割り込みの回数を数え
 *                      タスクを切り替えるTaskSwitchInt()関数
 *              [testtask.c  2/3] (page 288)
 */

void TaskSwitchInt(int n, unsigned short cs, unsigned short ip)
{
    if (n==TIMERVEC) {
        ticks++;
        if (ticks>SwitchCount) {
            ticks=0;
            if (++CurTask>2)
                CurTask = 0;
            SwitchTask(TaskList[CurTask]);
        }
    } else if (n==KEYINTVEC) {
        testend++;
    }
}

/*
 *    List 8-8  タスク切り替えの例題プログラムtesttask
 *              [testtask.c  3/3] (page 288)
 */

void SetUpTSS(void)
{
    void task1(void),task2(void),task3(void);

    TaskList[0] = AllocSel();
    TaskList[1] = AllocSel();
    TaskList[2] = AllocSel();

    SetTSS( tss+1, 0x08, 0x10, task2, FLAG_INT_ENABLE,
                  stack[0] +STACKSIZE, 0x10, NULL, 0);
    SetTSS( tss+2, 0x08, 0x10, task3, FLAG_INT_ENABLE,
                  stack[1] +STACKSIZE, 0x10, NULL, 0);

    SetSegDesc(TaskList[0],
           SegToLinier(seg.ds, (unsigned short) tss),
               (long) sizeof(TSS), TypeTSS, SmallSeg, 0);
    SetSegDesc(TaskList[1],
           SegToLinier(seg.ds, (unsigned short) (tss+1)),
               (long) sizeof(TSS), TypeTSS, SmallSeg, 0);
    SetSegDesc(TaskList[2],
           SegToLinier(seg.ds, (unsigned short) (tss+2)),
               (long) sizeof(TSS), TypeTSS, SmallSeg, 0);
}

void printTSS(int i)
{
    TSS *t;

    t=tss+i;
    printf("TSS(%d)  ",i);
    printf("cs:%04X ds:%04X es:%04X ss:%04X\n",
        t->cs, t->ds, t->es, t->ss);
    printf("        eip:%08lX esp:%08lX eflags:%08lX\n",
        t->eip, t->esp, t->eflags);
    printf("        eax:%08lX ebx:%08lX ecx:%08lX edx:%08lX\n",
        t->eax, t->ebx, t->ecx, t->edx);
}

#ifdef PC98
#ifdef __MSC__
#define _interrupt __interrupt
#define getvect _dos_getvect
#define setvect _dos_setvect
#endif

void ( _interrupt *oldVsync)();

void _interrupt Vsync(void)
{
    outp(0,0x20);
    outp(0x64,0x20);
}

void VsyncInit(void)
{
    int m;

    oldVsync = getvect(0x0a);
    setvect(0x0a, Vsync);

    DisableInterrupt();
    m = inp(2);
    outp(2, m&0xfb);
    EnableInterrupt();
    outp(0x64,1);
}

void VsyncTerm(void)
{
    int m;

    DisableInterrupt();
    m = inp(2);
    outp(2, m|4);
    EnableInterrupt();

    setvect(0x0a, oldVsync);
}
#endif /* PC98 */

void main(int argc, char *argv[])
{
    int i;

    if (argc<2)
        SwitchCount = 0;
    else
        SwitchCount = atoi(argv[1]);

    SetUpGDT();
    SetUpTSS();
    SetUpIDT(0);
    InitDisp();

    IntHandler = RealModeInt;
    IntHook    = TaskSwitchInt;

    for (i=0;i<3;i++)
        printTSS(i);
#ifdef PC98
    VsyncInit();
#endif
    RealToProto_I(1);
    ltr(TaskList[0]);
    task1();
    ProtoToReal_I();

#ifdef PC98
    VsyncTerm();
#endif
    printf("\n\n\n");
    for (i=0;i<3;i++)
        printTSS(i);
    exit(0);
}
