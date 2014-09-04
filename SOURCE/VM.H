/*
 *    vm.h  ( List 9-10 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 9-10  ヘッダファイル
 *               [vm.h  1/1] (page 321)
 */

#define MAXDOSMEM 0xfffff
#define SWAPFILE "c:/swapfile.$$$"

extern unsigned long *PhysToVirTbl;
extern unsigned long SearchTop;

void VMInit(unsigned long ptop, unsigned long psize,
    unsigned long vtop, unsigned long vsize);
void VMMapFile(char *filename);
void VMClose(void);
void PageFault(void);
void PageFaultHandler(unsigned long viraddr);
void PageIn(unsigned long viraddr);
void PageOut(unsigned long viraddr);
unsigned long ReallocPhysMem(void);
int NextPhysPage(int i);
void FlushAllPage(void);
int PhysToVirIndex(unsigned long physaddr);
unsigned long PhysToVir(unsigned long physaddr);
long PageOffset(unsigned long viraddr);
