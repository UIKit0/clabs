 #include "stdio.h"
 #define  N  50                           /*����ַ�����*/
 main()
  {
    int  up=0,                            /*��д��ĸ*/
         low=0,                           /*Сд��ĸ*/
         digit=0,                         /*����*/
         space=0,                         /*�ո�*/
	 other=0;                         /*�����ַ�*/
     char *p,s[N];
     printf("\n the string:\n");
     p=s;                                 /*ָ��ָ���ַ���*/
     gets(p);                             /*�õ��ַ���*/
     while(*p!='\0')                      /*ѭ����λ�ж�*/
        {
          if((*p>='A')&&(*p<='Z'))
             up++;
	  else if((*p>='a')&&(*p<='z'))
             low++;
          else if(*p==' ')
             space++;
          else if((*p>='0')&&(*p<='9'))
              digit++;
          else
              other++;                    /*�������Լ�*/
          p++;                            /*�ж���һ���ַ�*/
        }
      printf("\n up    letter:%d\n low   letter:%d\n space letter:%d\n digit letter:%d\n other letter:%d\n",up,low,space,digit,other);
      return;
   }