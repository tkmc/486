;;
;;    trans_a.asm  ( List 5-20 )
;;    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
;;    All rights reserved.
;;
;;    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
;;    プログラムの一部です。プログラム内容や利用方法については本文の
;;    記述を参照してください。
;;

;;
;;    List 5-20  指定されたメモリの内容を転送するMemTransfer()関数
;;               [trans_a.asm  1/1] (page 168)
;;

.386
_TEXT   segment byte public use16 'CODE'
        assume  cs:_TEXT

;;************************************************************
;;   void MemTransfer(unsigned long target, 
;;                          unsigned long source, long count);
public          _MemTransfer
_MemTransfer    proc
                push    bp
                mov     bp,sp
                push    ds
                push    esi
                push    edi
                mov     ax,30h
                mov     ds,ax
                mov     edi,[bp+4]
                mov     esi,[bp+8]
                mov     ecx,[bp+12]
                jcxz    m_exit
m_loop:
                mov     al,[esi]
                inc     esi
                mov     [edi],al
                inc     edi
                dec     ecx
                jnz     m_loop
m_exit:
                pop     edi
                pop     esi
                pop     ds
                pop     bp
                ret
_MemTransfer    endp

_TEXT           ends
                end
