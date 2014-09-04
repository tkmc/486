/*
 *    dpmiinfo.c  ( List 12-1 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 12-1  DPMIの働きを確認する例題プログラムのメインプログラム
 *               [dpmiinfo.c  1/1] (page 419)
 */

#include <stdio.h>
#include <dos.h>
#include "dpmi.h"

void main(void)
{
    DPMI_Info info;

    DPMIRealToProto();
    DPMIGetVersion(&info);

    printf("DPMI version %d.%d\n", info.major, info.minor);
    printf("host is %d-bit DPMI implementation\n",
                                               info.flags&1?32:16);
    printf("CPU returned to %s mode for reflected interrupts\n",
                                        info.flags&2?"real":"V86");
    printf("virtual memory %ssupported\n",
                                           info.flags&4?"":"not ");
    printf("processor type is %d86\n", info.cpu);
    printf("current value of PIC master base interrupt is 0x%02x\n",
                                                  info.master_pic);
    printf("current value of PIC slave base interrupt is 0x%02x\n",
                                                   info.slave_pic);

    ExitToDos();
}
