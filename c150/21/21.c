 #include "stdio.h"
 #define N 10000
 main()
    {
      float y;
      float fbds(float);
      float jifen(float,float,float(*fun)(float));
      y=jifen(0.0,2.0,fbds);
      printf("\n\n ����y=�� (1+x+x*x*x)dx�Ķ���(x��[0,2])��:%6.2f",y);
    }
 float fbds(float x)
   {
     return(1.0+x+x*x*x);
   }
 float jifen(float a,float b,float(*fun)(float))
   {
     int i;
     float h,s;
     h=(b-a)/N;
     s=((*fun)(a)+(*fun)(b))/2.0;
     for(i=1;i<=N;i++)
     s=s+(*fun)(a+i*h);
     return (s*h);
   }
