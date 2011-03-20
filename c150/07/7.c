#include "stdio.h"
#include "ctype.h"               /*Ӧ�ú���toupper*/
void move(int n,char a,char b)   /*nΪ�ƶ�������,aΪԴ����,bĿ������*/
  {
    int i=0;
    printf("Disc%d move from %c to %c;",(n+1),a,b);
    if(i++%2==0)
      printf("\n");
  }

void hanoi(int n,char a,char b,char c)
  {                   /*n�ƶ�������,aΪԴ����,bΪĿ������,cΪ�м�����*/
    if(n>0)
      {
	hanoi(n-1,a,c,b);        /*�ݹ����*/
	move(n-1,a,b);
	hanoi(n-1,c,b,a);
      }
   }
main()
  {
   int n;
   char ch='Y';
   printf("Now let us play the game of hanoitower\n");
   while(ch=='Y')                                     /*ͨ�������*/
     {
       printf("\n Input the number of disc[2-15]:");
       scanf("%d",&n);getchar();
       printf("\n The orders of moving %d discs from A to B are:\n",n);
       hanoi(n,'A','B','C');                           /*���ú���*/
       printf("\n Continue(Y/N):");
       ch=getchar();
       getchar();
       ch=toupper(ch);
     }
  return;
}
