/*
 *    pmem.h  ( List 5-21 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 5-21  ヘッダファイル
 *               [pmem.h  1/1] (page 169)
 */

void InitPmemBuf(void);
void SetPmemBufSize(unsigned long m);
unsigned long GetPmemBufSize();
void PutPmemBuf(char *buf, unsigned long m);
unsigned long GetPmemBuf(char *buf,
                            unsigned long s, unsigned long m);
