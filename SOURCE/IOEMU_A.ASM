;;
;;    ioemu_a.asm  ( List 13-8 )
;;    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
;;    All rights reserved.
;;
;;    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
;;    プログラムの一部です。プログラム内容や利用方法については本文の
;;    記述を参照してください。
;;

;;
;;    List 13-8  V86IOint()関数
;;               [ioemu_a.asm  1/1] (page 454)
;;

        .386p
_TEXT   segment byte public use16 'CODE'
_TEXT   ends
DGROUP  group   _DATA,_BSS
        assume  cs:_TEXT,ds:DGROUP
_DATA   segment word public use16 'DATA'
_DATA   ends
_BSS    segment word public use16 'BSS'
_BSS    ends
_TEXT   segment byte public use16 'CODE'
        assume  cs:_TEXT
;;
                extrn   _v86IOIntHook:near
;;************************************************************
;; void v86IOint(void);
public  _v86IOint
_v86IOint       proc near
                push    ds
                push    es
                pusha
                mov     ax,10h
                mov     ds,ax
                mov     es,ax
                push    bp
                mov     bp,sp
                ;
                push    word ptr [bp+12]        ; dx
                lea     ax, word ptr [bp+16]    ; &ax
                push    ax
                ;
                push    ds
                mov     ax,30h
                mov     ds,ax
                movzx   ebx,word ptr [bp+30]    ; cs
                shl     ebx,4
                add     ebx,[bp+26]             ; ip
                mov     ax,[ebx]                ; opeation code
                pop     ds
                push    ax
                ;
                push    word ptr [bp+26]        ; ip
                push    word ptr [bp+30]        ; cs
                ;
                call    _v86IOIntHook
                add     esp, 10
                add     word ptr [bp+26], ax    ; next ip
                ;
                pop     bp
                popa
                pop     es
                pop     ds
                add     esp,4
                iretd
_v86IOint       endp

_TEXT   ends
        end
