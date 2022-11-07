/* 懠偺僼傽僀儖偱嶌偭偨娭悢偑偁傝傑偡偲C僐儞僷僀儔偵嫵偊傞 */
#include <stdio.h>
void io_hlt(void);
void write(int i, int c);
void oi_8in(int port);
void oi_8out(int port, int date);
void oi_store_eflags(int eflags);
int oi_load_eflags(void);
void init_palette(void);
void oi_cli(void);
void oi_sti(void);
void draw(int x, int y, int bootx, int booty, int ads);
void set_palette(int start, int end, unsigned char* rgb);
void draw_font(int x,int y,char* font,char* vram,int c);
void draw_mouse(int setx,int sety,int a,int b,int c,char * fontpk);
void draw_rout(int x, int y);
void draw_src(int x,int y,char * font,char * ads,int color,char * ads_src);




void HariMain(void)
{
	int i;
	char* p;
	init_palette();

	
	static char font_A[16] = {
		0x00,0x18,0x18,0x18,0x18,0x24,0x24,0x24,0x24,0x7e,0x42,0x42,0x42,0xe7,0x00,0x00
	};

	for (i = 0xa0000; i <= 0xaffff; i++) {
		if (i <= 0xabb80) {
			p = (char*)i;
			*p = 6;
		}

		else {
			p = (char*)i;
			*p = 8;
		}

	}


	draw(60, 160, 50, 20, 0xa0000);
	draw(280, 160, 25, 20, 0xa0000);
	extern char fontpk[4096];
	p= (char*)0xa0000;
	draw_font(20, 20, fontpk+'H'*16,p,6);
	draw_font(30, 20, fontpk + 'S' * 16, p, 6);

	draw_font(40, 20, fontpk + 'J' * 16, p, 6);

	draw_font(50, 20, fontpk + 'S' * 16, p, 6);

	draw_font(60, 20, fontpk + 's' * 16, p, 6);



char m[500];
sprintf(m,"name=%dhahaha      hhhhh    @@@@@    &&&&&","123haha40");
draw_src(0,48,fontpk,p,6,m);

draw_mouse(50,60,6,6,6,fontpk);
draw_rout(60, 20);


	for (;;) {
		io_hlt();
	}



}



void draw(int x, int y, int bootx, int booty,int ads) {

	int i = ads;
	int rember = bootx;
	int start = 320 * y + x+i;
	char *p;
	for (; booty >= 0; booty-=1) {
		p = (char*)start;
		for (; bootx >= 0; bootx-=1) {
			
			p[bootx] = 2;
			
			
		
		}
		bootx = rember;
		start += 320;
	}



}/*绘制屏幕*/






void init_palette(void) {
	static unsigned char table_rgb[16 * 3] = {
		0x00,0x00,0x00,//black
		0xff,0x00,0x00,//red
		0xff,0xff,0x00,//green
		0xff,0xff,0x00,//yellow
		0x00,0x00,0xff,//blue
		0xff,0x00,0xff,//puple
		0x00,0xff,0xff,//light blue
		0xff,0xff,0xff,//white
		0xc6,0xc6,0xc6,//light black
		0x84,0x00,0x00,//dark red
		0x00,0x84,0x00,//drak green
		0x84,0x84,0x00,//drak yellow
		0x00,0x00,0x84,//drak green
		0x00,0x84,0x84,//light drak blue
		0x84,0x84,0x84,//drak light black
		0x84,0x00,0x84//drak pople
	};
	set_palette(0, 15, table_rgb);
	return;
}/*初始化画板*/
void set_palette(int start, int end, unsigned char* rgb) {


	int i, eflags;
	eflags = oi_load_eflags();
	oi_cli();
	oi_8out(0x03c8, start);
	for (i = start; i <= end; i++) {
		oi_8out(0x03c9, rgb[0]);
		oi_8out(0x03c9, rgb[1]);
		oi_8out(0x03c9, rgb[2]);
		rgb += 3;
	}
	oi_store_eflags(eflags);
	return;

}/*设置画板*/


