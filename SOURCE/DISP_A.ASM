;;
;;    disp_a.asm  ( List 6-5 )
;;    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
;;    All rights reserved.
;;
;;    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
;;    プログラムの一部です。プログラム内容や利用方法については本文の
;;    記述を参照してください。
;;

;;
;;    List 6-5  文字列を画面に表示するvstr()関数
;;              [disp_a.asm  1/1] (page 216)
;;

.386
_TEXT   segment byte public use16 'CODE'
        assume  cs:_TEXT

;;************************************************************
;; display string
;; void vstr(unsigned int, unsigned int, char *str);
public          _vstr
_vstr           proc    near
                push    bp
                mov     bp,sp
                push    es
                push    si
                push    di
                mov     ax,[bp+6]
                mov     es,ax
                mov     di,[bp+4]
                mov     si,[bp+8]
vsloop:
                mov     al,[si]
                inc     si
                cmp     al,0
                jz      vsexit
                mov     es:[di],al
                inc     di
                inc     di
                jmp     vsloop
vsexit:
                pop     di
                pop     si
                pop     es
                pop     bp
                ret
_vstr           endp

_TEXT           ends
                end
