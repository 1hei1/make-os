TOOLPATH = ../qemu1/
INCPATH  = ../qemu1/cll/
nask 	=$(TOOLPATH)nask.exe
EDIMG    = $(TOOLPATH)edimg.exe
MAKE     = $(TOOLPATH)make.exe -r
cc1      = $(TOOLPATH)cc1.exe -I$(INCPATH) -Os -Wall -quiet
gas2nask		=$(TOOLPATH)gas2nask.exe
obj2bim		=$(IOOLPATH)obj2bim.exe
bim2hrb		=$(IOOLPATH)bim2hrb.exe
bin2obj       =$(TOOLPATH)bin2obj.exe
makefont      =$(TOOLPATH)makefont.exe
RULEFILE = $(TOOLPATH)cll/haribote.rul


COPY     = copy


bootpack.gas:bootpack.c Makefile
		$(cc1) -o    bootpack.gas  bootpack.c
bootpack.nas: bootpack.gas Makefile
		$(gas2nask)   bootpack.gas  bootpack.nas
bootpack.obj:bootpack.nas Makefile
		$(nask)    bootpack.nas  bootpack.obj
ospack.obj:ospack.nas Makefile
		$(nask)		ospack.nas  ospack.obj
fontpack.bin:fontpack.txt Makefile
		$(makefont) 	fontpack.txt  fontpack.bin
fontpack.obj:fontpack.bin Makefile
		$(bin2obj)   fontpack.bin fontpack.obj _fontpk   
		
bootpack.bim :FIFO.obj bootpack.obj ospack.obj fontpack.obj gdt_idt.obj draw.obj int.obj memorymanger.obj test.obj Makefile
	$(obj2bim) @$(RULEFILE) out:bootpack.bim stack:3136k map:bootpack.map \
		bootpack.obj ospack.obj fontpack.obj gdt_idt.obj draw.obj int.obj memorymanger.obj FIFO.obj test.obj

bootpack.hrb: bootpack.bim Makefile
		$(bim2hrb) bootpack.bim bootpack.hrb 0
os.sys : screen.bin bootpack.hrb Makefile
	copy /B screen.bin+bootpack.hrb os.sys


screen.bin:screen.nas Makefile
		$(nask)   screen.nas  screen.bin

day1.bin: day1.nas Makefile
		$(nask)   day1.nas   day1.bin
ospack.bin:
		$(nask)	ospack.nas    ospack.bin

haribote.img : day1.bin os.sys Makefile
	$(EDIMG)   imgin:../qemu1/fdimg0at.tek \
		wbinimg src:day1.bin len:512 from:0 to:0   copy from:os.sys to:@: \
  imgout:haribote.img



%.gas : %.c Makefile
	$(cc1) -o $*.gas $*.c

%.nas : %.gas Makefile
	$(gas2nask) $*.gas $*.nas

%.obj : %.nas Makefile
	$(nask) $*.nas $*.obj
img :
	$(MAKE) haribote.img



run :
	$(MAKE) img
	$(COPY) haribote.img ..\qemu1\qemu\fdimage0.bin
	$(MAKE) -C ../qemu1/qemu








