;;
;;    int_a.asm  ( List 7-1, 7-3, 7-4, 7-10, 7-11, 7-13 )
;;    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
;;    All rights reserved.
;;
;;    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
;;    プログラムの一部です。プログラム内容や利用方法については本文の
;;    記述を参照してください。
;;

;;
;;    List 7-1  IDTRに値を設定するlidt()関数
;;              [int_a.asm  1/6] (page 242)
;;

.386p
_TEXT   segment byte public use16 'CODE'
        assume  cs:_TEXT

;;************************************************************
;; void lidt(DescTblPtr *idtptr);
public          _lidt
_lidt           proc    near
                push    bp
                mov     bp,sp
                cli
                mov     bx,[bp+4]
                lidt    fword ptr [bx]
                pop     bp
                ret
_lidt           endp

;;************************************************************
;;
;;    List 7-3  割り込み処理ルーチンの定義
;;              [int_a.asm  2/6] (page 245)
;;
;; void i0(void),i1(void),...,i255(void);

IntEntry        macro   n
                public  _i&n
_i&n            proc
                push    n
                jmp     IntCaller
_i&n            endp
endm

                i=0
rept            256     ; for TASM
;repeat         256     ; for MASM
                IntEntry %i
                i=i+1
endm
_TEXT ends

;;
;;    List 7-4  割り込みの共通的な処理を行うIntCaller()関数
;;              [int_a.asm  3/6] (page 245)
;;

DGROUP  group   _DATA,_BSS
        assume ds:DGROUP
_DATA   segment word public use16 'DATA'
_DATA   ends
_BSS    segment word public use16 'BSS'
                extrn   _IntHandler:word
_BSS    ends
_TEXT   segment byte public use16 'CODE'
                extrn   _GPEHandler:near
;;************************************************************
;; interrupt entry
IntCaller       proc
                push    ds
                push    es
                pusha
                mov     ax,10h
                mov     ds,ax
                mov     es,ax
                call    _IntHandler
                popa
                pop     es
                pop     ds
                add     esp,2
                iretd
intCaller       endp

;;************************************************************
;;
;;    List 7-10  割り込みを禁止するDisableInterrupt()関数
;;               [int_a.asm  4/6] (page 252)
;;
;; void DisableInterrupt(void);

public          _DisableInterrupt
_DisableInterrupt       proc    near
                cli
                ret
_DisableInterrupt       endp

;;************************************************************
;;
;;    List 7-11  割り込みを許可するEnableInterrupt()関数
;;               [int_a.asm  5/6] (page 252)
;;
;; void EnableInterrupt(void);

public          _EnableInterrupt
_EnableInterrupt        proc    near
                sti
                ret
_EnableInterrupt        endp

;;************************************************************
;;
;;    List 7-13  一般保護例外に対応するGPEFault()関数
;;               [int_a.asm  6/6] (page 256)
;;
;; General Protection Error Fault entry
public          _GPEFault
_GPEFault       proc near
                push    ds
                push    es
                pusha
                mov     ax,10h
                mov     ds,ax
                mov     es,ax
                call    _GPEHandler
                popa
                pop     es
                pop     ds
                add     esp,2
                iretd
_GPEFault       endp

_TEXT           ends
                end
