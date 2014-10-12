/*
 *    vsieve.c  ( List 9-17 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 9-17  仮想メモリ空間で
 *                       「エラトステネスのふるい」を実行するメインプログラム
 *               [vsieve.c  1/1] (page 330)
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <dos.h>
#include "proto.h"
#include "int.h"
#include "page.h"
#include "vm.h"

#define NUM 100000
#define TBLADR 0x100000
#define TBLSIZE 0x400000
#define PHYSSIZE 0x4000

void VMMapFile(char *);
void VMClose(void);
extern unsigned short csseg32;

void main(int argc, char *argv[])
{
    unsigned long i,m,snum, ptop;
    unsigned short sel;
    char *swapfile;
    void (__far *sieveFunc)();
    int  (__far *isprimeFunc)();
    void sieve(unsigned short sel, unsigned long num);
    int isprime(unsigned short sel, unsigned long num);

    if (argc>1)
        m = atol(argv[1]);
    else
        m = NUM;

    swapfile = getenv("SWAPFILE");
    if (swapfile==NULL)
        swapfile = SWAPFILE;

    SetUpGDT();
    SetUpIDT(0);
    EnableA20();

    sel = AllocSel();
    SetSegDesc(sel, SegToLinier(csseg32, 0),
                                0xffff, TypeCode, Code386, 0);
    sieveFunc = (void (__far *)() )
        (((unsigned long)sel<<16) + (unsigned short) sieve);
    isprimeFunc = (int (__far *)() )
        (((unsigned long)sel<<16) + (unsigned short) isprime);

    SetUpPTE();

    ptop = (unsigned long) (char *) malloc(PHYSSIZE+PAGESIZE);
    if (ptop==0L) {
        fprintf(stderr, "Can't alloc memory\n");
        exit(1);
    }
    ptop = SegToLinier(seg.ds, (unsigned short)ptop+PAGESIZE) & 0xfffff000;
    VMInit(ptop, PHYSSIZE, TBLADR, TBLSIZE);
    VMMapFile(swapfile);

    sel = AllocSel();
    SetSegDesc(sel, TBLADR, (m>>12)+1, TypeData, BigSeg, 0);

    RealToProto_P(0);

    sieveFunc(sel, m);
    snum=0;
    for (i=2;i<=m;i++) {
        if (isprimeFunc(sel,i)) {
            snum++;
            ProtoToReal_P();
            printf("%lu ", i);
            RealToProto_P(0);
        }
    }

    VMClose();
    ProtoToReal_P();

    putchar('\n');
    printf("%lu prime numbers in 2..%lu\n",snum,m);
}

