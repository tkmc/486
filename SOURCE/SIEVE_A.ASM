;;
;;    sieve_a.asm  ( List 5-28 )
;;    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
;;    All rights reserved.
;;
;;    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
;;    プログラムの一部です。プログラム内容や利用方法については本文の
;;    記述を参照してください。
;;

;;
;;    List 5-28  32ビット命令を活用するアセンブリ言語プログラムsieve
;;               [sieve_a.asm  1/1] (page 184)
;;

.386

DGROUP  group   _DATA

_TEXT32 segment byte public use32 'CODE'
        assume  cs:_TEXT32


;;************************************************************
;; void sieve(unsigned short tblsel, unsigned long num)
public          _sieve
_sieve          proc    far
                push    bp
                mov     bp,sp
                push    ds
                ;
                mov     ds,[bp+6]
                ;
                xor     ebx,ebx
                mov     ecx,[bp+8]
l1:             mov     byte ptr [ebx], 1
                inc     ebx
                cmp     ebx, ecx
                jbe     l1
                ;
                mov     ecx,[bp+8]
                mov     edx,ecx
                shr     edx,1
                mov     ebx,2
l2:
                cmp     byte ptr [ebx],1
                jne     s1

                mov     eax,ebx
l3:
                lea     eax,[ebx+eax]
                cmp     eax,ecx
                ja      s1
                mov     byte ptr [eax],0
                jmp     l3
s1:
                inc     ebx
                cmp     ebx,edx
                jbe     l2

                pop     ds
                pop     bp
                db      66h
                ret
_sieve          endp

;;************************************************************
;; int isprime(unsigned short tblsel, unsigned long num)
public          _isprime
_isprime        proc    far
                push    bp
                mov     bp,sp
                push    ds
                ;
                mov     ds,[bp+6]
                ;
                mov     ebx,[bp+8]
                mov     ah, 0
                mov     al,[ebx]
                ;
                pop     ds
                pop     bp
                db      66h
                ret
_isprime        endp

_TEXT32         ends


_DATA   segment word public use16 'DATA'

public  _csseg32
_csseg32        dw      _TEXT32

_DATA           ends

                end
