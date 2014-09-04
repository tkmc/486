/*
 *    proto.h  ( List 5-2, 5-3, 5-6, 5-7, 5-13 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 5-3  セグメントディスクリプタの構造を表す構造体SegDesc型の定義
 *              [proto.h  1/5] (page 150)
 */

/* Segment Descripter */
typedef struct _SegDesc {
    unsigned short limitL;
    unsigned short baseL;
    unsigned char  baseM;
    unsigned char  type;
    unsigned char  limitH;
    unsigned char  baseH;
} SegDesc;

/*
 *    List 5-6  セグメント属性の定義
 *              [proto.h  2/5] (page 152)
 */

/* Descriptor Type */
#define TypeCode     0x9a
#define TypeData     0x92
#define TypeStack    0x96
#define TypeLDT      0x82
#define TypeTSS      0x89
#define TypeTSSBusy  0x8b
#define TypeCallGate 0x84
#define TypeIntrGate 0x8e
#define TypeTrapGate 0x8f
#define TypeTaskGate 0x85

/*
 *    List 5-7  セグメントの32ビット属性の定義
 *              [proto.h  3/5] (page 152)
 */

/* Descriptor Type 32 */
#define BigSeg       0x80
#define SmallSeg     0x00

#define Code386      0x40
#define Data386      0x40
#define Code286      0x00

/*
 *    List 5-13  GDTRの構造を表す構造体DescTblPtr型の定義
 *               [proto.h  4/5] (page 155)
 */

typedef struct _DescTblPtr {
    unsigned short  limit;
    unsigned long   base;
} DescTblPtr;

/*
 *    List 5-2  グローバル変数の定義や関数のプロトタイプ宣言
 *              [proto.h  5/5] (page 148)
 */

/* global variables */
extern struct SREGS seg;

/* function definition */
unsigned int AllocSel(void);
void SetSegDesc(
  unsigned short sel,
  unsigned long addr,
  unsigned long limit,
  unsigned char segtype,
  unsigned char seg32type,
  unsigned char dpl);
unsigned long SegToLinier(unsigned short seg,
                                           unsigned short off);
void          SetUpGDT(void);
void          InitDisp(void);
void          DispStr(int x, int y, char *str);
void          EnableA20(void);

void lgdt(DescTblPtr *);
void RealToProto(void);
void ProtoToReal(void);
