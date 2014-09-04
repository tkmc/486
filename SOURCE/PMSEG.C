/*
 *    pmseg.c  ( List 5-19 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 5-19  プロテクトモードに移行する例題プログラムpmseg
 *               [pmseg.c  1/1] (page 160)
 */

#include <stdio.h>
#include <dos.h>
#include "proto.h"
#include "printseg.h"

void main()
{
    int i, val;

    SetUpGDT();

    printf("Before ***********\n");
    for (i=8;i<=0x30;i+=8)
        PrintGDTSegDesc(i);

    val = 0;
    printf("val:%d\n",val);

    RealToProto();
    val = 1;
    ProtoToReal();

    printf("After  ***********\n");
    printf("val:%d\n",val);

    for (i=8;i<=0x30;i+=8)
        PrintGDTSegDesc(i);
}
