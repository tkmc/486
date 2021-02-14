/*
 *    disp.c  ( List 6-4 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 6-4  画面表示を行う関数群
 *              [disp.c  1/1] (page 215)
 */

#include <dos.h>
#include "proto.h"
#include "disp.h"

static int   ScreenWidth;
unsigned int VramSel;

void InitDisp(void)
{
    VramSel = AllocSel();
    SetSegDesc(VramSel, SegToLinear(VRAMSEG,0), 0x2000,
            TypeData, SmallSeg, 3);
#ifdef PC98
    ScreenWidth = 80;
#else /* PC/AT */
    ScreenWidth = *(unsigned int __far *)MK_FP(0x0040,0x004a);
#endif
}

void DispStr(int x, int y, char *str)
{
    vstr(x*2+y*ScreenWidth*2, VramSel, str);
}

