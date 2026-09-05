#include"header.h"

 void delay_ms(unsigned int ms)
{
 int a[]={15,60,30,0,15};
 int PCLK=0;
 PCLK=a[VPBDIV]*1000;

 T0PC=0;
 T0PR=PCLK-1;
 T0TC=0;

 T0TCR=1;
 while(T0TC<ms);
 T0TCR=0;
}
