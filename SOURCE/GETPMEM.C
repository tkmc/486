/*
 *    getpmem.c  ( List 5-24 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 5-24  getpmemのメインプログラム
 *               [getpmem.c  1/1] (page 172)
 */

#include <stdio.h>
#include <dos.h>
#include <io.h>
#include "proto.h"
#include "pmem.h"
#define min(a,b) (a)<(b)?(a):(b)

unsigned long GetPmemBufSize(void);

void main()
{
    char buf[1024];
    unsigned long s=0,t;
    int m=sizeof(buf);

    SetUpGDT();
    EnableA20();

    RealToProto();
    t = GetPmemBufSize();
    m = min(t, m);
    ProtoToReal();

    while (m>0) {
        RealToProto();
        m = (int) GetPmemBuf(buf, s, (unsigned long)m);
        s += m;
        ProtoToReal();
        write(1, buf, m);
    }
}
