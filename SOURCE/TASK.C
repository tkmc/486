/*
 *    task.c  ( List 8-2 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 8-2  タスク起動時のレジスタの値をTSSに設定するSetTSS()関数
 *              [task.c  1/1] (page 272)
 */

#include <stdio.h>
#include <dos.h>
#include <memory.h>
#include "proto.h"
#include "task.h"

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
)
{
    memset(t, 0, sizeof(TSS));
    t->cs       = cs;
    t->eip      = (unsigned short) f;
    t->eflags   = eflags;
    t->esp      = (unsigned short) esp;
    t->ds = t->es = ds;
    t->ss = ss;
    t->esp0     = (unsigned short) esp0;
    t->ss0      = ss0;
}

