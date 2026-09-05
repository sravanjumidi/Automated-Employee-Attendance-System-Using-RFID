 #include"header.h"
 #define SI ((I2CONSET>>3)&1)

void i2c_init(void)
{
 PINSEL0 |=0x50;
 I2SCLH=75;
 I2SCLL=75;
 I2CONSET=(1<<6);

}
 void  i2c_byte_write_frame(u8 sa,u8 mr,u8 data)

{
 
 I2CONSET=(1<<5);
 I2CONCLR=(1<<3);
 while(SI==0);
 I2CONCLR=(1<<5);
 if(I2STAT !=0X08)
   {
    uart0_tx_string("err:start condition in write\r\n");
	goto exit;
   }


  I2DAT=sa;
  I2CONCLR=(1<<3);
  while(SI==0);
   if(I2STAT==0X20)
   {
    uart0_tx_string("err:sa+w in write \r\n");
	goto exit;
   }


    I2DAT=mr;
  I2CONCLR=(1<<3);
  while(SI==0);
   if(I2STAT==0X30)
   {
    uart0_tx_string("err:memory addr in write\r\n");
	goto exit;
   }


   I2DAT=data;
  I2CONCLR=(1<<3);
  while(SI==0);
   if(I2STAT==0X30)
   {
    uart0_tx_string("err:data in write\r\n");
	goto exit;
   }
   
    exit:
	 I2CONSET=(1<<4);
	 I2CONCLR=(1<<3); 

}
unsigned char i2c_byte_read_frame(u8 sa,u8 mr)
{
 unsigned char temp;

   I2CONSET=(1<<5);
 I2CONCLR=(1<<3);
 while(SI==0);
 I2CONCLR=(1<<5);
 if(I2STAT !=0X08)
   {
    uart0_tx_string("err:start condition in read\r\n");
	goto exit;
   }


  I2DAT=sa;
  I2CONCLR=(1<<3);
  while(SI==0);
   if(I2STAT==0X20)
   {
    uart0_tx_string("err:sa+w in read\r\n");
	goto exit;
   }


    I2DAT=mr;
  I2CONCLR=(1<<3);
  while(SI==0);
   if(I2STAT==0X30)
   {
    uart0_tx_string("err:memory addr in  read\r\n");
	goto exit;
   }


   I2CONSET=(1<<5);
 I2CONCLR=(1<<3);
 while(SI==0);
 I2CONCLR=(1<<5);
 if(I2STAT !=0X10)
   {
    uart0_tx_string("err:restart condition in read\r\n");
	goto exit;
   }



	 I2DAT=sa | 1;
  I2CONCLR=(1<<3);
  while(SI==0);
   if(I2STAT==0X48)
   {
    uart0_tx_string("err:sa+r in read \r\n");
	goto exit;
   }


   I2CONCLR=(1<<3);
   while(SI==0);
   temp=I2DAT;


   exit:
    I2CONSET=(1<<4);
	I2CONCLR=(1<<3); 
	return temp;

}



 char num_to_hex(int num)
{
   int sum=0;
    int i=0,a[10];
   while(num!=0)
     {
      int rem=num%16;
      if(rem>9 && rem<16)
        a[i++]=(rem-10)+65;
      else
        a[i++]=(rem+48);
    num=num/16;
  
   }
  for(--i;i>=0;i--)
    {
     sum=sum*10+a[i];
     }
  	  return(sum);
  }


 

