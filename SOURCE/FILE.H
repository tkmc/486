/*
 *    file.h  ( List 9-14 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 9-14  ヘッダファイル
 *               [file.h  1/1] (page 328)
 */

int ReadFile(int fd, unsigned long buf, int count);
int WriteFile(int fd, unsigned long buf, int count);
int SeekFile(int fd, long offset, int fromwhere);
