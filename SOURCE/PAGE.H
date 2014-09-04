/*
 *    page.h  ( List 9-2, 9-4, 9-9 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 9-2  PTEの各ビットの定義
 *              [page.h  1/3] (page 314)
 */

#define PTE_PRESENT 0x01
#define PTE_RW      0x02
#define PTE_USER    0x04
#define PTE_ACCESS  0x20
#define PTE_DIRTY   0x40

/*
 *    List 9-4  使用するページテーブルの定義
 *              [page.h  2/3] (page 316)
 */

#define PAGENUM 1024
#define PAGESIZE 4096
#define MAXDIRNUM 2

/*
 *    List 9-9  関数のプロトタイプ宣言
 *              [page.h  3/3] (page 320)
 */

void lcr3(unsigned long PageDirAddr);
unsigned long cr2(void);
void FlushTLB(void);
void PagingStart(void);
void PagingStop(void);

unsigned long *GetPTEAddr(unsigned long viraddr);
long MakePTE(unsigned long physaddr);
void SetPTE(unsigned long viraddr, unsigned long physaddr);
int IsPTEAccessed(unsigned long viraddr);
void ClearPTEAccessed(unsigned long viraddr);
int IsPTEDirty(unsigned long viraddr);
void SetPTEAbsent(unsigned long viraddr);
int IsPTEPresent(unsigned long viraddr);
void SetUpPTE(void);
void PagingEnable(void);
void RealToProto_P(int sw);
void ProtoToReal_P(void);

extern int Paging;
