/*
 *    fault.c  ( List 7-15 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 7-15  保護機能を確認する例題プログラムfault
 *               [fault.c  1/1] (page 257)
 */

#include <dos.h>
#include "proto.h"
#include "disp.h"
#include "gate.h"
#include "int.h"

void GenFault(unsigned int);

void main(void)
{
    unsigned int sel;

    SetUpGDT();
    SetUpIDT(0);

    sel = AllocSel();
    SetSegDesc(sel, SegToLinier(seg.ds, 0), 0x03ff,
                                       TypeData, SmallSeg, 0);

    RealToProto_I(1);
    GenFault(sel);
    ProtoToReal_I();
}
