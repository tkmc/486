/*
 *    int.c  ( List 7-6, 7-7, 7-8, 7-9, 7-14 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 7-6  割り込みディスクリプタテーブルの作成
 *              [int.c  1/5] (page 248)
 */

#include <dos.h>
#include <stdio.h>
#include <process.h>
#include "proto.h"
#include "disp.h"
#include "gate.h"
#include "int.h"

IntFunc     *IntHandler;
DescTblPtr  idtptr,ridtptr;
GateDesc    idt[IDTNUM];
void        (*IntHook)(int n, unsigned short cs,
                                             unsigned short ip);
void        IntHookDummy(int n, unsigned short cs, 
                                             unsigned short ip);

void SetIDTGateDesc(int i, unsigned short sel, void (*f)(),
    unsigned short count, unsigned char type, unsigned char dpl)
{
    MakeGate(idt+i, sel, f, count, type, dpl);
}

void SetUpIDT(unsigned char dpl)
{
    int i;
    extern void (*intvec[IDTNUM])();
    void    GPEFault();
    IntFunc IntExit;
    IntFunc RealModeInt;

    for (i=0;i<IDTNUM;i++)
        SetIDTGateDesc(i, 0x08, intvec[i], 0, TypeIntrGate, dpl);

    SetIDTGateDesc(0x0d, 0x08, GPEFault, 0, TypeTrapGate, dpl);

    idtptr.limit = IDTNUM*sizeof(GateDesc);
    idtptr.base  = SegToLinear(seg.ds, (unsigned short) idt);
    ridtptr.limit = 0x3ff;
    ridtptr.base  = 0;

    IntHandler = RealModeInt;
    IntHook    = IntHookDummy;
}

/*
 *    List 7-7  リアルモードで割り込みを再実行するRealModeInt()関数
 *              [int.c  2/5] (page 250)
 */

void    RealModeInt(
  unsigned short di, unsigned short si, unsigned short bp, 
  unsigned short sp, unsigned short bx, unsigned short dx, 
  unsigned short cx, unsigned short ax, unsigned short es, 
  unsigned short ds, unsigned short n, long eip,
  unsigned short cs, unsigned short f1, unsigned eflags
)
{
    union REGS r;

    ProtoToReal_I();
    int86(n,&r,&r);
    RealToProto_I(1);

    (*IntHook)(n, cs, (unsigned short)eip);
}

void IntHookDummy(int n, unsigned short cs, unsigned short ip)
{
}

/* 
 *    List 7-8  割り込みを禁止してプロテクトモードに移行するRealToProto_I()関数
 *              [int.c  3/5] (page 251)
 */

void RealToProto_I(int sw)
{
    DisableInterrupt();
    lidt(&idtptr);
    RealToProto();
    if (sw) EnableInterrupt();
}

/* 
 *    List 7-9  割り込みを禁止してリアルモードに移行するProtoToReal_I()関数
 *              [int.c  4/5] (page 251)
 */

void ProtoToReal_I(void)
{
    DisableInterrupt();
    lidt(&ridtptr);
    ProtoToReal();
    EnableInterrupt();
}

/*
 *    List 7-14  一般保護例外を処理するGPEHandler()関数
 *               [int.c  5/5] (page 256)
 */

void    GPEHandler(
  unsigned short di, unsigned short si, unsigned short bp,
  unsigned short sp, unsigned short bx, unsigned short dx,
  unsigned short cx, unsigned short ax, unsigned short es,
  unsigned short ds, long errcode, long eip,
  unsigned short cs, unsigned short f1, unsigned eflags
)
{
    ProtoToReal_I();
    printf("protection fault!\n");
    printf("error code %08lX\n", errcode);
    printf("cs:%04X eip:%08lX eflags:%04X ds:%04X es:%04X\n", 
                                       cs, eip, eflags, ds, es);
    printf("ax:%04X bx:%04X cx:%04X dx:%04X ", ax, bx, cx, dx);
    printf("si:%04X di:%04X bp:%04X sp:%04X\n", si, di, bp, sp);

    exit(1);
}

