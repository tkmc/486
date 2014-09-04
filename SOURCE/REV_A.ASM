;;
;;    rev_a.asm  ( List 13-5 )
;;    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
;;    All rights reserved.
;;
;;    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
;;    プログラムの一部です。プログラム内容や利用方法については本文の
;;    記述を参照してください。
;;

;;
;;    List 13-5  メモリ上のデータを並べ替えるプログラム
;;               [rev_a.asm  1/1] (page 445)
;;

.386

_TEXT   segment byte public use16 'CODE'
        assume  cs:_TEXT

;;************************************************************
;; void reverse_mem(unsigned int sel,
;;         PERSON *base, unsigned long n, unsigned long size);
public          _reverse_mem
_reverse_mem    proc    near
                push    bp
                mov     bp, sp
                push    si
                push    di
                ;
                push    ds
                mov     ds, [bp+4]
                ;
                mov     esi, [bp+6]
                mov     eax, [bp+10]
                dec     eax
                mul     dword ptr [bp+14]
                add     eax, esi
                mov     edi, eax

l1:
                cmp     esi, edi
                jae     r1
                push    edi
                mov     ecx, [bp+14]
l2:
                mov     al, [esi]
                mov     ah, [edi]
                mov     [esi], ah
                mov     [edi], al
                inc     esi
                inc     edi
                dec     ecx
                jnz     l2
                ;
                pop     edi
                sub     edi, [bp+14]
                jmp     l1
r1:
                pop     ds
                pop     di
                pop     si
                pop     bp
                ret
_reverse_mem    endp

_TEXT           ends
                end
