/*
 *    dpmisiev.c  ( List 12-6 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 12-6  DPMIの機能を使うようにした例題プログラムsieve32
 *               [dpmisiev.c  1/1]  (page 428)
 */

#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include "proto.h"
#include "dpmi.h"

#define NUM 100000

void main(int argc, char *argv[])
{
    unsigned long i,m,snum;
    unsigned long bh, addr;
    unsigned short sel, csel, codesize;
    struct SREGS seg;
    void (__far *sieveFunc)();
    int  (__far *isprimeFunc)();
    void sieve(unsigned short tblsel, unsigned long num);
    int isprime(unsigned short tblsel, unsigned long num);

    if (argc>1)
        m = atol(argv[1]);
    else
        m = NUM;

    segread(&seg);
    codesize=(seg.ds-seg.cs)*16;

    DPMIRealToProto();

    csel = DPMIAllocLDT();
    DPMISetRights(csel, TypeCode+0x60, Code386);
    DPMISetBaseAddr(csel, SegToLinier(seg.cs, 0));
    DPMISetLimit(csel, codesize);
    sieveFunc = (void (__far *)() )
        (((unsigned long)csel<<16) + (unsigned short) sieve);
    isprimeFunc = (int (__far *)() )
        (((unsigned long)csel<<16) + (unsigned short) isprime);

    sel = DPMIAllocLDT();
    bh = DPMIAllocBlock(m+1, &addr);
    DPMISetRights(sel, TypeData+0x60, BigSeg);
    DPMISetBaseAddr(sel, addr);
    DPMISetLimit(sel, m+1);

    sieveFunc(sel, m);
    snum=0;
    for (i=2;i<=m;i++) {
        if (isprimeFunc(sel, i)) {
            snum++;
            printf("%lu ", i);
        }
    }

    putchar('\n');
    printf("%lu prime numbers in 2..%lu\n",snum,m);

    DPMIFreeBlock(bh);
    DPMIFreeLDT(sel);
    DPMIFreeLDT(csel);
    ExitToDos();
}
