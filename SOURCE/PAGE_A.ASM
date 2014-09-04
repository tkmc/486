;;
;;    page_a.asm  ( List 9-5, 9-6, 9-12, 9-16 )
;;    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
;;    All rights reserved.
;;
;;    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
;;    プログラムの一部です。プログラム内容や利用方法については本文の
;;    記述を参照してください。
;;

;;
;;    List 9-5  レジスタCR3にアドレスを設定するlcr3()関数
;;              [page_a.asm  1/4] (page 316)
;;

.386p

_TEXT   segment byte public use16 'CODE'
        assume  cs:_TEXT

;;************************************************************
;; void lcr3(unsigned long PageDirAddr);
public          _lcr3
_lcr3           proc    near
                push    bp
                mov     bp,sp
                mov     eax,[bp+4]
                mov     cr3,eax
                pop     bp
                ret
_lcr3           endp

;;
;;    List 9-6  PGビットをセットするPagingStart()関数と
;;                      PGビットをリセットするPagingStop()関数
;;              [page_a.asm  2/4] (page 318)
;;
;;************************************************************
;; void PagingStart(void);
public          _PagingStart
_PagingStart    proc    near
                mov     eax,cr0
                or      eax,80000000h
                mov     cr0,eax
                ret
_PagingStart    endp

;;************************************************************
;; void PagingStop(void);
public          _PagingStop
_PagingStop     proc    near
                mov     eax,cr0
                and     eax,7fffffffh
                mov     cr0,eax
                ret
_PagingStop     endp

;;
;;    List 9-12  ページフォルトハンドラPageFault()関数
;;               [page_a.asm  3/4] (page 325)
;;
;;************************************************************
;; void PageFault(void);
public          _PageFault
extrn           _PageFaultHandler:near
_PageFault      proc    near
                push    ds
                push    es
                pushad
                mov     ax,10h
                mov     ds,ax
                mov     es,ax
                mov     eax,cr2
                push    eax
                call    _PageFaultHandler
                add     sp,4
                popad
                pop     es
                pop     ds
                add     sp,4    ; remove error code
                iretd
_PageFault      endp

;;
;;    List 9-16  TLBをフラッシュさせるFlushTLB()関数
;;               [page_a.asm  4/4] (page 330)
;;
;;************************************************************
;; void FlushTLB(void);
public          _FlushTLB
_FlushTLB       proc    near
                mov     eax,cr3
                mov     cr3,eax
                ret
_FlushTLB       endp

_TEXT           ends
                end
