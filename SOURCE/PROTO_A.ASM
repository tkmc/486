;;
;;    proto_a.asm  ( List 5-12, 5-15, 5-16 )
;;    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
;;    All rights reserved.
;;
;;    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
;;    プログラムの一部です。プログラム内容や利用方法については本文の
;;    記述を参照してください。
;;

;;
;;    List 5-12  GDTRにロードするlgdt()関数
;;               [proto_a.asm  1/3] (page 154)
;;

.386p
_TEXT   segment byte public use16 'CODE'
        assume  cs:_TEXT

;; void lgdt(DescTblPtr *gdtptr);
public          _lgdt
_lgdt           proc    near
                push    bp
                mov     bp,sp
                mov     bx,[bp+4]
                lgdt    fword ptr [bx]
                pop     bp
                ret
_lgdt           endp

;;
;;    List 5-15  リアルモードからプロテクトモードに移行するRealToProto()関数
;;               [proto_a.asm  2/3] (page 156)
;;

saveDS  dw      ?
saveES  dw      ?
saveSS  dw      ?

;; void RealToProto(void);
public          _RealToProto
_RealToProto    proc    near
                push    bp
                mov     bp,sp
                ;
                mov     saveDS, ds
                mov     saveES, es
                mov     saveSS, ss
                ;
                cli
                ;
                mov     eax,cr0
                or      eax,1
                mov     cr0,eax
                ;
                jmp     flush_q1
flush_q1:
                db      0eah
                dw      offset set_cs_desc1
                dw      08h
set_cs_desc1:
                mov     ax,10h
                mov     ds,ax
                mov     es,ax
                mov     ax,18h
                mov     ss,ax
                ;
                pop     bp
                ret
_RealToProto    endp

;;
;;    List 5-16  プロテクトモードからリアルモードに移行するProtoToReal()関数
;;               [proto_a.asm  3/3] (page 157)
;;

;; void ProtoToReal(void);
public          _ProtoToReal
_ProtoToReal    proc    near
                push    bp
                mov     bp,sp
                ;
                mov     ax,28h
                mov     ds,ax
                mov     es,ax
                mov     ss,ax
                ;
                db      0eah
                dw      offset set_cs_desc2
                dw      20h
set_cs_desc2:
                mov     eax,cr0
                and     eax,0fffffffeh
                mov     cr0,eax
                ;
                jmp     flush_q2
flush_q2:
                db      0eah
                dw      offset set_cs_desc3
                dw      seg set_cs_desc3
set_cs_desc3:
                mov     ds, cs:saveDS
                mov     es, cs:saveES
                mov     ss, cs:saveSS
                ;
                pop     bp
                ret
_ProtoToReal    endp

_TEXT   ends
        end
