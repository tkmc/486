;;
;;    dpmi_a.asm  ( List 12-3 )
;;    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
;;    All rights reserved.
;;
;;    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
;;    プログラムの一部です。プログラム内容や利用方法については本文の
;;    記述を参照してください。
;;

;;
;;    List 12-3  DPMIホストを呼び出す関数群
;;               [dpmi_a.asm  1/1] (page 421)
;;

.386
_TEXT   segment byte public use16 'CODE'
        assume  cs:_TEXT

;;************************************************************
;; void CallDPMI(union REGS *reg);
public          _CallDPMI
_CallDPMI       proc    near
                push    bp
                mov     bp,sp
                push    si
                push    di
                mov     bx,[bp+4]
                ;
                mov     ax,ds
                mov     es,ax
                mov     ax,[bx+0]
                mov     cx,[bx+4]
                mov     dx,[bx+6]
                mov     si,[bx+8]
                mov     di,[bx+10]
                mov     bx,[bx+2]
                ;
                int     31h
                ;
                push    bx
                mov     bx,[bp+4]
                mov     [bx+0],ax
                mov     [bx+4],cx
                mov     [bx+6],dx
                mov     [bx+8],si
                mov     [bx+10],di
                mov     ax,0
                jnc     noCarry
                mov     ax,1
noCarry:        mov     [bx+12],ax
                pushf
                pop     ax
                mov     [bx+14],ax
                mov     si,bx
                pop     bx
                mov     [si+2],bx
                ;
                pop     di
                pop     si
                pop     bp
                ret
_CallDPMI       endp

;;************************************************************
;; void CallDPMIProtoEntry(void far (*entry)(),
;;                                         int seg, int type);
public          _CallDPMIProtoEntry
_CallDPMIProtoEntry     proc    near
                push    bp
                mov     bp,sp
                ;
                mov     es,[bp+8]
                mov     ax,[bp+10]
                call    dword ptr [bp+4]
                ;
                pop     bp
                ret
_CallDPMIProtoEntry     endp

_TEXT   ends
        end
