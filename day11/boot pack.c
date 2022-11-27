/////////////////////////////////////////////////////////
/////////         千万不要搞错指针类型           //////////
/////////                                      //////////
/////////////////////////////////////////////////////////






#include <stdio.h>
#include "bootpack.h"
extern struct fifo jianpan;
extern struct fifo shubiao1;
struct memorymanger1 memorymanger;//memorymanger声明必须写在外面不然包allocd错误



//int shubiaojianpan(struct fifo jianpan, struct fifo shubiao1, int mousex, int mousey, unsigned char date, struct date1 date1, struct mousemove mmv, char fontpk) {


void HariMain(void)
{
	init_pic();//初始化pic（中断控制器）
	oi_sti();//启用中断

	struct gdt_ads* gdt_adss = (struct gdt_ads*)0x00270000;    //设置gdt表起始地址
	struct idt_ads* idt_adss = (struct idt_ads*)0x0026f800;    //设置idt表其实地址
	extern char fontpk[4096];
	int i;
	int s[200];
	char s1[3];
	char moused[200];
	unsigned char k[64];
	unsigned char mmb[320];
	unsigned int mousess[256];
	draw_mouse(0,0,8,8,8,fontpk,&mousess);//绘制鼠标形状
	char mtest[625];
	struct contents mmmm;
	char opq[20]={1,2,3};
	mmmm.x=0;
	mmmm.y=0;
	mmmm.ads=opq;
	
	
	


	fifo_init(&jianpan, 64, &k);		//键盘缓冲区设置
	fifo_init(&shubiao1, 320, &mmb);     //鼠标缓冲区设置                              

	char* p;
	init_palette();//初始化画板
	oi_8out(0x03c7,0);
	
	////////////////////////////////////////////////////////////////////////////////////////
	for (i = 0; i < 8192; i++) {
		draw_gdt(gdt_adss + i, 0, 0, 0);
	}//将8192个段描述符初始化为0
		draw_gdt(gdt_adss + 1, 0xffffffff, 0x00000000, 0x4092);
		draw_gdt(gdt_adss + 2, 0x0007ffff, 0x00280000, 0x409a);                                                                //
	gdt_save(0xffff, 0x00270000);//将段描述符表地址存入寄存器中

	for (i = 0; i < 256; i++) {
		draw_idt(idt_adss + i, 0, 0, 0);
	};//将256个中断向量描述符初始化为0                    

	draw_idt(idt_adss + 0x21, (int)asm_inthandler, 2 * 8, 0x008e);
	draw_idt(idt_adss + 0x27, (int)asm_inthandler27, 16, 0x008e);
	draw_idt(idt_adss + 0x2c, (int)asm_inthandler2c, 16, 0x008e);
	idt_save(0x7ff, 0x0026f800);//将中断向量表地址存入寄存器中




	/////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////////
	for (i = 0xa0000; i <= 0xaffff; i++) {
		if (i <= 0xabb80) {
			p = (char*)i;
			*p = 6;
		}                                                             //绘制屏幕上

		else {
			p = (char*)i;
			*p = 6;
		}                                                              //绘制屏幕下

	}


	char atest[20];
	sprintf(atest,"ok");
	draw(60, 160, 50, 20, 0xa0000, 8);                                  //绘制方框
	draw(280, 160, 50, 50, 0xa0000, 8);
	drawnormal(100,100,135,135,320,0xa0000,3);
	drawnormal(100,100,135,105,320,0xa0000,4);
	drawnormal(100,100,105,135,320,0xa0000,7);
	drawnormal_src(115,115,320,0xa0000,8,atest);
	//drawnormal(0,0,50,50,320,0xa0000,2);
	//draw_windows_content(mtest,&mmmm,25,25,2);//除数组外其他都要加&
	//test1(mtest[100],180,80);
	///////////////////////////////////////////////////////////////////////////////////////////////
	extern char fontpk[4096];                                         //导入字体库
	p = (char*)0xa0000;
	
	                                               //
	draw_font(20, 20, fontpk + 'H' * 16, p, 6);         //
	draw_font(30, 20, fontpk + 'S' * 16, p, 6);        //
	
	draw_font(40, 20, fontpk + 'J' * 16, p, 6);        //

	draw_font(50, 20, fontpk + 'S' * 16, p, 6);        //

	draw_font(60, 20, fontpk + 's' * 16, p, 6);        //绘制字符

	//draw_font(300, 20, fontpk + ok+1, p, 8);  	

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	int memory_size = memory_mgr(0x00400000, 0xbfffffff);
	char m0[30];
	sprintf(m0, "%dMB", memory_size / (1024 * 1024));           //输出内存大小
	draw_src(0, 150, fontpk, p, 8, m0);
	memorymanger_init(&memorymanger);
	int stuat1=memory_free(&memorymanger, 0x00001001, 0x0009e000);
	int stuat2=memory_free(&memorymanger, 0x00400000, memory_size - 0x00400000);//增加两条空间剩余记录
	struct manger_windows *mws = windows_init(&memorymanger,0xa0000,320,200);//初始化图层控制模块
	struct windows_content *back=windows_allow(mws);
	struct windows_content *mouse=windows_allow(mws);
	struct windows_content *test=windows_allow(mws);
	struct windows_content *test2=windows_allow(mws);//添加图层
	windows_set(back,mtest,25,25,30,20,2);
	windows_set(mouse,mousess,16,16,30,90,2);
	windows_set(test,mtest,80,100,80,80,2);
	windows_set(test2,mtest,80,100,80,80,2);//设置图层信息
	test1(mtest[624],120,80);
	windows_update(mws,test,0);
	windows_update(mws,test2,1);
	windows_update(mws,back,2);//图层更新入图层管理模块
	windows_update(mws,mouse,3);
	
	//test1(mws->top,100,80);
	/// ///////////////////////////////////////////////////////////////////////////////////
	//char m[500];
	//sprintf(m, "name=%dhahahahhhhh@@@@@&&&&&123h%oaha40%d");           //½«×Ö·û´®±£´æµ½mÖÐ
	//draw_src(0, 100, fontpk, p, 8, m);   
	//char atest[10];      
	//sprintf(atest,"ok%d",996);                          //»æÖÆ×Ö·û´®
	//drawnormal_src(30,20,320,0xa0000,8,atest);
	//drawnormal_font(30,20,320,'A',0xa0000,8);

	//draw_mouse(50, 60, 6, 6, 6, fontpk);                             //»æÖÆÊó±êÐÎ×´
	draw_rout(60, 20);
	oi_8out(pic0_imr, 0xf9);                                          //随意绘制的图层
	oi_8out(pic1_imr, 0xef);             //禁用所有中断（imr为屏蔽寄存器）
	init_jianpan();
	enable_mouse();                      //激活鼠标，键盘控制模块

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	struct date1 {
		unsigned char datearray[3];
		int number;
	};
	struct mousemove {
		int btn, x, y
	};
	struct mousemove mmv;
	struct date1 date1;

	unsigned char date;
	int mousex, mousey;
	mousex = 50;
	mousey = 60;
	int numbe=1;
	oi_sti();
	for (;;)

	{
		//shubiaojianpan(jianpan, shubiao1, mousex, mousey, date, date1, mmv, fontpk);

		                                               
			if (64 - (jianpan.free) != 0) {
				oi_cli();
				date = jianpan.date[jianpan.q];

				if (jianpan.q < 64) {
					jianpan.q++;
					jianpan.free++;
					oi_sti();
					sprintf(s, "%02x", date);
					drawnormal(0, 0, 30, 30,320, 0xa0000, 2);
					draw_src(0, 0, fontpk, 0xa0000, 8, s);
				}
				else {
					jianpan.q = 0;
					oi_sti();
				}




			}
			else if (320 - (shubiao1.free) != 0) {
				date = shubiao1.date[shubiao1.q];
				if (shubiao1.q < 320) {
					if (date == 0xfa) {
						date1.number = 1;
						shubiao1.q++;
						shubiao1.free++;
						oi_sti();

					}
					else if (date1.number == 1) {

						shubiao1.q++;
						shubiao1.free++;
						oi_sti();
						if ((date & 0xc8) == 0x08) {             //ÅÐ¶ÏÊó±êµÚÒ»¸öÊý¾ÝÊÇ·ñÕýÈ·

							date1.datearray[0] = date;

							date1.number = 2;
						}




					}
					else if (date1.number == 2) {
						shubiao1.q++;
						shubiao1.free++;
						oi_sti();
						date1.datearray[1] = date;
						date1.number = 3;

					}
					else if (date1.number == 3) {
						shubiao1.q++;
						shubiao1.free++;
						oi_sti();
						drawnormal(mousex, mousey,mouse+16,mousey+16,320, 0xa0000, 6);
						date1.datearray[2] = date;
						mmv.btn = date1.datearray[0] & 0x07;
						mmv.y = date1.datearray[2];
						mmv.x = date1.datearray[1];
						if ((date1.datearray[0] & 0x10) != 0) {
							mmv.x |= 0xffffff00;
						}
						if ((date1.datearray[0] & 0x20) != 0) {
							mmv.y |= 0xffffff00;
						}
						mmv.y = -mmv.y;
						mousex += mmv.x;
						mousey += mmv.y;
						if (mousex < 0) {
							mousex = 0;
						}
						if (mousey < 0) {
							mousey = 0;
						}
						if (mousex >= 304) {
							mousex = 304;
						}
						if (mousey >= 184) {
							mousey = 184;
						}

						//windows_update(mws,mouse,0);
						
						
						//draw_mouse(mousex, mousey, 2, 5, 8, fontpk);
						//movemouse(mmv.x,mmv.y,mousex,mousey,fontpk);
						sprintf(moused, "%02x %4d %4d", date1.datearray[0], mmv.x, mmv.y);

						
						drawnormal(40, 0, 150, 30,320, 0xa0000, 2);
						draw_src(40, 0, fontpk, 0xa0000, 8, moused);
						
						
						//windows_set(mouse,&mousess,16,16,mousex,mousey,2);//指针类型不能写错了，不然一次写入的数据大小不确定。（改了一天）
						date1.number = 1;
						drawnormal(mousex,mousey,mousex+16,mousey+16,320,0xa0000,2);
						
						//windows_refresh(mws,mousex,mousey,&mmv);//注意区分地址
						continue;

					}



					//moused[date1.number] = date;


				
				
			
			}
			else {
				shubiao1.q=0;
				oi_sti();
			}
		
		
		

	}
}}
////////////////////////////////////////////////////////////////////////////////////////

void wait_kbc(void){                           //ÅÐ¶Ï¼üÅÌ×´Ì¬
for(;;){
if((oi_8in(0x0064)&0x02)==0){
break;}
}
return;
}

void init_jianpan(){
wait_kbc();
oi_8out(0x64,0x60);
wait_kbc();
oi_8out(0x60,0x47);
return;//键盘控制模块激活
}



void enable_mouse(){
wait_kbc();
oi_8out(0x64,0xd4);
wait_kbc();
oi_8out(0x60,0xf4);
return;
};//鼠标控制模块激活
//int movemouse(int x,int y,int mousex,int mousey,int fontpk) {
//	mousex += x;
//	mousey += y;
//
//	//mmv.y = -mmv.y;
//	if (mousex < 0) {
//		mousex = 0;
//	}
//	if (mousey < 0) {
//		mousey = 0;
//	}
//	if (mousex >= 304) {
//		mousex = 304;
//	}
//	if (mousey >= 184) {
//		mousey = 184;
//	}
//
//
//
//	draw_mouse(mousex, mousey, 8, 8, 8, fontpk);
//	return mousex, mousey;
//}
