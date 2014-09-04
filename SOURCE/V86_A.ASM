;;
;;    v86_a.asm  ( List 11-3 )
;;    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
;;    All rights reserved.
;;
;;    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
;;    プログラムの一部です。プログラム内容や利用方法については本文の
;;    記述を参照してください。
;;

;;
;;    List 11-3  リアルモードの割り込みのエミュレートを行うプログラム
;;               [v86_a.asm  1/1] (page 396)
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
                extrn   _v86IntHook:near
;;************************************************************
;; void v86int();
public  _v86int
_v86int         proc near
                push    bp
                mov     bp,sp
                ;
                push    word ptr [bp+18]
                push    word ptr [bp+26]
                push    word ptr [bp+30]
                push    word ptr [bp+24]
                call    _v86IntHook
                add     esp,8
                ;
                mov     ax,30h
                mov     ds,ax
                movzx   ebx,word ptr [bp+42]
                shl     ebx,4
                add     ebx,[bp+38]
                ;
                mov     ax,[bp+34]
                mov     [ebx-2],ax
                mov     ax,[bp+30]
                mov     [ebx-4],ax
                mov     ax,[bp+26]
                mov     [ebx-6],ax
                sub     word ptr [bp+38],6
                ;
                movzx   ebx,byte ptr [bp+24]
                mov     ax,[ebx*4]
                mov     [bp+26],ax
                mov     ax,[ebx*4+2]
                mov     [bp+30],ax
                ;
                pop     bp
                ret
_v86int         endp

_TEXT   ends
        end
