 #include "stdio.h"
 #include "stdlib.h"                                /*Ӧ��malloc����*/
 #define  LENGTH  sizeof(struct number)             /*�ڴ�ռ�*/
 struct number                                      /*����ṹ��*/
           {
	      long key;                             /*����*/
	      int count;                            /*������*/
	      struct number *next;                  /*����ָ��*/
           };
 struct number *add(long k,struct number *head)
    {
      int flag=1;
      struct number *p=head;
      while(p!=NULL&&flag==1)
          {
            if(p->key==k)
              flag=0;
            else
               p=p->next;
           }
       if(flag==0)                                  /*������֪��*/
            p->count++;
       else                                         /*�ڱ�ͷ���*/
          {
            p=head;
	    head=(struct number *)malloc(LENGTH);   /*���ٿռ�*/
            head->key=k;
            head->count=1;
            head->next=p;
           }
       return(head);
     }
 void list(struct number *p)                        /*�����¼*/
    {
      printf(" \n The result are:\n");
      while(p!=NULL)
	{
	  printf("%16ld %6d\n",p->key,p->count);
          p=p->next;
	}
    }
 main()
   {
     struct number *head=NULL;
     long k;
     printf("\n Input natural numbers,-1 to end:\n");
     scanf("%ld",&k);
     while(k>=0)
        {
          head=add(k,head);
          scanf("%ld",&k);
         }
     list(head);
     return;
   }