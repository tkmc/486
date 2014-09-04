/*
 *    v86.h  ( List 11-2 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 11-2  ヘッダファイル
 *               [v86.h  1/1] (page 394)
 */

typedef struct _TSS_IO {
    TSS tss;
    unsigned char iomap[8193];
} TSS_IO;

extern TSS_IO  v86tss;

void SetV86(void (*f)());
void RealToV86(void);
IntFunc v86int;
