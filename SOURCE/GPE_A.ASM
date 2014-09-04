;;
;;    gpe_a.asm  ( List 7-16 )
;;    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
;;    All rights reserved.
;;
;;    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
;;    プログラムの一部です。プログラム内容や利用方法については本文の
;;    記述を参照してください。
;;

;;
;;    List 7-16  わざと例外を発生させるGenFault()関数
;;               [gpe_a.asm  1/1] (page 257)
;;

.386
_TEXT   segment byte public use16 'CODE'
        assume  cs:_TEXT

;;************************************************************
;; void GenFault(unsigned int sel)
public          _GenFault
_GenFault      proc    near
                push    bp
                mov     bp,sp
                push    ds
                mov     ds,[bp+4]
                ;
                mov     si,0300h
                mov     ax,[si]
                ;
                mov     si,0500h
                mov     ax,[si]
                ;
                pop     ds
                pop     bp
                ret
_GenFault      endp

_TEXT           ends
                end
