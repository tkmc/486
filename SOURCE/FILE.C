/*
 *    file.c  ( List 9-15 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
 *    プログラムの一部です。プログラム内容や利用方法については本文の
 *    記述を参照してください。
 */

/*
 *    List 9-15  ディスクにファイルを読み書きする関数群
 *               [file.c  1/1] (page 328)
 */

#include <dos.h>
#include <io.h>
#include <fcntl.h>
#include "proto.h"
#include "page.h"
#include "file.h"
#include "pmem.h"

void MemTransfer(unsigned long,unsigned long,unsigned long);

static char dosbuf[PAGESIZE];

int ReadFile(int fd, unsigned long buf, int count)
{
    int r;

    ProtoToReal_P();
    r = read(fd, dosbuf, count);
    RealToProto_P(0);

    MemTransfer(buf,
       SegToLinier(seg.ds, (unsigned short) dosbuf), (long) r);
    return r;
}

int WriteFile(int fd, unsigned long buf, int count)
{
    int r;

    MemTransfer(SegToLinier(seg.ds, (unsigned short) dosbuf),
                                            buf, (long) count);

    ProtoToReal_P();
    r = write(fd, dosbuf, count);
    RealToProto_P(0);

    return r;
}

int SeekFile(int fd, long offset, int fromwhere)
{
    int r;

    ProtoToReal_P();
    r = lseek(fd, offset, fromwhere);
    RealToProto_P(0);

    return r;
}
