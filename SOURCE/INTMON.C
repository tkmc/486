/*
 *    intmon.c  ( List 11-4 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 11-4  オペレーティングシステムの役割を演じる
 *                       例題プログラムのメインプログラム
 *               [intmon.c  1/1] (page 398)
 */

#include <stdio.h>
#include <dos.h>
#include <process.h>
#include <string.h>
#include <stdlib.h>
#include "proto.h"
#include "int.h"
#include "task.h"
#include "v86.h"
#include "disp.h"
#include "pmem.h"

IntFunc IntExit;

void main()
{
    void v86task();

    SetUpGDT();
    EnableA20();
    SetUpIDT(3);
    InitDisp();
    SetV86(v86task);
    InitPmemBuf();

    RealToV86();
}

void v86task()
{
    int e;
    char *shell;

    printf("entering V86 mode.\n");
    printf("begin monitoring interrupts...\n");
    putenv("PROMPT=[Interrupts Monitoring] $p$g");

	if ((shell=getenv("COMSPEC"))==NULL) shell = "\\command.com";
    e = spawnl(P_WAIT, shell, shell, NULL);
    if (e!=0)
		perror(shell);

    /* abort program */
    bdos(0xff, 0, 0);
}

void v86IntHook(int n, unsigned short cs, unsigned short ip,
                                              unsigned short ax)
{
    char buf[64];
    unsigned long len;
    static int m=0;

    if (n < 0x10) {
        sprintf(buf,"int %02X cs:%04X ip:%04X ax:%04X",
                                                 n, cs, ip, ax);
        DispStr(45,m,buf);
        if (m++>=24)
            m=0;

        sprintf(buf,"int %02X cs:%04X ip:%04X ax:%04X\n",
                                                 n, cs, ip, ax);
        len = strlen(buf);
        PutPmemBuf(buf, len);
    }
    if (n == 0x21 && ax == 0xff00) {
        ProtoToReal_I();
        printf("exiting V86 mode...\n");
        exit(1);
    }
}
