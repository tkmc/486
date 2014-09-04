/*
 *    hardint.c  ( List 7-12 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 7-12  ハードウェア割り込みの発生を確認する例題プログラムhardint
 *               [hardint.c  1/1] (page 252)
 */

#include <dos.h>
#include <stdio.h>
#include "proto.h"
#include "int.h"

void main()
{
    void TestHardInt(void);
    void CheckInt(int n, unsigned short cs, unsigned short ip);

    SetUpGDT();
    InitDisp();
    SetUpIDT(0);

    IntHook    = CheckInt;

    RealToProto_I(1);
    TestHardInt();
    ProtoToReal_I();
}

void DispInt(int n, unsigned short cs, unsigned short ip)
{
    char buf[32];
    static int m=0;

    sprintf(buf,"interrupt %02X cs:%04X ip:%04X", n, cs, ip);
    DispStr(50,m,buf);
    if (++m>20)
        m=0;
}

int keyInt;

void CheckInt(int n, unsigned short cs, unsigned short ip)
{
    if (n==KEYINTVEC)
        keyInt++;
    DispInt(n,cs,ip);
}

void TestHardInt(void)
{
    int n;
    char buf[32];

    keyInt=n=0;
    while (n<10) {
        if (keyInt>0) {
            n++;
            sprintf(buf,"Key interrupted %d tiems.", n);
            DispStr(0,2,buf);
            keyInt--;
        }
    }
}
