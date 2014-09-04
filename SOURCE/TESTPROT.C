/*
 *    tesstprot.c  ( List 4-3 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 4-3  プロテクトモードに移行するプログラム
 *             ［testprot.c 1/1］ (page 113)
 */

#include <stdio.h>
#include <dos.h>
#include "proto0.h"

void main()
{
    printf("Now going to Protected mode...");
    getchar();

    RealToProto();
    ProtoToReal();

    printf("Returned from Protected mode.\n");
}
