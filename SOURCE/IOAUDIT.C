/*
 *    ioaudit.c  ( List 13-7, 13-9, 13-10 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 13-10  I/Oアクセスの記録とI/Oモニターの初期化を行う関数
 *                [ioaudit.c  1/3] (page 458)
 */

#include <dos.h>
#include <stdio.h>
#include <string.h>
#ifdef __WATCOMC__
#include <conio.h>
#endif
#include "proto.h"
#include "int.h"
#include "task.h"
#include "v86.h"
#include "v86iomon.h"
#include "pmem.h"

static char buf[64];

void IOaudit(char *str, unsigned short a, unsigned short b,
                            unsigned short c, unsigned short d)
{
    unsigned long m;

    sprintf(buf, str, a, b, c, d);
    m = strlen(buf);
    PutPmemBuf(buf, m);
}

void SetUpV86IOmon(void)
{
      SetIDTGateDesc(0x0d, 0x08, v86IOint, 0, TypeIntrGate, 0);
    InitPmemBuf();
}

/*
 *    List 13-7  指定したポート番号のアクセスを禁止するSetV86IOmonAddr()関数
 *               [ioaudit.c  2/3] (page 454)
 */

void SetV86IOmonAddr(unsigned short port)
{
    v86tss.iomap[port/8] |= 1<<(port%8);
}

/*
 *    List 13-9  例外発生時点の命令の種類を調べるV86IOintHook()関数
 *               [ioaudit.c  3/3] (page 456)
 */

unsigned int v86IOIntHook(unsigned short cs, unsigned short ip,
    unsigned int opcode, unsigned short *ax, unsigned short dx)
{
    unsigned char port;
    unsigned short value;
    unsigned char *al;
    unsigned int opsiz;

    port = ((opcode>>8) & 0xff);
    al = (unsigned char *) ax;

    switch(opcode & 0xff) {
    case 0xe4:
        value = inp(port);
        *al = value;
        IOaudit("%04x:%04x  in al, %02x = %02x\n",
                                          cs, ip, port, value);
        opsiz = 2;
        break;
    case 0xe5:
        value = inpw(port);
        *ax = value;
        IOaudit("%04x:%04x  in ax, %02x = %04x\n",
                                          cs, ip, port, value);
        opsiz = 2;
        break;
    case 0xec:
        value = inp(dx);
        *al = value;
        IOaudit("%04x:%04x  in al, dx(%04x) = %02x\n",
                                            cs, ip, dx, value);
        opsiz = 1;
        break;
    case 0xed:
        value = inpw(dx);
        *ax = value;
        IOaudit("%04x:%04x  in ax, dx(%04x) = %04x\n",
                                            cs, ip, dx, value);
        opsiz = 1;
        break;
    case 0xe6:
        outp(port, *al);
        IOaudit("%04x:%04x  out %02x, al(%02x)\n",
                                            cs, ip, port, *al);
        opsiz = 2;
        break;
    case 0xe7:
        outpw(port, *ax);
        IOaudit("%04x:%04x  out %02x, ax(%04x)\n",
                                            cs, ip, port, *ax);
        opsiz = 2;
        break;
    case 0xee:
        outp(dx, *al);
        IOaudit("%04x:%04x  out dx(%04x), al(%02x)\n",
                                              cs, ip, dx, *al);
        opsiz = 1;
        break;
    case 0xef:
        outpw(dx, *ax);
        IOaudit("%04x:%04x  out dx(%04x), ax(%04x)\n",
                                              cs, ip, dx, *ax);
        opsiz = 1;
        break;
    default:
        sprintf(buf, "Unknown opcode %02x", opcode & 0xff);
        DispStr(30,22, buf);
        for (;;);
    }
    return opsiz;
}

