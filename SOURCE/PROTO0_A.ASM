;;
;;    proto0_a.asm  ( List 4-1, 4-2 )
;;    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
;;    All rights reserved.
;;
;;    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
;;    プログラムの一部です。プログラム内容や利用方法については本文の
;;    記述を参照してください。
;;

;;
;;    List 4-1  プロテクトモードへ移行する関数の暫定版
;;              [proto0_a.asm  1/2] (page 110)
;;

.386p
_TEXT   segment byte public use16 'CODE'
        assume  cs:_TEXT

;; void ProtoToReal(void);
public          _ProtoToReal
_ProtoToReal    proc    near
                push    bp
                mov     bp,sp
                ;
                mov     eax,cr0
                and     eax,0fffffffeh
                mov     cr0,eax
                ;
                jmp flush_q2
flush_q2:
                pop     bp
                ret
_ProtoToReal    endp

;;
;;    List 4-2  リアルモードへ移行する関数の暫定版
;;              [proto0_a.asm  2/2] (page 112)
;;

;; void RealToProto(void);
public          _RealToProto
_RealToProto    proc    near
                push    bp
                mov     bp,sp
                ;
                cli
                ;
                mov     eax,cr0
                or      eax,1
                mov     cr0,eax
                ;
                jmp     flush_q1
flush_q1:
                pop     bp
                ret
_RealToProto    endp

_TEXT   ends
        end