void draw_font(int x, int y, char* font, char* vram,int c) {
	int n;

	for (n = 0; n < 16; n++) {
		int d = font[n];
		
	if ((d & 0x80) != 0){
		vram[x + y * 320 + n * 320] = c;
	}
	if ((d & 0x40) != 0){
	vram[x + y * 320 + n * 320+1] = c;
	}
	if ((d & 0x20) != 0){
	vram[x + y * 320 + n * 320+2] = c;
	}
	if ((d & 0x10) != 0){
	vram[x + y * 320 + n * 320+3] = c;
	}
	if ((d & 0x08) != 0){
	vram[x + y * 320 + n * 320+4] = c;
	}
	if ((d & 0x04) != 0){
	vram[x + y * 320 + n * 320+5] = c;
	}
	if ((d & 0x02) != 0){
	vram[x + y * 320 + n * 320+6] = c;
	}
	if ((d & 0x01) != 0){
	vram[x + y * 320 + n * 320+7] = c;
	}
	}
	return;
}/*绘制字符*/


void draw_src(int x,int y,char * fontpk,char * ads,int color,char * ads_src){

for (;*ads_src!=0;ads_src++) {
	draw_font(x, y, fontpk + (*ads_src) * 16, ads, color);
	x += 8;
	if (x == 312) {
		y += 16;
		x = 0;
	}
}}


/*绘制字符串*/

void draw_mouse(int setx,int sety,int a,int b,int c,char * fontpk){
char *ads = 0xa0000;
char m[256];
char mouse[16][16] = {
"**************..",
"*00000000000*...",
"*0000000000*....",
"*000000000*.....",
"*0000.000*......",
"*0000000*.......",
"*..0..00*.......",
"*...00000*......",
"*000000000*.....",
"*0000000000*....",
"*0000000.000*...",
"*.........000*..",
"*..........000*.",
"*...........000.",
",,,,,,,,,,,,,,,,",
"0000000000000000"

};
int x,y;
for (y=0;y<16;y++){
for(x=0;x<16;x++){
if (mouse[y][x] == '*'){
ads[setx+sety*320+x] = 6;}
if (mouse[y][x] == '0'){ /*此处只能用单引号否则不能执行判断条件*/
ads[setx+sety*320+x] = 8;}
if (mouse[y][x] == '.'){
ads[setx+sety*320+x] = 6;}


};char mtest[590];
sprintf(mtest,"hanizhen6");
draw_src(80,80,fontpk,ads,6,mtest);
draw_src(80,80,fontpk,ads,6,mtest);
sety +=1;}
/*char mtest[590];
sprintf(mtest,"hanizhen6");
draw_src(80,80,fontpk,ads,6,mtest);*/
}

void draw_rout(int x, int y) {
	char rout[16][16] = {
"**************..",
"*00000000000*...",
"*0000000000*....",
"*00.....00*.....",
"*0000.000*..0...",
"*0000000*..000..",
"*..0..00*..000..",
"*...00000*......",
"*......000*.....",
"*...0...000*....",
"*...0....000*...",
"*...0.....000*..",
"*...0000...000*.",
"*...........000.",
",,,,,,,,,,,,,,,,",
"0000000000000000"

	};
	char* ads = 0xa0000;
	int l_x, l_y;
	for (l_y = 0; l_y < 16; l_y++) {
		for (l_x = 0; l_x < 16; l_x++) {
			if (rout[l_y][l_x] == '*') {
				ads[x + y * 320 + l_x] = 6;
			}
			if (rout[l_y][l_x] == '0') {
				ads[x + y * 320 + l_x] = 8;
			}
			if (rout[l_y][l_x] == '.') {     /*此处只能用单引号否则不能执行判断条件*/
				ads[x + y * 320 + l_x] = 6;
			}
		}y += 1;
		
	}
}
