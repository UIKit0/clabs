#include "stdio.h"
void selectsort(int a[],int n)
{
  int i,j,k,num;
  for(i=0;i<n-1;i++)              /*�ⲿѭ��ʵ��ѡ������*/
    {
      k=i;
      for(j=i+1;j<n;j++)          /*�ڲ�ѭ���õ���С��*/
	if(a[j]<a[k])
	  k=j;
      if(k!=i)
	{
	  num=a[k];              /*����������С��*/
	  a[k]=a[i];
	  a[i]=num;
	}
     }
  printf("\n\n The sorted numbers are:");
  for(i=0;i<n;i++)
    printf("%7d",a[i]);           /*��ʾ���������*/
}

void halfind(int a[],int n)       /*aΪ�β�,��ַ����*/
{
  int i,k,
  find=0,                         /*�ҵ���־*/
  first=0,                        /*��Χ���*/
  last=(n-1),                     /*��Χ�յ�*/
  half;                           /*���ҵ�*/
  printf("\n\n Input the number to look for:");
  scanf("%d",&k);
  do{
      half=(first+last)/2;
      if(k==a[half])                /*�����жϽ��ִ����һ��*/
	{
	  printf("\n Find %d,it is a[%d].",k,half);
	  find=1;
	}
      else if (k>a[half])
	 first=half+1;
      else
	 last=half-1;
     }while((first<=last)&&(find==0));   /*ѭ������*/
   if(find==0)
     printf("\n %d not been found!",k);
}

main()
{
  int i,n,a[100];
  printf("\n Input the total number[1-100]:");
  scanf("%d",&n);
  printf("\n Input %d numbers:",n);
  for(i=0;i<n;i++)
    scanf("%d",&a[i]);
  printf("\n The original orders are:");
  for(i=0;i<n;i++)
     printf("%7d",a[i]);
  selectsort(a,n);
  halfind(a,n);                     /*aΪʵ��,��ַ����*/
  return;
}
