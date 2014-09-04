/*
 *    disp.h  ( List 6-3 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 6-3  ヘッダファイル
 *              [disp.h  1/1] (page 215)
 */

extern unsigned int VramSel;
void InitDisp(void);
void DispStr(int x, int y, char *str);
void vstr(unsigned int, unsigned int, char *str);

#ifdef PC98
#define VRAMSEG   0xa000
#else /* PC/AT */
#define VRAMSEG   0xb800
#endif
