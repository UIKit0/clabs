/*1-3.c*/
     #include "stdio.h"
     #include "graphics.h"
     main()
     {
          int gdriver, gmode, i,j;
          gdriver=DETECT;
          initgraph(&gdriver, &gmode, ""); /*ͼ�γ�ʼ��*/
          setbkcolor(0);                   /*����ͼ�α���*/ 
          cleardevice(); 
          for(i=0; i<=15; i++) 
          { 
            setcolor(i);                   /*���ò�ͬ��ͼɫ*/ 
            circle(319, 239, 20+i*15);     /*���뾶��ͬ��Բ*/ 
            delay(3000);                   /*�ӳ�3000����*/ 
          } 
          for(i=0; i<=15; i++) 
          { 
             setbkcolor(i);                /*���ò�ͬ����ɫ*/ 
             cleardevice(); 
       for(j=0; j<=15;j++) 
          { 
            setcolor(j);                   /*���ò�ͬ��ͼɫ*/ 
            circle(319, 239, 20+j*15);     /*���뾶��ͬ��Բ*/ 
            delay(3000); 
             } 
          } 
      getch();
      closegraph(); 
      } 
