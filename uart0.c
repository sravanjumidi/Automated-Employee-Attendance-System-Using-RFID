#include"header.h"

#define THRE ((U0LSR>>5)&1)
#define RDR (U0LSR&1)

void uart0_init(unsigned int baud)
{
 int result;

 int a[]={15,60,30,0,15};
  int PCLK=0;
  PCLK=a[VPBDIV]*1000000;
  
  result=PCLK/(16*baud);
  PINSEL0 |=0X05;
  U0LCR=0X83;
  U0DLL=(result)&0xff;
  U0DLM=(result>>8)&0xff;
  U0LCR=0X03;
}

void uart0_tx(unsigned char data)
{
U0THR=data;
while(THRE==0);
}

unsigned char uart0_rx(void)
{
 while(RDR==0);
 return(U0RBR);
}


void uart0_tx_string( unsigned char *p)
{
while(*p != 0)
  {
   uart0_tx(*p);
    p++;
  }
}

void uart0_tx_integer(int num)
{
 int a[20],i=0;
 
 if(num==0)
    {
	 uart0_tx('0');
	 return;
	}
  if(num<0)
    {
	 uart0_tx('-');
	 num=-(num);
	}
   while(num!=0)
    {
	 a[i]=num%10;
	 i++;
	 num=num/10;
	}
	for(--i;i>=0;i--)
	  {
	   uart0_tx(a[i]+48);
	  }
}


void uart0_float(float f) 
{
 int i;
 i=f;
 uart0_tx_integer(i);
 uart0_tx('.');
 i=(f-i)*100;
 uart0_tx_integer(i);
}

void uart0_rx_string(char *ptr,u8 len)
{
s32 i;
for(i=0;i<len;i++)
{
while(RDR==0);
ptr[i]=U0RBR;
if(ptr[i]=='\r') //if enter key
break;
}
ptr[i]='\0';  //null
}















