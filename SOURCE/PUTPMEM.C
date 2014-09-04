/*
 *    putpmem.c  ( List 5-23 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 5-23  putpmemのメインプログラム
 *               [putpmem.c  1/1] (page 171)
 */

#include <stdio.h>
#include <fcntl.h>
#include <dos.h>
#include <io.h>
#include <process.h>
#include "proto.h"
#include "pmem.h"

void main(int argc, char *argv[])
{
    char *filename, buf[1024];
    int m, fd;

    if (argc<2) {
        fprintf(stderr, "usage: putpmem filename\n");
        exit(1);
    }
    filename = argv[1];

    SetUpGDT();
    EnableA20();

    fd = open(filename, O_RDONLY|O_BINARY);
    if (fd < 0) {
        fprintf(stderr, "Can't open %s\n", filename);
        exit(1);
    }

    InitPmemBuf();

    while ((m = read(fd, buf, sizeof(buf))) > 0) {
        RealToProto();
        PutPmemBuf(buf, (unsigned long)m);
        ProtoToReal();
    }
    close(fd);
}
