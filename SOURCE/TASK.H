/*
 *    task.h  ( List 8-1, 8-5 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 8-1  TSSのレジスタ保存部
 *              [task.h  1/2] (page 271)
 */

typedef struct _TSS {
    unsigned short backlink;
    unsigned short f1;
    unsigned long esp0;
    unsigned short ss0;
    unsigned short f2;
    unsigned long esp1;
    unsigned short ss1;
    unsigned short f3;
    unsigned long esp2;
    unsigned short ss2;
    unsigned short f4;
    unsigned long cr3;
    unsigned long eip;
    unsigned long eflags;
    unsigned long eax;
    unsigned long ecx;
    unsigned long edx;
    unsigned long ebx;
    unsigned long esp;
    unsigned long ebp;
    unsigned long esi;
    unsigned long edi;
    unsigned short es;
    unsigned short f5;
    unsigned short cs;
    unsigned short f6;
    unsigned short ss;
    unsigned short f7;
    unsigned short ds;
    unsigned short f8;
    unsigned short fs;
    unsigned short f9;
    unsigned short gs;
    unsigned short f10;
    unsigned short ldt;
    unsigned short f11;
    unsigned short t;
    unsigned short iobase;
} TSS;

/*
 *    List 8-5  ヘッダファイル
 *              [task.h  2/2] (page 285)
 */

void SetTSS(
  TSS *t,
  unsigned short cs,
  unsigned short ds,
  void (*f)(),
  unsigned long eflags,
  unsigned char *esp,
  unsigned short ss,
  unsigned char *esp0,
  unsigned short ss0
);

void ltr(unsigned short selector);
void SwitchTask(unsigned short sel);
