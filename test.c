#include "bootpack.h"
#include <stdio.h>
void test1(int n,int x,int y) {
	char testnum[20];
	extern char fontpk[4096];
	sprintf(testnum, "%d",n);
	draw_src(x, y, fontpk, 0xa0000, 8, testnum);
};