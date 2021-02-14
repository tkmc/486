/*
 *    sieve32.c  ( List 5-29 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 5-29  sieve32のメインプログラム
 *               [sieve32.c  1/1] (page 186)
 */

#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include "proto.h"

#define NUM 100000
#define TBLADR 0x100000

void __far sieve(unsigned short sel, unsigned long num);
int __far isprime(unsigned short sel, unsigned long num);
extern unsigned short csseg32;

void main(int argc, char *argv[])
{
    unsigned long i,m,snum;
    unsigned short sel;
    void (__far *sieveFunc)();
    int  (__far *isprimeFunc)();

    if (argc>1)
        m = atol(argv[1]);
    else
        m = NUM;

    SetUpGDT();
    EnableA20();

    sel = AllocSel();
    SetSegDesc(sel, SegToLinear(csseg32, 0),
                                0xffff, TypeCode, Code386, 0);
    sieveFunc = (void (__far *)() )
          (((unsigned long)sel<<16) + (unsigned short) sieve);
    isprimeFunc = (int (__far *)() )
        (((unsigned long)sel<<16) + (unsigned short) isprime);

    sel = AllocSel();
    SetSegDesc(sel, TBLADR, (m>>12)+1, TypeData, BigSeg, 0);

    RealToProto();

    sieveFunc(sel, m);
    snum=0;
    for (i=2;i<=m;i++) {
        if (isprimeFunc(sel, i)) {
            snum++;
            ProtoToReal();
            printf("%lu ", i);
            RealToProto();
        }
    }

    ProtoToReal();

    putchar('\n');
    printf("%lu prime numbers in 2..%lu\n",snum,m);
}
