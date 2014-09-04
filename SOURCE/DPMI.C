/*
 *    dpmi.c  ( List 12-2, 12-5 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 12-2  DPMIの機能を呼び出す関数群
 *               [dpmi.c  1/2] (page 420)
 */

#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include "dpmi.h"

static union REGS reg;
static struct SREGS sreg;

void GetDPMIProtoEntry(union REGS *reg, struct SREGS *sreg)
{
    reg->x.ax = 0x1687;
    int86x(0x2f, reg, reg, sreg);
}

void DPMIRealToProto(void)
{
    unsigned short entryOff, entrySeg;
    char *buf;
    unsigned short bufseg;

    GetDPMIProtoEntry(&reg, &sreg);
    if (reg.x.ax != 0) {
        fprintf(stderr, "DPMI host is not available.\n");
        exit(1);
    }

    entryOff = reg.x.di;
    entrySeg = sreg.es;

    buf = (char *) malloc((reg.x.si+1)*16);
    if (buf==NULL) {
        fprintf(stderr, "Can't alloc memory for DPMI\n");
        exit(1);
    }
    segread(&sreg);
    bufseg = sreg.ds+((unsigned int)buf/16 +1);
    CallDPMIProtoEntry(entryOff, entrySeg, bufseg, 0);
}

void DPMIGetVersion(DPMI_Info *info)
{
    reg.x.ax = 0x0400;
    CallDPMI(&reg);
    if (reg.x.cflag) {
        fprintf(stderr, "Can't get version info\n");
        ExitToDos();
    }
    info->major = reg.h.ah;
    info->minor = reg.h.al;
    info->flags = reg.x.bx;
    info->cpu   = reg.h.cl;
    info->master_pic = reg.h.dh;
    info->slave_pic  = reg.h.dl;
}

/*
 *    List 12-5  DPMIの機能のうちの主要なものを呼び出す関数群
 *               [dpmi.c  2/2] (page 425)
 */

unsigned short DPMIAllocLDT(void)
{
    reg.x.ax=0x0000;
    reg.x.cx=1;
    CallDPMI(&reg);
    if (reg.x.cflag) {
        fprintf(stderr, "Can't alloc LDT\n");
        ExitToDos();
    }
    return reg.x.ax;
}

unsigned long DPMIAllocBlock(unsigned long size,
                                          unsigned long *addr)
{
    reg.x.ax = 0x0501;
    reg.x.bx = size >> 16;
    reg.x.cx = size & 0xffff;
    CallDPMI(&reg);
    if (reg.x.cflag) {
        fprintf(stderr, "Can't alloc Block\n");
        ExitToDos();
    }
    *addr = ((unsigned long)reg.x.bx<<16) + reg.x.cx;
    return ((unsigned long)reg.x.si<<16) + reg.x.di;
}

void DPMISetBaseAddr(unsigned short sel, unsigned long addr)
{
    reg.x.ax=0x0007;
    reg.x.bx=sel;
    reg.x.cx=addr>>16;
    reg.x.dx=addr&0xffff;
    CallDPMI(&reg);
    if (reg.x.cflag) {
        fprintf(stderr, "Can't set base address\n");
        ExitToDos();
    }
}

void DPMISetLimit(unsigned short sel, unsigned long limit)
{
    reg.x.ax=0x0008;
    reg.x.bx=sel;
    reg.x.cx=limit>>16;
    reg.x.dx=limit&0xffff;
    CallDPMI(&reg);
    if (reg.x.cflag) {
        fprintf(stderr, "Can't set limit\n");
        ExitToDos();
    }
}

void DPMISetRights(unsigned short sel,
                     unsigned char type, unsigned char type32)
{
    reg.x.ax = 0x0009;
    reg.x.bx = sel;
    reg.h.cl = type;
    reg.h.ch = type32;
    CallDPMI(&reg);
    if (reg.x.cflag) {
        fprintf(stderr, "Can't set access rights\n");
        ExitToDos();
    }
}

void DPMIFreeLDT(unsigned short sel)
{
    reg.x.ax = 0x0001;
    reg.x.bx = sel;
    CallDPMI(&reg);
    if (reg.x.cflag) {
        fprintf(stderr, "Can't free LDT\n");
        ExitToDos();
    }
}

void DPMIFreeBlock(unsigned long bh)
{
    reg.x.ax = 0x0502;
    reg.x.si = bh>>16;
    reg.x.di = bh&0xffff;
    CallDPMI(&reg);
    if (reg.x.cflag) {
        fprintf(stderr, "Can't free Block\n");
        ExitToDos();
    }
}

void ExitToDos(void)
{
    reg.x.ax=0x4c00;
    intdos(&reg,&reg);
}
