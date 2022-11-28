#include "bootpack.h"

void drawnormal(int x, int y, int x1,int y1,int bootx,char *ads,int c){
int i,j;
for (i=y;i<y1;i++){
	for(j=x;j<x1;j++){
		ads[bootx*i+j]=c;
	}
}
}




void draw(int x, int y,int bootx,int booty,int *ads,int c){





	int i = ads;
	int rember = bootx;
	int start = 320 * y + x+i;
	char *p;
	for (; booty >= 0; booty-=1) {
		p = (char*)start;
		for (; bootx >= 0; bootx-=1) {
			
			ads[bootx] = c;
			
			
		
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

void drawnormal_font(int x, int y,int xsize, char font, char* vram,int c) {
	int n;
	extern char fontpk[4096];
	char *p;
	p=fontpk+font*16;
	for (n = 0; n < 16; n++) {
		int d = p[n];
		
	if ((d & 0x80) != 0){
		vram[x +(y+n)*320] = c;                          //绘制字符时控制绘制字符的draw—font只负责绘制判断换行交给draw—src
	}
	if ((d & 0x40) != 0){                             //需要注意的是draw——font在屏幕上绘制字符，并不是在对应的图层绘制因此being不能用xsize来进行绘制
	vram[x + (y+n)*320+1] = c;
	}
	if ((d & 0x20) != 0){
	vram[x + (y+n)*320+2] = c;
	}
	if ((d & 0x10) != 0){
	vram[x + (y+n)*320+3] = c;
	}
	if ((d & 0x08) != 0){
	vram[x + (y+n)*320+4] = c;
	}
	if ((d & 0x04) != 0){
	vram[x + (y+n)*320+5] = c;
	}
	if ((d & 0x02) != 0){
	vram[x + (y+n)*320+6] = c;
	}
	if ((d & 0x01) != 0){
	vram[x + (y+n)*320+7] = c;
	}
	}
	return;
}/*绘制字符*/




void draw_src(int x, int y, char* fontpk, char* ads, int color, char* ads_src) {

for (;*ads_src!=0;ads_src++) {
	draw_font(x, y, fontpk + (*ads_src) * 16, ads, color);
	x += 8;
	if (x == 312) {
		y += 16;
		x = 0;
	}
}}


void drawnormal_src(int x, int y,int xsize, char* ads, int color,unsigned char* ads_src) {

for (;*ads_src!=0;ads_src++) {
	drawnormal_font(x, y,xsize, *ads_src, ads, color);//
	x += 8;
	if (x >= xsize-8) {
		y += 16;
		x = 0;
	}
}}

/*绘制字符串*/

void draw_mouse(int setx, int sety, int a, int b, int c, char* fontpk,unsigned int *ads) {
	//char* ads = 0xa0000;
	char m[256];
	char mouse[16][16] = {
	"**************..",
	"*00000000000*...",
	"*0000000000*....",
	"*000000000*.....",
	"*00000000*...0..",
	"*0000000*....0..",
	"*..00000*....0..",
	"*...00000*...0..",
	"*0000..000*.....",
	"*00....0000*....",
	"*0000000.000*...",
	"*.........000*..",
	"*..........000*.",
	"*...........000.",
	"................",
	"0000000000000000"

	};
	int x, y,n;
	n=0;
	for (y = 0; y < 16; y++) {
		for (x = 0; x < 16; x++) {
			if (mouse[y][x] == '*') {
				ads[n] = a;
				n+=1;
			}
			if (mouse[y][x] == '0') {
				ads[n] = b;
				n+=1;
			}
			if (mouse[y][x] == '.') {
				ads[n] = c;
				n+=1;
			}


		}; 
		
	}
	//draw_src(80, 80, fontpk, ads, 6, mtest);
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
"................",
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
			if (rout[l_y][l_x] == '.') {
				ads[x + y * 320 + l_x] = 6;
			}
		}y += 1;
		
	}
};



void draw_windows_content(char* ads,struct contents* content,int xsize,int ysize,char c){
	int i,j,x,y,n=0;
	char*p;
	char*q;
	extern char fontpk[4096];

    for (i=0;i<ysize;i++){
	for(j=0;j<xsize;j++){
		ads[n]=c;
		n++;
	}
}
	n=0;
	p=content->ads;
	q=fontpk;
	x=content->x;
	y=content->y;
	
	/*for(;;){
		if(p[n]!=0){
			for(i=0;i<16;i++){
				
					if(q[p[n]*16]&&0x80!=0){
						ads[x+y*xsize+0+i*xsize]=2;
					}
					if(q[p[n]*16]&&0x40!=0){
						ads[x+y*xsize+1+i*xsize]=2;
					}
					if(q[p[n]*16]&&0x20!=0){
						ads[x+y*xsize+2+i*xsize]=2;
					}
					if(q[p[n]*16]&&0x10!=0){
						ads[x+y*xsize+3+i*xsize]=2;
					}
					if(q[p[n]*16]&&0x8!=0){
						ads[x+y*xsize+4+i*xsize]=2;
					}
					if(q[p[n]*16]&&0x4!=0){
						ads[x+y*xsize+5+i*xsize]=2;
					}
					if(q[p[n]*16]&&0x2!=0){
						ads[x+y*xsize+6+i*xsize]=2;
					}
					if(q[p[n]*16]&&0x1!=0){
						ads[x+y*xsize+7+i*xsize]=2;
					}test1(0,150,80);



			

		};n++;
		x+=8;


		}
		else{
			test1(88,150,80);
			break;
		}
	}*/



}
