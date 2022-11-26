#include "bootpack.h" 



void fifo_init(struct fifo *fifo_int,int size,unsigned char *date ) {
	fifo_int->date = date;
	fifo_int->p = 0;
	fifo_int->q = 0;
	fifo_int->size = size;
	fifo_int->flage = 1;
	fifo_int->free = size;
	//fifo_int->len = size - (fifo_int->free);
}

//extern char fontpk[4096];
void fifo_put(struct fifo* fifo, char date) {
	//unsigned char date;
	if (fifo->free == 0) {
		return;
	}
	
	else {
		fifo->date[fifo->p] = date;
		
		fifo->p++;
		fifo->free--;
		if (fifo->p == fifo->size) {
			fifo->p = 0;
		}
	}
}
