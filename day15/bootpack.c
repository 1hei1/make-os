/////////////////////////////////////////////////////////
/////////         千万不要搞错指针类型           //////////
/////////                                      //////////
/////////////////////////////////////////////////////////
////////现在的drawnaormal（）可以根据首地址，尾地址绘制背景色块//////////////
////////现在的drawnormal—src（）可以根据首地址，窗口宽度来绘制色块///////////
////////首地址是根据图层的首地址计算来的               /////////////////////






#include <stdio.h>
#include "bootpack.h"
extern struct fifo jianpan;
extern struct fifo shubiao1;
struct memorymanger1 memorymanger;//memorymanger声明必须写在外面不然包allocd错误
void tetsnnb();
struct time_manger time_manger;
//int shubiaojianpan(struct fifo jianpan, struct fifo shubiao1, int mousex, int mousey, unsigned char date, struct date1 date1, struct mousemove mmv, char fontpk) {
int count=0;
int minute=23;
char nop[20000];
char test_win[400];
void HariMain(void)
{
	init_pic();//初始化pic（中断控制器）
	oi_sti();//启用中断

	struct gdt_ads* gdt_adss = (struct gdt_ads*)0x00270000;    //设置gdt表起始地址
	struct idt_ads* idt_adss = (struct idt_ads*)0x0026f800;    //设置idt表其实地址

	extern char fontpk[4096];
	int i;
	

	char s[200];
	char s1[3];
	char moused[200];
	unsigned char k[64];
	unsigned char mmb[320];
	unsigned int mousess[256];
	unsigned int layer_content_ads[80];
	sprintf(layer_content_ads,"NUMBER1OKOKOOKOOOKOOOOK");
	//draw_mouse(0,0,8,8,8,fontpk,&mousess);//绘制鼠标形状
	struct layer_content mtest;
	mtest.x=20;
	mtest.y=20;
	mtest.ads=layer_content_ads;
	///////////////////////////////////////////////
	struct layer_backs layer_backs;//管理一个图层的所有块的结构体
	layer_backs.blocks=3;//设置图层快书
	struct block block1;
	block1.x=0;
	block1.y=0;
	block1.x1=120;
	block1.y1=30;
	block1.c=2;
	struct block block2;
	block2.x=120;
	block2.y=0;
	block2.x1=160;
	block2.y1=30;
	block2.c=6;
	struct block block3;//每块图层快的具体信息（位置，颜色）
	block3.x=0;
	block3.y=16;
	block3.x1=160;
	block3.y1=100;
	block3.c=0;
	layer_backs.content[0]=&block1;
	layer_backs.content[1]=&block2;
	layer_backs.content[2]=&block3;//设置图层块
	///////////////////////////////////////////////

	drawnormal(0,0,100,100,100,nop,0);
	char content_test[100];
	sprintf(content_test,"",123);
	drawnormal(0,50,20,60,200,nop,12);
	drawnormal_src(0,20,200,nop,2,content_test);
	char mouse_map[256];
	draw_rout(0,0,mouse_map);


	///////////////////////////////////////////////////////////////////////////
	unsigned char time1_fifo_ads[6];
	struct fifo time_fifo;
	fifo_init(&time_fifo,6,&time1_fifo_ads);
	time_manger_init(&time_manger);
	struct time *time1= time_alloc(&time_manger);
	time_set(&time_manger,time1,&time_fifo,4);//首先声明计时器总管，在设置缓冲区，缓冲区管理，申请一个计时器，设置计时器的缓冲区，超时时间，，最后调用开始计时

	unsigned char time1_fifo_ads1[6];
	struct fifo time_fifo1;
	fifo_init(&time_fifo1,6,&time1_fifo_ads1);
	struct time *time2= time_alloc(&time_manger);
	time_set(&time_manger,time2,&time_fifo1,5000);
	

	

//////////////////////////////////////////////////////////////////////////////////
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
	draw_idt(idt_adss + 0x20,(int)asm_inthander20,16,0x008e);
	idt_save(0x7ff, 0x0026f800);//将中断向量表地址存入寄存器中





	/////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////////
	for (i = 0xa0000; i <= 0xaffff; i++) {
		if (i <= 0xabb80) {
			p = (char*)i;
			*p = 14;
		}                                                             //绘制屏幕上

		else {
			p = (char*)i;
			*p = 14;
		}                                                              //绘制屏幕下

	}
	//drawnormal(0,160,320,161,320,0xa0000,0);
	

	/*char atest[20];
	sprintf(atest,"ok");
	draw(60, 160, 50, 20, 0xa0000, 8);                                  //绘制方框
	draw(280, 160, 50, 50, 0xa0000, 8);
	drawnormal(100,100,135,135,320,0xa0000,3);
	drawnormal(100,100,135,105,320,0xa0000,4);
	drawnormal(100,100,105,135,320,0xa0000,7);
	drawnormal_src(115,115,320,0xa0000,8,atest);*/
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
	//char m0[30];
	//sprintf(m0, "%dMB", memory_size / (1024 * 1024));           //输出内存大小
	//draw_src(0, 150, fontpk, p, 8, m0);
	memorymanger_init(&memorymanger);
	int stuat1=memory_free(&memorymanger, 0x00001001, 0x0009e000);
	int stuat2=memory_free(&memorymanger, 0x00400000, memory_size - 0x00400000);//增加两条空间剩余记录
	//
	int map_ads=memory_alloc(320*200,&memorymanger);
	
	
	//
	struct manger_windows *mws = windows_init(&memorymanger,0xa0000,320,200);//初始化图层控制模块
	struct windows_content *back=windows_allow(mws);
	struct windows_content *mouse=windows_allow(mws);
	struct windows_content *win2=windows_allow(mws);
	struct windows_content *win3=windows_allow(mws);//添加图层
	struct windows_content *win4=windows_allow(mws);
	windows_set(back,map_ads,320,200,0,0);
	//windows_set(mouse,mousess,16,16,30,90,2);
	windows_set(win2,nop,200,100,10,80);
	windows_set(win3,mouse_map,16,16,0,0);//设置图层信息
	
	drawnormal(0,0,20,20,20,test_win,8);
	windows_set(win4,test_win,20,20,0,0);
	//test1(&mtest[624],120,80);
	windows_update(mws,back,0);
	windows_update(mws,win2,1);
	windows_update(mws,win3,2);//图层更新入图层管理模块
	windows_update(mws,win4,3);
	//windows_update(mws,mouse,3);
	drawnormal_font(100,80,320,mws->top,0xa0000,8);
	drawnormal(0,0,320,200,320,map_ads,14);
	window_draw_map(mws,map_ads);
	
	
	
	
	//test1(mws->top,100,80);
	/// ///////////////////////////////////////////////////////////////////////////////////
	//char m[500];
	//sprintf(m, "name=%dhahahahhhhh@@@@@&&&&&123h%oaha40%d");           //½«×Ö·û´®±£´æµ½mÖÐ
	//draw_src(0, 100, fontpk, p, 8, m);   
	/*char atest[10];      
	sprintf(layer_content_ads,"ok%d",mws->top);                          //»æÖÆ×Ö·û´®
	drawnormal_src(100,80,320,0xa0000,8,mtest.ads);*/
	//drawnormal_font(30,20,320,layer_content_ads[8],0xa0000,8);
	//char *testp;
	//*testp=tetsnnb;
	//*testp;
	
	//draw_mouse(50, 60, 6, 6, 6, fontpk);                             //»æÖÆÊó±êÐÎ×´
	//draw_rout(60, 20);
	//test1(mtest.ads,100,80);
	init_pit();
	oi_8out(pic0_imr, 0xf8);                                          //随意绘制的图层
	oi_8out(pic1_imr, 0xef);             //禁用所有中断（imr为屏蔽寄存器）
	init_jianpan();
	enable_mouse();                      //激活鼠标，键盘控制模块
	int memory=0;
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
	int n=1;
	int time_start=2;
	int mm1=0;
	int movex=10,movey=10;
	for (;;)

	{
		//shubiaojianpan(jianpan, shubiao1, mousex, mousey, date, date1, mmv, fontpk);
			char test2[100];
			int s00= (count/100);
			sprintf(test2,"today is 2022.12.2.11:%d %02d",minute,s00);
			drawnormal(0,0,200,32,200,nop,0);
			drawnormal_src(0,0,200,nop,2,test2);
			char test00[10];
			char nu =s[0]*100;
			nu+=s[1]*10;
			nu+=s[2];
			test00[0]=(nu);
			drawnormal_src(130,16,200,nop,2,test00);
			test1(nu,130,80);//键盘按下与抬起有两个数据（asill是一个内存单位存一个字ascill）


			//int time_keep=count/100;
			
			/*if(((time_keep-time_start)>=0)&&((time_keep-time_start)<2)) {
				
				drawnormal(100,16,110,32,200,nop,6);
				
				if(time_keep-time_start>=1){
					n=2;
				}
			};
			
			if (n==2){
				time_start+=2;
				n=1;
			};*/
			
			/*if(time1_fifo_ads[0]==1){
				
				
				
				if(mm1+5!=s){drawnormal(100,16,110,32,200,nop,6);}
			};
			
				if(mm1+5==s){
					//time1_fifo_ads[0]=0;
					time_set(&time_manger,time1,&time_fifo,0);
					mm1+=2;
				}*/

			



			window_draw_map(mws,map_ads);
			window_draw(back,0xa0000);
			//starttime(&time_manger,1,s,memory);
			//if(memory+2==s){memory+=2;};
			//test1(time1_fifo_ads[0],100,60);
			//test1(time1_fifo_ads1[0],100,140);
			drawnormal(40, 0, 150, 30,320, 0xa0000, 14);
			draw_src(40, 0, fontpk, 0xa0000, 7, moused);
			//test1(movey,100,100);
			//test1(mouse_map[10],100,80);
			//draw_mouse(mousex,mousey,6,2,5,fontpk,0xa0000);
		       //numbe++;  
		       //sprintf(layer_content_ads,"%010d",numbe);
		       //drawnormal(0,0,100,16,320,0xa0000,14);
		       //drawnormal_src(0,0,320,0xa0000,1,mtest.ads);//draw不能只提供一种颜色，要实现传入颜色数组
		       //drawnormal(0,20,89,36,320,layer_content_ads,14);
		       //drawnormal_src(0,20,320,layer_content_ads,7,layer_content_ads);
		       //drawnormal(0,20,89,36,320,layer_content_ads);

		       //windows_refresh(mws);

			if (64 - (jianpan.free) != 0) {
				oi_cli();
				date = jianpan.date[jianpan.q];

				if (jianpan.q < 64) {
					jianpan.q++;
					jianpan.free++;
					oi_sti();
					test1(date,100,80);

					sprintf(s, "%d", date);
					drawnormal(0, 0, 30, 30,320, 0xa0000, 14);
					draw_src(0, 0, fontpk, 0xa0000, 7, s);
					

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
						//drawnormal(mousex, mousey,mousex+16,mousey+16,320, 0xa0000, 14);
						drawnormal(mousex,mousey,mousex+16,mousey+16,320,map_ads,14);
						drawnormal(0,0,320,200,320,map_ads,14);
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

						

						drawnormal(40, 0, 150, 30,320, 0xa0000, 14);
						draw_src(40, 0, fontpk, 0xa0000, 7, moused);
						if(date1.datearray[0]==0x9){
							//movex+=(mmv.x/2);
							//movey+=(mmv.y/2);
							//if(200+mmv.x>0){
							//	if(100+mmv.y>0){
									
									windows_set(win2,nop,200,40,mousex-184,mousey-24);
									

								
							//	}
							//}

							


						};
						
						
						//windows_set(mouse,&mousess,16,16,mousex,mousey,2);//指针类型不能写错了，不然一次写入的数据大小不确定。（改了一天）
						date1.number = 1;
						
						//drawnormal_src(mousex,mousey,320,0xa0000,,10);
						//windows_refresh(mws);//注意区分地址
						//draw_mouse(mousex,mousey,6,2,5,fontpk,0xa0000);
						
			
			//window_draw(win2,nop,0xa0000);
			windows_set(win3,mouse_map,16,16,mousex,mousey);

			window_draw_map(mws,map_ads);
			//window_draw(back,0xa0000);
			
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


void init_pit(){
	oi_8out(0x43,0x34);
	oi_8out(0x40,0x9c);//中段周期低
	oi_8out(0x40,0x2e);//中段周期高
	return;
}

void inthander20(int *esp){
	oi_8out(pic0_ocw2,0x60);
	count++;
	if((count%=6000)==0){
				minute++;
			};
	
	
	return;
}


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

void tetsnnb(){
	test1(0,100,80);
}
