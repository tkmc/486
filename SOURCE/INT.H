/*
 *    int.h  ( List 7-2 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 7-2  ヘッダファイル
 *              [int.h  1/1] (page 243)
 */

#define IDTNUM 256
#define FLAG_INT_ENABLE  0x200

typedef void    IntFunc(
  unsigned short di, unsigned short si, unsigned short bp,
  unsigned short sp, unsigned short bx, unsigned short dx,
  unsigned short cx, unsigned short ax, unsigned short es,
  unsigned short ds, unsigned short n, long eip,
  unsigned short cs, unsigned short f1, unsigned eflags
);
extern IntFunc     *IntHandler;
extern DescTblPtr  idtptr,ridtptr;
extern void        (*IntHook)(int n, unsigned short cs,
                                           unsigned short ip);

void SetIDTGateDesc(int i, unsigned short sel, void (*f)(),
                   unsigned short count, unsigned char type,
                                           unsigned char dpl);
void SetUpIDT(unsigned char dpl);
void    RealModeInt(
  unsigned short di, unsigned short si, unsigned short bp,
  unsigned short sp, unsigned short bx, unsigned short dx,
  unsigned short cx, unsigned short ax, unsigned short es,
  unsigned short ds, unsigned short n, long eip, 
  unsigned short cs, unsigned short f1, unsigned eflags
);
void RealToProto_I(int sw);
void ProtoToReal_I(void);

void lidt(DescTblPtr *idtptr);
void EnableInterrupt(void);
void DisableInterrupt(void);

#ifdef PC98
#define KEYINTVEC 9
#define TIMERVEC 0x0A
#else /* PC/AT */
#define KEYINTVEC 9
#define TIMERVEC 8
#endif
