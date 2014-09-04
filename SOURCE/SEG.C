/*
 *    seg.c  ( List 5-4, 5-5, 5-8, 5-9, 5-11, 5-14 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 5-4  ディスクリプタテーブルの定義
 *              [seg.c  1/6] (page 150)
 */

#include <stdio.h>
#include <dos.h>
#ifdef __MSC__
#include <malloc.h>
#else
#include <alloc.h>
#endif
#include <process.h>
#include "proto.h"

#define GDTNUM 16
SegDesc         gdt[GDTNUM];
DescTblPtr  gdtptr;
unsigned int    gdtfre=0x30/8+1;
struct SREGS    seg;

/*
 *    List 5-5  引数をセグメントディスクリプタに格納するMakeSegDesc()関数
 *              [seg.c  2/6] (page 151)
 */

void MakeSegDesc(
  SegDesc  *desc,
  unsigned long addr,
  unsigned long limit,
  unsigned char segtype,
  unsigned char seg32type,
  unsigned char dpl)
{
    desc->baseL = (unsigned int) (addr & 0xffff);
    desc->baseM = (unsigned char) ((addr >> 16) & 0xff);
    desc->baseH = (unsigned char) ((addr >> 24) & 0xff);
    desc->limitL = (unsigned int) (limit & 0xffff);
    desc->limitH = (unsigned char) ((limit >> 16) & 0x0f)
                                                  + seg32type;

    desc->type = segtype | (dpl<<5);
}

/*
 *    List 5-8  セグメントディスクリプタをセットするSetSegDesc()関数
 *              [seg.c  3/6] (page 152)
 */

void SetSegDesc(
  unsigned short sel,
  unsigned long addr,
  unsigned long limit,
  unsigned char segtype,
  unsigned char seg32type,
  unsigned char dpl)
{
    MakeSegDesc(&gdt[sel>>3], addr, limit,
                                     segtype, seg32type, dpl);
}

/*
 *    List 5-11  セレクタ値の割り当てを行うAllocSel()関数
 *               [seg.c  4/6] (page 154)
 */

unsigned int AllocSel(void)
{
    if (gdtfre>=GDTNUM) {
        fprintf(stderr, "Can't allocate selector\n");
        exit(1);
    }
    return gdtfre++ * 8;
}

/*
 *    List 5-9  セグメント配置を表すディスクリプタを作成するSetUpGDT()関数
 *              [seg.c  5/6] (page 153)
 */

void SetUpGDT(void)
{
    unsigned short codesize,datasize,stacksize;

    segread(&seg);
    codesize=(seg.ds-seg.cs)*16;
    datasize=0xffff;
    stacksize=0; /*(unsigned short) sbrk(0);*/

    SetSegDesc(0x08, SegToLinier(seg.cs, 0),
                             codesize, TypeCode, SmallSeg, 0);
    SetSegDesc(0x10, SegToLinier(seg.ds, 0),
                             datasize, TypeData, SmallSeg, 0);
    SetSegDesc(0x18, SegToLinier(seg.ss, 0),
                           stacksize, TypeStack, SmallSeg, 0);
    SetSegDesc(0x20, SegToLinier(seg.cs, 0),
                               0xffff, TypeCode, SmallSeg, 0);
    SetSegDesc(0x28, SegToLinier(seg.ds, 0),
                               0xffff, TypeData, SmallSeg, 0);
    SetSegDesc(0x30, 0L, 0xfffff, TypeData, BigSeg, 3);

/*
 *    List 5-14  lgdt()関数の呼び出し
 *               [seg.c  6/6] (page 155)
 */

    gdtptr.limit = GDTNUM*sizeof(SegDesc) -1;
    gdtptr.base  = SegToLinier(seg.ds, (unsigned short) gdt);

    lgdt(&gdtptr);
}
