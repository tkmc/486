/*
 *    gate.c  ( List 6-2 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 6-2  ゲートディスクリプタを作成する
 *                      MakeGate()関数と設定するSetGateDesc()関数
 *              [gate.c  1/1] (page 209)
 */

#include <dos.h>
#include "proto.h"
#include "gate.h"

void MakeGate(GateDesc *gate, unsigned short sel, void (*f)(),
    unsigned short count, unsigned char type, unsigned char dpl)
{
    gate->offsetL  = (unsigned short) f;
    gate->selector = sel;
    gate->count    = count;
    gate->type     = type | (dpl<<5);
    gate->offsetH  = 0;
}

void SetGateDesc(unsigned short selgate,
    unsigned short selcs, void (*f)(), unsigned short count,
                          unsigned char type, unsigned char dpl)
{
    extern SegDesc gdt[];

    MakeGate((GateDesc *)&gdt[selgate>>3], selcs, f, count, type, dpl);
}

