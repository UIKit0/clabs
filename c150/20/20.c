 #include "stdio.h"
 #include "string.h"               /*Ӧ��strcmp����*/
 #define LENGTH  30                /*�����ַ�����󳤶�*/
 #define N  10                     /*�����ַ�����*/
 void sort(char **p)               /*ð������*/
  {
    int i,j;
    char *pstr;
    for(i=0;i<N;i++)
      for(j=i+1;j<N;j++)
        if(strcmp(*(p+i),*(p+j))>0) /*�ȽϺ󽻻��ַ�����ַ*/
          {
            pstr=*(p+j);
            *(p+j)=*(p+i);
            *(p+i)=pstr;
           }
   }

 main()
  {
    int i;
    char *pstr[N],s[N][LENGTH];
    for(i=0;i<N;i++)
      pstr[i]=s[i];         /*����i���ַ������׵�ַ����ָ������*/
   printf("\n Input %d strings:\n", N);
    for(i=0;i<N;i++)
      gets(pstr[i]);                  /*�����ַ���*/
    sort(pstr);
    printf("\n The sorted string are:\n");
    for(i=0;i<N;i++)
      puts(pstr[i]);
    return;
  }

