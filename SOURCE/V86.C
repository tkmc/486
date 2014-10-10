/*
 *    v86.c  ( List 11-1 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 11-1  仮想8086モードへ移行するプログラム
 *               [v86.c  1/1] (page 393)
 */

#include <stdio.h>
#include <dos.h>
#ifdef __MSC__
#include <malloc.h>
#else  /* BC */
#include <alloc.h>
#endif
#ifdef __WATCOMC__
#include <stdlib.h>
#endif
#include <memory.h>
#include "proto.h"
#include "int.h"
#include "task.h"
#include "v86.h"

TSS_IO  v86tss;
TSS tss;
unsigned int ProtoTssSel, V86TssSel;

#define STACKSIZE 2048
unsigned char stack[STACKSIZE];

void SetV86(void (*f)())
{
#ifdef __MSC__
	_heapmin();
#endif
    SetTSS( (TSS *)&v86tss, seg.cs, seg.ds, f, 0x23002L,
            (unsigned char *) sbrk(0)+2048, seg.ss,
        stack+STACKSIZE, 0x10);

    v86tss.tss.iobase = v86tss.iomap
                       -(unsigned char *)&v86tss;
    memset(v86tss.iomap, 0, sizeof(v86tss.iomap));
    v86tss.iomap[8192]=0xff;

    ProtoTssSel = AllocSel();
    SetSegDesc(ProtoTssSel,
        SegToLinier(seg.ds, (unsigned short) &tss),
            (long) sizeof(TSS), TypeTSS, SmallSeg, 0);
    V86TssSel = AllocSel();
    SetSegDesc(V86TssSel,
        SegToLinier(seg.ds, (unsigned short) &v86tss),
            (long) sizeof(TSS_IO), TypeTSS, SmallSeg, 0);

    IntHandler = v86int;
}

void RealToV86(void)
{
    RealToProto_I(0);
    ltr(ProtoTssSel);
    SwitchTask(V86TssSel);
}

