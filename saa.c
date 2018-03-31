#include<reg51.h>
sbit DK=P1^0;
sbit DS=P1^1;
sbit DY=P1^2;
sbit YK=P1^3;
sbit YS=P1^4;
sbit YY=P1^5;


int dikey =0,yatay=0;
int dikeyzaman=10,yatayzaman=10,flagyatay=0,flagdikey=0;

void delay (unsigned  int b)
 {
	 int i,c;

	TMOD=0x01;
	for(c=0;c<=b;c++){
     for(i=0;i<20;i++)
       {
         TH0=500000/255;
         TL0=-500000%256;
         TF0=0;
         TR0=1;
         while (TF0==0);
       }
     }
 }
void clear()
{
DK=0;
DS=0;
DY=0;
YK=0;
YS=0;
YY=0;
} 

void yatayyesil(unsigned int a)
{
DK=1;
YY=1;
delay(a);
DS=1;
delay(2);

}

void dikeyyesil(unsigned int b)
{
YK=1;
DY=1;
delay(b);
YS=1;
delay(2);
}
void yatay1() interrupt 0
{
	yatay=yatay+1;
	flagyatay=1;
}
void dikey1() interrupt 2
{
	dikey=dikey+1;
	flagdikey=1;
}

void zaman()
{
  if(dikey+yatay<30)
	{
		dikeyzaman=dikey;
		yatayzaman=yatay;
		yatay=1;
		dikey=1;
	}
  yatay=1;
	dikey=1;

}
void main()
{
P1=0x00;
P2=0x00;
IE=0x85;
 
EX0=1;
IT0=1;
EX1=1;
IT1=1;
while(1)
  {

	 yatayyesil(yatayzaman);
	 clear();
	 dikeyyesil(dikeyzaman);
	 clear();
   yatayzaman=10;
	 dikeyzaman=10;
	 if(flagyatay==1 || flagdikey==1)
	 {
			 zaman();
			
	 }
  flagyatay=0;
	flagdikey=0;
  }

}
