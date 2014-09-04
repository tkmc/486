/*
 *    v86iomon.h  ( List 13-11 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 13-11  ヘッダファイル
 *                [v86iomon.h  1/1] (page 459)
 */

void SetUpV86IOmon(void);
void SetV86IOmonAddr(unsigned short port);
unsigned int v86IOIntHook(unsigned short cs, unsigned short ip,
    unsigned int opcode, unsigned short *ax, unsigned short dx);
void iomon(char *str, unsigned short a, unsigned short b,
    unsigned short c, unsigned short d);
void v86IOint(void);
