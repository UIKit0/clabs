#include "stdio.h"
#define  M  200                   /*��Χ*/
#define  N  ((M+1)/2)             /*�����ĸ���*/
main()
{
  int i,j,a[N];
  a[0]=2;
  for(i=1;i<N;i++)                /*��ʼ����ʵ�ֵ�һ��ɸѡ*/
    a[i]=2*i+1;
  for(i=1;i<(N-1);i++)            /*�ڶ���ɸѡ*/
    if(a[i]!=0)
      for(j=i+1;j<N;j++)
	if((a[j]%a[i]==0))        /*����ʱ����ɸȥ*/
	   a[j]=0;
  printf("\n The primer are[2-%d]:\n",M);
  for(i=0,j=0;i<N;i++)            /*��ʾ�õ�����*/
     {
       if(a[i]!=0)
	 {
	   printf("%5d",a[i]);
	   if((++j)%10==0)        /*ʮ��������*/
	     printf("\n");
	 }
      }
   return;
 }
