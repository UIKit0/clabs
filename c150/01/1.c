 #include "stdio.h"                     /*Ӧ��printf����*/
 #include "stdlib.h"                    /*Ӧ��toupper����*/
 void print()                           /*�����Ӻ���*/
   {
      printf("\n\t This is an example.\n\n\t You are welcome!!\n\n");
   }
                          /* \n ��ʾ����; \t ��ʾ�ƶ�8���ַ�λ*/
void main()
  {
     int flag=1;                        /*�������ͱ�������ֵ*/
     char ch;                           /*�����ַ�����*/
     while(flag)                        /*ѭ������*/
       {
	 printf("\n Input 'F' or 'f' to start the program print,\n other to exit:");
	 ch=toupper(getchar());         /*�õ���д�ַ�*/
	 getchar();                     /*ȥ���س���*/
	 if(ch=='F')
	   print();                     /*ִ���Ӻ���*/
	 else
	   flag=0;
       }
     return;                            /*����*/
  }

