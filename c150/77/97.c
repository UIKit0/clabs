/*7-1.c*/
#include "graphics.h"
#include "dos.h"
#include "stdio.h"
#define ENABLE 0x0F
#define INDEXREG 0x3CE
/*���������Ĵ����˿ڵ�ַ*/
#define VALREG 0x3CF
/*�������ݼĴ����˿ڵ�ַ*/
#define VGABASE 0xA0000000L
#define WIDTH 80L
#define XMAX 639
#define YMAX 479
#define XMIX 0
#define YMIN 0
#define OUTINDEX(index,val)  outport(INDEXREG,index);outport(VALREG,val);
char far *vgabase;
void putpoint(int x,int y,int color,int how);
main()
{
int gmode=VGAHI,gdriver=VGA;
int color=1,x,y;
initgraph(&gdriver,&gmode,"");
/*���Ƹ�����ɫ��ֱ�߶�*/
for(y=1;y<=479;++y){
for(x=1;x<=639;++x)
putpoint(x,y,color,0);
color++;}
getch();
/*�����ʽ��������ֱ��*/
color=1;
for(y=1;y<=479;++y){
for(x=1;x<=639;++x)
putpoint(x,y,color,0x18);
color++;}
getch();
closegraph();
     }

/*����ͼ�ο��ƼĴ�������д���غ���*/
void putpoint(int x,int y,int color,int how)
{
register unsigned char mask=0x80;
register char far *base;
unsigned dummy;
vgabase=(char far *)MK_FP(0xA000,0);
base=(char far *)(vgabase+((long)y*
WIDTH+(long)x/8L));
mask>>=x%8;
dummy=*base;
OUTINDEX(0,color);/*�趨��ɫ*/
OUTINDEX(1,ENABLE);/*����λƽ��*/
OUTINDEX(3,how); /*ȷ���߼�������ʽ*/
OUTINDEX(8,mask);/*��������λ*/
*base=1;
OUTINDEX(0,0);/*�Ĵ�����λ*/
OUTINDEX(1,0);
OUTINDEX(3,0);
OUTINDEX(8,0xff);
}
