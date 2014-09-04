/*
 *    rmseg.c  ( List 5-1 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 5-1  リアルモードのセグメントを確認する例題プログラム
 *              [rmseg.c  1/1] (page 134)
 */

#include <stdio.h>
#include <dos.h>

void main()
{
    struct SREGS sreg;
    
    segread(&sreg);
    printf("cs:%04x ds:%04x es:%04x ss:%04x\n",
        sreg.cs, sreg.ds, sreg.es, sreg.ss);
}
