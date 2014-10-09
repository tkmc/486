# Makefile for MASM bundled with MS Visual Studio.
#
# Usage: nmake -f Makefile.VS
#
# Tested with VS2010 and VS2012 only.

ASMSRC	= DISP_A.ASM DPMI_A.ASM GPE_A.ASM INT_A.ASM IOEMU_A.ASM PAGE_A.ASM \
	  PROTO0_A.ASM PROTO_A.ASM REV_A.ASM SIEVE_A.ASM TASK_A.ASM \
	  TRANS_A.ASM V86_A.ASM

AFLAGS	= /nologo /omf

ASMOBJ	= $(ASMSRC:.ASM=.OBJ)

default: $(ASMOBJ)

clean:
	-DEL /F /Q $(ASMOBJ)

.asm.obj:
	$(AS) $(AFLAGS) /c $<
