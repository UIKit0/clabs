 #include "stdio.h"
 #define  N  4                           /*����*/
 #define  M  5                           /*����*/
 void search(int (*p)[N])              /*ָ��ָ����n��Ԫ�ص�����*/
    {
      int i,j,flag;
      for(i=0;i<M;i++)
        {
          flag=0;
          for(j=0;j<N;j++)
	    if(*(*(p+i)+j)<60)           /*�Ƚ���Ӧ�ɼ�:��i+1�˵�j+1��*/
               flag=1;                  /*С��60�����*/
           if(flag==1)                  /*������������ʾ*/
             {
               printf("\n\n N0.%d is flunked,score are:",(i+1));
               for(j=0;j<N;j++)
		  printf("%5.1d",(*(*(p+i)+j)));

             }
         }
      }

 main()
  {
    int i,j;
    int score[M][N];
    for(i=0;i<M;i++)                    /* �õ���ʼ�ɼ�*/
      {
	printf("\n Input %d scores of N0.%d :\n",N,i+1);
        for(j=0;j<N;j++)
	   scanf("%d",&score[i][j]);
      }
    search(score);
    return;
  }