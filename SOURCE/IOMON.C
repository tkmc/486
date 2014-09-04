/*
 *    iomon.c  ( List 13-12 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 13-12  I/Oモニターのメインプログラム
 *                [iomon.c  1/1] (page 459)
 */

#include <stdio.h>
#include <dos.h>
#include <process.h>
#include <stdlib.h>
#include "proto.h"
#include "int.h"
#include "task.h"
#include "v86.h"
#include "v86iomon.h"
#include "disp.h"

IntFunc IntExit;

void main(int argc, char *argv[])
{
    int i;
    unsigned short port;
    void v86task(void);

    SetUpGDT();
    EnableA20();
    SetUpIDT(3);
    InitDisp();
    SetV86(v86task);
    SetUpV86IOmon();

    if (argc < 2) {
        fprintf(stderr, "usage: %s port-number...", argv[0]);
        exit(1);
    }
    for (i=1; i<argc; i++) {
        sscanf(argv[i], "%x", &port);
        SetV86IOmonAddr(port);
    }

    RealToV86();
}

void v86task(void)
{
    int e;
    char *shell;

    printf("begin I/O monitoring...\n");
    putenv("PROMPT=[I/O Monitoring] $p$g");

	if ((shell=getenv("COMSPEC"))==NULL) shell = "\\command.com";
    e = spawnl(P_WAIT, shell, shell, NULL);
    if (e!=0)
		perror(shell);

    /* abort program */
    bdos(0xff, 0, 0);
}

void v86IntHook(int n, unsigned short cs,
                          unsigned short ip, unsigned short ax)
{
    if (n == 0x21 && ax == 0xff00) {
        ProtoToReal_I();
        printf("I/O Monitoring stopped.\n");
        exit(1);
    }
}
