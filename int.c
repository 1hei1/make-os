#include "bootpack.h"
void init_pic(){
oi_8out(pic0_imr,0xff);
oi_8out(pic1_imr,0xff);
oi_8out(pic0_icw1,0x11);
oi_8out(pic0_icw2,0x20);
oi_8out(pic0_icw3,1<<2);
oi_8out(pic0_icw4,0x01);
oi_8out(pic1_icw1,0x11);
oi_8out(pic1_icw2,0x28);
oi_8out(pic1_icw3,2);

oi_8out(pic1_icw4,0x01);
oi_8out(pic0_imr,0xfb);
oi_8out(pic1_imr,0xff);


}