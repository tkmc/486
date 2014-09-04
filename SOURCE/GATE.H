/*
 *    gate.h  ( List 6-1 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 6-1  ゲートディスクリプタの構造を表す構造体GateDesc型の定義
 *              [gate.h  1/1] (page 208)
 */

typedef struct _GateDesc {
    unsigned short offsetL;
    unsigned short selector;
    unsigned char  count;
    unsigned char  type;
    unsigned short offsetH;
} GateDesc;

void MakeGate(GateDesc *gate, unsigned short sel,
                       void (*f)(), unsigned short count,
                       unsigned char type, unsigned char dpl);
void SetGateDesc(unsigned short selgate,
    unsigned short selcs, void (*f)(), unsigned short count,
                       unsigned char type, unsigned char dpl);
