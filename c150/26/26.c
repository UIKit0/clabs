 #include "stdio.h"
 #define  N  5
 #define  M  20
 main()
   {
     struct                           /*����ṹ��*/
       {
	 char name[M];                /*����*/
	 int age;                     /*����*/
	 char sex;                    /*�Ա�*/
	 char job;                    /*ְҵ*/
	 union                        /*���干����*/
	    {
	      int class;              /*�༶*/ 
	      char office[M];         /*�칫��*/ 
	    }depart;                  /*��λ*/
	}info[N];
      int i;
      for(i=0;i<N;i++)
	{
	  printf("\n Input name:");
	  gets(info[i].name);
	  printf("\n Input age:");
	  scanf("%d",&info[i].age);
	  getchar();
	  printf("\n Input sex(m/w):");
	  info[i].sex=getchar();
	  getchar();
	  printf("\n Input job(s/t):");
	  info[i].job=getchar();
	  getchar();
	  if(info[i].job=='s')          /*����ְҵ��ͬѡ��λ����*/
	     {
	       printf("\n Input class:");
	       scanf("%d",&info[i].depart.class);
	       getchar();
	     }
	   else if(info[i].job=='t')
	      {
		printf("\n Input office:");
		gets(info[i].depart.office);
	      }
	   else
	      {
		printf("\n Input wrong job,return!");
		i--;
	      }
	 }
     printf("\n name \t\t age \t sex \t job \t depart ");
     for(i=0;i<N;i++)
       {
	 if(info[i].job=='s')          /*����ְҵ��ͬѡ��λ����*/
	    printf("\n %-15s %-3d \t  %c \t  %-6c %-20d",info[i].name,info[i].age,info[i].sex,info[i].job,info[i].depart.class);
	 else
	    printf("\n %-15s %-3d \t  %c \t  %-6c %-20s",info[i].name,info[i].age,info[i].sex,info[i].job,info[i].depart.office);
	}
     return;
   }