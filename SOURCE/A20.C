/*
 *    a20.c  ( List 5-25 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 5-25  ガードをはずして全アドレスを有効にするEnableA20()関数
 *               [a20.c  1/1] (page 174)
 */

#include "proto.h"
#include <dos.h>
#include <conio.h>

void EnableA20(void)
{
#ifdef PC98
    outp(0xf2,0);
#else /* PC/AT */
    while(inp(0x64)&2);
    outp(0x64,0xd1);
    while(inp(0x64)&2);
    outp(0x60,0xdf);
    while(inp(0x64)&2);
    outp(0x64,0xff);
    while(inp(0x64)&2);
#endif
}
