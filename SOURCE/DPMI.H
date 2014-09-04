/*
 *    dpmi.h  ( List 12-4 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 12-4  ヘッダファイル
 *               [dpmi.h  1/1] (page 423)
 */

typedef struct _DPMI_Info {
    unsigned char major;
    unsigned char minor;
    unsigned short flags;
    unsigned char cpu;
    unsigned char master_pic;
    unsigned char slave_pic;
} DPMI_Info;

void DPMIRealToProto(void);
unsigned short DPMIAllocLDT(void);
unsigned long DPMIAllocBlock(unsigned long size, 
                                         unsigned long *addr);
void DPMISetBaseAddr(unsigned short sel, unsigned long addr);
void DPMISetLimit(unsigned short sel, unsigned long limit);
void DPMISetRights(unsigned short sel, unsigned char type,
    unsigned char type32);
void DPMIFreeLDT(unsigned short sel);
void DPMIFreeBlock(unsigned long bh);
void ExitToDos(void);
void DPMIGetVersion(DPMI_Info *info);

void CallDPMI(union REGS *reg);
void CallDPMIProtoEntry(unsigned short off,
                       unsigned short sel, int seg, int type);
