#include "bootpack.h"

unsigned int memory_mgr(unsigned int start, unsigned int end) {
	char is486 = 0;
	unsigned int cr0, eflg;
	//int eflg;
	eflg = oi_load_eflags();
	eflg |= 0x00040000;
	oi_store_eflags(eflg);
	eflg = oi_load_eflags();
	if ((eflg & 0x00040000) != 0) {
		is486 = 1;
	}
	eflg &= ~0X00040000;
	oi_store_eflags(eflg);
	if (is486 != 0) {
		cr0 = load_cr0();
		cr0 |= 0x60000000;
		store_cr0(cr0);
	}
	unsigned int i = memory_size(start, end);
	if (is486 != 0) {
		cr0 = load_cr0();
		cr0 &= ~0x60000000;
		store_cr0(cr0);
	}
	//i /= (1024*1024);

	return i;


};






void memorymanger_init(struct memorymanger1* memorymanger) {


	memorymanger->number_record = 0;

};

unsigned int memory_alloc(int size, struct memorymanger1* memorymanger) {
	int i;
	for (i = 0; i <= 1000; i++) {
		if (memorymanger->free[i].size >= size) {
			int c;

			c = memorymanger->free[i].startads;
			memorymanger->free[i].startads += size;
			memorymanger->free[i].size -= size;
			if (memorymanger->free[i].size == 0) {
				memorymanger->number_record--;
				for (; i < memorymanger->number_record; i++) {

					memorymanger->free[i] = memorymanger->free[i + 1];
				}

			}
			return c;
		}
	}
};


int memory_free(struct memorymanger1* memorymanger, unsigned int ads, unsigned int size) {
	int i;
	for (i = 0; i < memorymanger->number_record; i++) {
		if (memorymanger->free[i].startads > ads) {
			if (ads + size == memorymanger->free[i].startads) {
				memorymanger->free[i].startads = ads;
				memorymanger->free[i].size += size;

			}
			if (ads == (memorymanger->free[i-1].startads)+(memorymanger->free[i-1].size)) {
				memorymanger->free[i].size += memorymanger->free[i - 1].size;
				memorymanger->free[i].startads = memorymanger->free[i - 1].startads;
				i -= 1;
				for (; i < memorymanger->number_record; i++) {
					memorymanger->free[i] = memorymanger->free[i + 1];
				}
				memorymanger->number_record--;
				return 1;
				break;
			}
			return 0;
			break;

		}
	}
	memorymanger->number_record += 1;
	i = memorymanger->number_record - 1;
	memorymanger->free[i].startads = ads;
	memorymanger->free[i].size = size;
	return -1;



};



struct manger_windows * windows_init(struct memorymanger1 *memorymanger,int ads,int xsize,int ysize){

struct manger_windows *mws;
int i;
mws =(struct manger_windows*) memory_alloc(sizeof(struct manger_windows),memorymanger);
if (mws==0){
	goto erro;
}
mws->ads = ads;
mws->xsize = xsize;
mws->ysize = ysize;
mws->top =-1;
for (i=0;i<256;i++){
	mws->window_contentd[i].flage=0;
}
erro:
return mws;
}



struct windows_content * windows_allow(struct manger_windows * mws){
struct windows_content * std;
int i;
for (i=0;i<256;i++){
	if (mws->window_contentd[i].flage==0){
		std = &mws->window_contentd[i];
		std->flage=1;
		std->height = -1;
		return std;
	}
}
return 0;
};

void windows_set(struct windows_content*std,struct layer_content *ads,int xsize,int ysize,int x,int y,int color){
	std->content_ads = ads;
	//test1(ads[624],180,80);
	std->xsize=xsize;
	std->ysize=ysize;
	std->x=x;
	std->y=y;
	std->color=color;
};
extern char fontpk[4096];int n=0;



void windows_update(struct manger_windows *mws,struct windows_content*std,int height){
	int h,old=std->height;
	if(height > mws->top){
		height = mws->top+1;
	}
	else if(height<-1){
		height=-1;
	};
	

	if(height==mws->top+1){
		if(old>=0&&old<mws->top){
			for(h=old;old<mws->top;h++){
			mws->window_contentd_ads[h]=mws->window_contentd_ads[h+1];
			mws->window_contentd_ads[height-1]=std;
			
		}return;
		}
		mws->window_contentd_ads[height]=std;
		mws->top++;
		

		return;

	}
	else if(height<=mws->top){
		if(height<0){
			if(old>=0){
			for(h=old;h<mws->top;h++){
				mws->window_contentd[h]=mws->window_contentd[h+1];

			}
			mws->top--;
			return;}
			mws->window_contentd_ads[height]=std;
			return;

		}
		else{
			if(height!=old){
				//mws->window_contentd_ads[old]=mws->window_contentd_ads[height];
				mws->window_contentd_ads[height]=std;
				
				return;
			}
			mws->window_contentd_ads[height]=std;
			
			return;
		}




	}







	

	//windows_refresh(mws);
}

//
struct mousemove {
		int btn, x, y
	};
void windows_refresh(struct manger_windows *mws){
	int i,j;
	struct windows_content *std;
	for (i=0;i<=mws->top;i++){
		std=mws->window_contentd_ads[i];
		char m[10];
		sprintf(m,"NO");
		
		drawnormal(std->x,std->y,std->x+std->xsize,std->y+std->ysize,320,0xa0000,std->color);
		drawnormal_src(std->content_ads->x,std->content_ads->y,std->xsize,0xa0000+std->x+(std->y)*320,8,std->content_ads->ads);//注意字符串绘制起始地址的计算
		test1(std->x+(std->y)*320,180,100);
		
		//drawnormal_src(0,0,320,0xa2000,8,std->x+(std->y)*320);
	}
}






















	/*int i,x,y,n,testnmu=0;
	unsigned char *a=0xa0000;
	extern char fontpk[4096];
	struct windows_content *std;
	for (i=0;i<=mws->top;i++){
		n=0;if(i==mws->top){	
		test1(mws->top,160,80);	
		mousex -=mmv->x;
		mousey -=mmv->y;
		draw(mousex,mousey,16,16,0xa0000,6);};
		std = (struct windows_content *)mws->window_contentd_ads[i];
		test1(std->content_ads[0],180,80);
		for(y=std->y;y<=(std->ysize+std->y);y++){
			for(x=std->x;x<=(std->xsize+std->x);x++){
				a[x+y*320]=std->content_ads[n];
				
				n++;
			};
		};
	};*/
//};



