/*
 *    page.c  ( List 9-1, 9-3, 9-7, 9-8 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 9-1  PTEを設定する関数群
 *              [page.c  1/4] (page 314)
 */

#include <stdio.h>
#include <malloc.h>
#include <process.h>
#include <dos.h>
#include "proto.h"
#include "page.h"
#include "int.h"

/* must alligned at 4096 bytes boundary */
unsigned long *PageDir;
unsigned long *PageTbl[MAXDIRNUM];

unsigned long *GetPTEAddr(unsigned long viraddr)
{
    int dir;

    dir = viraddr>>22;
    return &PageTbl[dir][(viraddr>>12)&0x3ff];
}

long MakePTE(unsigned long physaddr)
{
    return (physaddr & 0xfffff000)
                             | PTE_RW | PTE_USER | PTE_PRESENT;
}

/*
 *    List 9-3  PTEを初期設定するSetUpPTE()関数
 *              [page.c  2/4] (page 315)
 */

void SetPTE(unsigned long viraddr, unsigned long physaddr)
{
    unsigned long *pte;

    pte = GetPTEAddr(viraddr);
    *pte = MakePTE(physaddr);
}

void SetUpPTE(void)
{
    int i;
    unsigned long p;
    struct SREGS seg;
    unsigned char *ptr;

    ptr = (unsigned char *)malloc((1+MAXDIRNUM+1)*(PAGESIZE));
    if (ptr==NULL) {
        printf("SetUpPTE: Can't alloc memory for PTE\n");
        exit(1);
    }

    segread(&seg);
    p = SegToLinier(seg.ds, (unsigned short)ptr);
    p = (p+0xfff)&0xfffff000;
    ptr = (unsigned char *)(p-SegToLinier(seg.ds,0));

    PageDir = (unsigned long *)ptr;
    ptr+=PAGESIZE;
    for (i=0;i<MAXDIRNUM;i++,ptr+=PAGESIZE)
        PageTbl[i] = (unsigned long *)ptr;

    for (i=0;i<MAXDIRNUM;i++)
        PageDir[i] = MakePTE(SegToLinier(seg.ds,
                    (unsigned short)PageTbl[i]));

    for (p=0;p<(long)MAXDIRNUM*PAGENUM*PAGESIZE;p+=PAGESIZE)
        SetPTE(p,p);

    lcr3(SegToLinier(seg.ds,(unsigned short)PageDir));
}

/*
 *    List 9-7  ページング機構のON/OFFも行う
 *                      RealToProto_P()関数とProtoToReal_P()関数
 *              [page.c  3/4] (page 318)
 */

void RealToProto_P(int sw)
{
    RealToProto_I(sw);
    PagingStart();
}

void ProtoToReal_P(void)
{
    PagingStop();
    ProtoToReal_I();
}

/*
 *    List 9-8  仮想記憶などのメモリ管理を行うための関数群
 *              [page.c  4/4] (page 319)
 */

int IsPTEAccessed(unsigned long viraddr)
{
    unsigned long *pte;

    pte = GetPTEAddr(viraddr);
    return (*pte)&PTE_ACCESS;
}

void ClearPTEAccessed(unsigned long viraddr)
{
    unsigned long *pte;

    pte = GetPTEAddr(viraddr);
    *pte &= ~PTE_ACCESS;
}

int IsPTEDirty(unsigned long viraddr)
{
    unsigned long *pte;

    pte = GetPTEAddr(viraddr);
    return (*pte)&PTE_DIRTY;
}

void SetPTEAbsent(unsigned long viraddr)
{
    unsigned long *pte;

    pte = GetPTEAddr(viraddr);
    *pte &= ~PTE_PRESENT;
}

int IsPTEPresent(unsigned long viraddr)
{
    unsigned long *pte;

    pte = GetPTEAddr(viraddr);
    return (*pte)&PTE_PRESENT;
}
