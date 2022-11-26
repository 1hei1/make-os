#include "bootpack.h"
void draw_idt(struct idt_ads *idt,int offset,int selector,int ad) {
	idt->offset_low = offset & 0xffff;
	idt->selectpr = selector;
	idt->dw_count = (ad >> 8) & 0xff;
	idt->access_right = ad & 0xff;
	idt->offset_high = (offset >> 16) & 0xffff;
	return;
}

void draw_gdt(struct gdt_ads* gdt_adss, int limit, int base, int ad) {
	if (limit > 0xfffff) {
		ad |= 0x8000;
		limit /= 0x1000;
	}
	gdt_adss->limit_low = limit & 0xffff;
	gdt_adss->base_low = base & 0xffff;
	gdt_adss->base_mid = (base >> 16) & 0xff;
	gdt_adss->access_right = ad & 0xff;
	gdt_adss->limit_hight = ((limit >> 16) & 0x0f) | ((ad >> 8) & 0xf0);
	gdt_adss->base_high = (base >> 24) & 0xff;
	return;
}

struct fifo jianpan;
struct fifo shubiao1;


void JIANPAN(int* esp) {
	//char *p;
	char date;
	//extern char fontpk[4096];//导入字体库
	//p= (char*)0xa0000;
	//draw_font(300, 60, fontpk + 'A' * 16, p, 8);
	oi_8out(pic0_ocw2, 0x61);
	date = oi_8in(0x0060);
	fifo_put(&jianpan, date);
	return;
}




void shubiao(int *esp){	
oi_8out(0x20,0x67);
return;
}


void shubiaodate(int *esp){	
unsigned char date;
//char *p;
//extern char fontpk[4096];//导入字体库
//p= (char*)0xa0000;
//draw_font(150, 60, fontpk + 'A' * 16, p, 8);

oi_8out(0xa0,0x64);
oi_8out(0x20,0x62);
date = oi_8in(0x60);
fifo_put(&shubiao1, date);



//int fifo8_put(huancong huancongmouse,char date){
//
// huancongmouse.date[huancongmouse.next_w] = date;
//if (huancongmouse.len < 32) {
//	huancongmouse.date[huancong.next_w] = date;
//	huancongmouse.next_w++;
//	huancongmouse.len++;
//	if(huancongmouse.next_w==32){
//		huancongmouse.next_w=0;}
//}
//
//}


}





