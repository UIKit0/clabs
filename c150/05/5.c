 #include "stdio.h"
 #include "math.h"                       /*����*/
 #define PI 3.1415927
 #define H  25                           /* ������ */
 #define N 2*PI/H                        /* ���ϵ��*/
 #define BLANK ' '
 #define DOT   '.'
 main()
  {
  int a,i,j;
  for(i=0;i<H;i++)
    {
       a=30*sin(i*N);                    /*����30��*/
       for(j=0;j<(a+40);j++)             /*��40Ϊ������ͼ��*/
	 {
	   if(j==40)
	   printf("%c",'|');
	   else
	   printf("%c",BLANK);
	 }
       printf("%c",DOT);
       if(a<0)
	 {
	   for(j=(a+41);j<40;j++)
	     {
	     printf("%c",BLANK);
	     }
	   printf("%c",'|');
	 }
       printf("\n");
    }
 }