#define  N 17                       /*������*/
#define  M 3                        /*��������*/
#include "stdio.h"
main()
{
  int a[N],k=0,i,j;
  printf("\n\n The original orders are :\n");
  for(i=0;i<N;i++)                  /*��ʼλ�Ų���ʾ*/
   {
     a[i]=i+1;
     printf("%3d",a[i]);
   }
  printf("\n");
  for(i=0;k<N*M;i++)                /*ѭ��ʵ�ֳ���*/
    {
      if(a[i%N]!=-1)
	{
	  k++;                       /*����������*/
	  if(k%3==0)
	    {
	      a[i%N]=-1;             /*3��������*/
	      printf("\n%2d is out!",(i%N+1));
	      if(k!=N*3)
		printf("The new order is:");
	      else
		printf("The game is over!");
	      for(j=0;j<N;j++)
		{
		  if(a[j]!=-1)
		   printf("%3d",a[j]);  /*������Ϣ��ʾ*/
		 }
	     }
	 }
     }
  return;
}