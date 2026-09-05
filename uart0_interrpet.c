#include"header.h"
 int i=0;
#include<LPC21xx.H>
extern unsigned char temp[100];

void uart0_handler(void) __irq
{
   int t=U0IIR ;
  if(t&4)//check 4 th bit of UOIIR to check intruppt comes due to rx
   {
	  temp[i++]=U0RBR;
   }
	VICVectAddr=0;//mandatory line

}

void config_vic(void)
{
 	VICIntSelect=0;//irq select
	VICVectCntl0=6|(1<<5); //slot uart0 
	VICVectAddr0=(int)uart0_handler;	//address copy
	VICIntEnable |=1<<6; //unable uart0

}
void en_uart0_intr(void)
{
 U0IER=3;//SET FOR RX AND TX;
}

