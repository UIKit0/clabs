 #include "stdio.h"
 int atoi(char *p)               /*ת���Ӻ���*/
   {
     int k,number=0;
     while(*p!='\0'&&(*p>='0')&&(*p<='9'))             /*δ�������ѭ����ȡÿһλ����*/
        {
          k=*(p++)-48;
          number=10*number+k;    /*�õ�ÿһλ����*/
         }
     return number;              /*����������ֵ*/
    }
 main()
   {
     char s[10];
     int number;
	printf("\n\n Input a digit string:");
	gets(s);                     /*���������ַ���*/
     number=atoi(s);              /*����ָ��*/
     printf("\n\n %d",number);
     return;
    }