/*
 *    printseg.h  ( List 5-17 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 5-17  ヘッダファイル
 *               [printseg.h  1/1] (page 159)
 */

void PrintSegDesc(SegDesc  *desc);
void PrintGDTSegDesc(unsigned short sel);
