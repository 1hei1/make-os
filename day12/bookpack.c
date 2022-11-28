//ospack.nas
void io_hlt(void);  
int oi_8in(int port);       //一字节输入cpu
void oi_8out(int port, int date);//一字节输出cpu
void oi_store_eflags(int eflags);//设置标志寄存器的值
int oi_load_eflags(void);//加载标志寄存器的值并返回
void oi_cli(void);//设置停用中断
void oi_sti(void);//设置启用中断
void asm_inthandler(void);//中断处理程序0x21（外）
void asm_inthandler27(void);
void asm_inthandler2c(void);



//fifo.c
void fifo_init(struct fifo *fifo_int, int size, unsigned char *date);
void fifo_put(struct fifo *fifo, char date);



//pic																			//让计算机休眠
void init_pic();



//bootpack.c
void wait_kbc(void);
void init_jianpan();
void enable_mouse();



//gdtidt.c


void gdt_save(int high, int ads);   //初始化pic中断控制器
void idt_save(int high, int ads);    //保存idt表的地址 (high=表的大小，ads=表的地址）
void JIANPAN(int* esp);//同上（内）
void shubiao(int* esp);
void shubiaodate(int* esp);



//draw.c
void write(int i, int c);         //  把c写到i中
void init_palette(void);//初始化画板
void draw(int x, int y, int bootx,int booty, int *ads,int c);//绘制屏幕x，y起始坐标，bootx，y规定长度，ads起始地址（0xa0000），c颜色
void drawnormal(int x, int y, int x1,int y1,int bootx,char *ads,int c);
void set_palette(int start, int end, unsigned char* rgb);//设置画板16种颜色（包含在初始化画板）
void draw_font(int x,int y,char* font,char* vram,int c);//绘制字体font字体库，varm初始地址（0xa0000），c颜色
void drawnormal_font(int x, int y,int xsize, char font, char* vram,int c);
void draw_mouse(int setx,int sety,int a,int b,int c,char * fontpk,unsigned int *ads);//绘制鼠标形状setx，y起始坐标，啊a,b,c颜色，fontpk字体库
void draw_rout(int x, int y);//自定义图形
void draw_ads(struct gdt_ads* gdt_adss, int limit, int base, int ad);//
void draw_src(int x,int y,char * font,char * ads,int color,char * ads_src);//绘制字符串
void drawnormal_src(int x, int y,int xsize, char* ads, int color,unsigned char* ads_src);
void draw_normal(int x,int y,int x1,int y1,int xsize,char *ads,int c);



//int fifo8_put(struct huanchong huancongmouse,unsigned char date);
//void draw_idt(struct idt_ads* idt, int offset, int selector, int ad);
//void draw_gdt(struct gdt_ads* gdt_adss, int limit, int base, int ad);
//void draw_gdt(struct gdt_ads* gdt_adss, int limit, int base, int ad);

//memorymanger.c

struct memoryrecord {
	unsigned int startads, size;

};

struct memorymanger1 {
	unsigned int number_record;
	struct memoryrecord free[10];
};

unsigned int memory_mgr(unsigned int start,unsigned int end);
unsigned int memory_size(unsigned int start,unsigned int end);
unsigned int memory_alloc(int size, struct memorymanger1* memorymanger);
int memory_free(struct memorymanger1* memorymanger, unsigned int ads, unsigned int size);
void memorymanger_init(struct memorymanger1 *memorymanger);
struct manger_windows * windows_init(struct memorymanger1 *memorymanger,int ads,int xsize,int ysize);
struct windows_content * windows_allow(struct manger_windows * mws);
//void windows_set(struct windows_content*std,struct layer_content *ads,int xsize,int ysize,int x,int y,int color);
void windows_update(struct manger_windows *mws,struct windows_content*std,int height);


//test.c
void test1(int n,int x,int y);




//pic相应寄存器
#define pic0_icw1  0x0020
#define pic0_ocw2  0x0020
#define pic0_imr   0x0021
#define pic0_icw2  0x0021
#define pic0_icw3  0x0021
#define pic0_icw4  0x0021
#define pic1_icw1  0x00a0
#define pic1_ocw2  0x00a0
#define pic1_imr   0x00a1
#define pic1_icw2  0x00a1
#define pic1_icw3  0x00a1
#define pic1_icw4  0x00a1


/* 娭悢愰尵側偺偵丄{}偑側偔偰偄偒側傝;傪彂偔偲丄
	懠偺僼傽僀儖偵偁傞偐傜傛傠偟偔偹丄偲偄偆堄枴偵側傞偺偱偡丅 */

struct gdt_ads {
	short limit_low, base_low;
	char base_mid, access_right;
	char limit_hight, base_high;//gdt结构体
};
struct idt_ads {
	short offset_low, selectpr;
	char dw_count,access_right;//idt结构体
	short offset_high;
};


/*struct huancong {
	unsigned char date[256];
	int next_w;
	int next_r;
	int len;
};*/

struct fifo {
	unsigned char* date;
		int p, q, free, size, flage;
};


struct windows_content{
struct layer_content *content_ads;
int xsize,ysize,x,y,height,flage,color;
};
struct manger_windows{
	int ads,xsize,ysize,top;
	struct windows_content * window_contentd_ads[256];
	struct windows_content window_contentd[256];
};


struct contents{
	int x,y;
	unsigned char *ads;
};



struct layer_content{
	int x,y;
	unsigned int ads;                       //注意此处ads类型为int，若为指针则任何类型都可
};
