/*
 *    revfile.c  ( List 13-4 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 13-4  メモリマップトファイル上で並べ替えを行うプログラムrevfile
 *               [revfile.c  1/1] (page 443)
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <dos.h>
#include "proto.h"
#include "int.h"
#include "page.h"
#include "vm.h"

#define MMAPADR  0x100000
#define MMAPSIZE 0x400000
#define PHYSSIZE 0x4000

#define FILENAME "c:\\person.dat"

void VMMapFile(char *);
void VMClose(void);
void MemTransfer(unsigned long,unsigned long,unsigned long);
unsigned long GetPmemBufSize(void);

typedef struct _person {
    char    name[16];
    char    yomi[22];
    char    age[3];
    char    sex[2];
    char    total[10];
    char    month[9];
    char    crlf[2];
} PERSON;

void main(int argc, char *argv[])
{
    unsigned short sel;
    char *filename;
    FILE *fp;
    long n;
    void reverse_mem(unsigned int sel, unsigned long base,
                          unsigned long n, unsigned long size);

    if (argc>1)
        filename = argv[1];
    else
        filename = FILENAME;

    fp = fopen(filename, "rb");
    if (fp==NULL) {
        fprintf(stderr, "Can't open %s\n", filename);
        exit(1);
    }
    fseek(fp, 0L, SEEK_END);
    n = ftell(fp)/sizeof(PERSON);
    fclose(fp);

    SetUpGDT();
    SetUpIDT(0);
    EnableA20();

    SetUpPTE();

    VMInit(MMAPADR, PHYSSIZE, MMAPADR, MMAPSIZE);
    VMMapFile(filename);

    sel = AllocSel();
    SetSegDesc(sel, MMAPADR, (MMAPSIZE>>12)+1,
                                     TypeData, BigSeg, 0);

    RealToProto_P(0);

    reverse_mem(sel, 0L, n, (long) sizeof(PERSON));

    VMClose();
    ProtoToReal_P();
}
