/*1-4.c*/
     #include "stdlib.h"
     #include "graphics.h"
     main()
     {
          int gdriver=DETECT, gmode, i;
          initgraph(&gdriver, &gmode, "");
          setbkcolor(RED);
          cleardevice();
          setcolor(BLUE);
          circle(320,240,50);
          circle(320,240,100);
          setlinestyle(0, 0, 3);   /*���������ʵ��*/
          setcolor(2);
          rectangle(220, 140, 420, 340);
          setcolor(WHITE);
          setlinestyle(4, 0xaaaa, 1);   /*����һ����û�������*/
          line(220, 240, 420, 240);
          line(320, 140, 320, 340);
          getch();
          closegraph();
     }
