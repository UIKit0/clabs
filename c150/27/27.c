 #include "stdio.h"
 main()
   {
     enum colours                          /*����ö������*/
	{
	  RED,YELLOW,BLUE,GREEN,WHITE,BLACK
	};
     enum colours i,j,k,p;                 /*����ö�ٱ���*/
     int n=0,number;
     for(i=RED;i<=BLACK;i++)               /*��ٱȽ�*/
	for(j=RED;j<=BLACK;j++)
	  {
	    if(i!=j)
	      {
		for(k=RED;k<=BLACK;k++)
		   if(k!=i&&k!=j)
		      {
			if(n%3==0)         /*ÿ����ʾ3�����*/
			   printf("\n");
			printf("%-4d",++n);/*�����������������*/
			for(number=1;number<=3;number++)
			   {
			     switch (number)/*ȡö�ٳ���ֵ*/
			       {
				 case 1 : p=i;break;
				 case 2 : p=j;break;
				 case 3 : p=k;break;
				 defaut :     break;
				}
			      switch (p)
				{
				  case RED    : printf("%-7s","red");break;
				  case YELLOW : printf("%-7s","yellow");break;
				  case BLUE   : printf("%-7s","blue");break;
				  case GREEN  : printf("%-7s","green");break;
				  case WHITE  : printf("%-7s","white");break;
				  case BLACK  : printf("%-7s","black");break;
				}
			   }
		       }
		 }
	    }
     printf("\n\n total: %4d \n",n);
     return;
   }