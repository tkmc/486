;;
;;    task_a.asm  ( List 8-3, 8-4 )
;;    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
;;    All rights reserved.
;;
;;    このファイルは『はじめて読む486』（アスキー出版局）に掲載した
;;    プログラムの一部です。プログラム内容や利用方法については本文の
;;    記述を参照してください。
;;

;;
;;   List 8-3  セグメント間ジャンプ命令によって
;;                     タスクを切り替えるSwitchTask()関数
;;             [task_a.asm  1/2] (page 276)
;;

.386p
_TEXT   segment byte public use16 'CODE'
        assume  cs:_TEXT

;;************************************************************
;; void SwitchTask(unsigned short sel);
public   _SwitchTask
_SwitchTask     proc near
                push    bp
                mov     bp,sp
                jmp     dword ptr [bp+2]
                ;
                pop     bp
                ret
_SwitchTask     endp

;;
;;   List 8-4  TRレジスタにセレクタ値を設定するltr()関数
;;             [task_a.asm  2/2] (page 279)
;;
;;************************************************************
;; void ltr(unsigned short sel);

public          _ltr
_ltr            proc    near
                push    bp
                mov     bp,sp
                ltr     word ptr [bp+4]
                pop     bp
                ret
_ltr            endp

_TEXT           ends
                end
