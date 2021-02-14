/*
 *    segtolin.c  ( List 5-10 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 5-10  リニアアドレスを計算するSegToLinear()関数
 *               [segtolin.c  1/1] (page 153)
 */

#include <dos.h>
#include "proto.h"

unsigned long SegToLinear(unsigned short seg,
                                          unsigned short off)
{
    return ((unsigned long)seg<<4) + off;
}


