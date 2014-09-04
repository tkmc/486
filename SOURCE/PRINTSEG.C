/*
 *    printseg.c  ( List 5-18 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 5-18  ディスクリプタテーブルの内容を表示する
 *                       PrintSegDesc()関数とPrintGDTSegDesc()関数
 *               [printseg.c  1/1] (page 159)
 */

#include <stdio.h>
#include <dos.h>
#include "proto.h"
#include "printseg.h"

extern SegDesc         gdt[];

void PrintSegDesc(SegDesc  *desc)
{
    unsigned long addr;
    unsigned long limit;
    unsigned int g, b, avl, p, dpl, s, type, a;

    addr  = ((unsigned long)desc->baseH<<24)
               + ((unsigned long)desc->baseM<<16) + desc->baseL;
    limit = ((unsigned long)(desc->limitH & 0xf)<<16)
                                                 + desc->limitL;

    g    = desc->limitH & 0x80;
    b    = desc->limitH & 0x40;
    avl  = desc->limitH & 0x10;
    p    = desc->type   & 0x80;
    dpl  = (desc->type  & 0x60) >> 5;
    s    = desc->type   & 0x10;
    type = (desc->type  & 0x0e) >> 1;
    a    = desc->type   & 0x01;

    printf("Base=%08lX Lim=%05lX", addr, limit);
    printf(g   ? " G"   : "  ");
    printf(b   ? " B"   : "  ");
    printf(avl ? " avl" : "    ");
    printf(p   ? " P"   : "  ");
    printf(" dpl:%d", dpl);
    printf(s   ? " seg" : " sys");
    switch(type) {
    case 0: printf(" RO-Data "); break;
    case 1: printf(" RW-Data "); break;
    case 2: printf(" RO-Stack"); break;
    case 3: printf(" RW-Stack"); break;
    case 4: printf(" EO-Code "); break;
    case 5: printf(" ER-Code "); break;
    case 6: printf(" RO-Conf "); break;
    case 7: printf(" RW-Conf "); break;
    }
    printf(a   ? " A"  : "  ");
    printf("\n");
}

void PrintGDTSegDesc(unsigned short sel)
{
    printf("%04X: ", sel);
    PrintSegDesc(gdt+sel/8);
}

