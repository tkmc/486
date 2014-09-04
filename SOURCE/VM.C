/*
 *    vm.c  ( List 9-11, 9-13 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 9-11  仮想記憶の初期化と終了を行う関数群
 *               [vm.c  1/2] (page 323)
 */

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <io.h>
#include <dos.h>
#include <malloc.h>
#include <process.h>
#include "proto.h"
#include "int.h"
#include "page.h"
#include "file.h"
#include "vm.h"

unsigned long PhysTop, PhysSize, PhysPageNum, VirTop, VirSize;
unsigned long *PhysToVirTbl;
unsigned long SearchTop;
int virfd;

void VMInit(unsigned long ptop, unsigned long psize,
    unsigned long vtop, unsigned long vsize)
{
    unsigned long p, v;

    PhysTop = ptop;
    PhysSize = psize;
    PhysPageNum = psize/PAGESIZE;
    VirTop = vtop;
    VirSize = vsize;

    PhysToVirTbl = (unsigned long *)
            malloc(PhysPageNum*sizeof(unsigned long));
    if (PhysToVirTbl==NULL) {
        fprintf(stderr, "VMInit: Can't alloc memory.\n");
        exit(1);
    }

    for (p=0;p<=MAXDOSMEM;p+=PAGESIZE)
        SetPTE(p,p);

    for (p=ptop; p<ptop+psize; p+=PAGESIZE)
        PhysToVirTbl[PhysToVirIndex(p)] = 0L;

    for (v=VirTop; v < VirTop+VirSize; v+=PAGESIZE)
        SetPTEAbsent(v);

    SearchTop = 0;

    SetIDTGateDesc(0x0e, 0x08, PageFault, 0, TypeTrapGate, 0);
}

void VMMapFile(char *filename)
{
    virfd = open(filename, O_RDWR|O_CREAT|O_BINARY, S_IREAD|S_IWRITE);
    if (virfd<0) {
        printf("Can't open %s\n", filename);
        exit(1);
    }
}

void VMClose(void)
{
    FlushAllPage();

    ProtoToReal_P();
    close(virfd);
    RealToProto_P(0);
}

/*
 *    List 9-13  ページフォルトの処理を行うPageFaultHander()関数
 *               [vm.c  2/2] (page 326)
 */

void PageFaultHandler(unsigned long viraddr)
{
    unsigned long virpage,physaddr;

    virpage = viraddr&0xfffff000;
    physaddr = ReallocPhysMem();

#ifdef DEBUG
    ProtoToReal_P();
    printf("Page Fault at %08lx: page out %08lx",
      viraddr, PhysToVirTbl[PhysToVirIndex(physaddr)]);
    printf(" [at phys-mem %08lx]\n", physaddr);
    RealToProto_P(0);
#endif

    PageOut(PhysToVir(physaddr));
    SetPTEAbsent(PhysToVir(physaddr));
    SetPTE(virpage, physaddr);
    PhysToVirTbl[PhysToVirIndex(physaddr)] = virpage;
    FlushTLB();
    PageIn(virpage);
}

void PageIn(unsigned long viraddr)
{
    SeekFile(virfd, PageOffset(viraddr), SEEK_SET);
    ReadFile(virfd, viraddr, PAGESIZE);
}

void PageOut(unsigned long viraddr)
{
    if (IsPTEPresent(viraddr) && IsPTEDirty(viraddr)) {
        SeekFile(virfd, PageOffset(viraddr), SEEK_SET);
        WriteFile(virfd, viraddr, PAGESIZE);
    }
}

unsigned long ReallocPhysMem(void)
{
    unsigned int i;
    unsigned long v;

    i = SearchTop;
    for (;;) {
        v = PhysToVirTbl[i];
        if (v == 0L)
            break;
        if (!IsPTEAccessed(v))
            break;
        ClearPTEAccessed(v);
        i = NextPhysPage(i);
        if (i==SearchTop)
            break;
    }
    SearchTop = NextPhysPage(i);
    return PhysTop+i*PAGESIZE;
}

int NextPhysPage(int i)
{
    if (i+1>=PhysPageNum)
        return 0;
    else
        return i+1;
}

void FlushAllPage(void)
{
    unsigned int i;

    for (i=0; i<PhysPageNum; i++)
        PageOut(PhysToVir(PhysTop+i*PAGESIZE));
}

int PhysToVirIndex(unsigned long physaddr)
{
    return (physaddr-PhysTop)/PAGESIZE;
}

unsigned long PhysToVir(unsigned long physaddr)
{
    return PhysToVirTbl[PhysToVirIndex(physaddr)];
}

long PageOffset(unsigned long viraddr)
{
    return viraddr-VirTop;
}
