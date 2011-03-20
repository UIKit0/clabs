 #include "stdio.h"
 #include "stdlib.h"                               /*Ӧ��malloc����*/
 #include "ctype.h"                                /*Ӧ��toupper����*/
 #include "string.h"                               /*Ӧ��strcpy����*/
 #define  LENGTH  sizeof(struct student)           /*�ڴ�ռ�*/
 static int n=0;
 struct student                                    /*����ṹ��*/
           {
              long number;                         /*ѧ��*/
	      char name[20];                       /*����*/
	      struct student *next;                /*����ָ��*/
           };
 struct student *new(struct student *head)
    {
      char numstr[20];
      struct student *p,*p1=head,*p2=head;
      p=(struct student *)malloc(LENGTH);          /*���ٿռ�*/
      printf("\n Input the new record`s number:"); /*��������*/
      gets(numstr);
      p->number=atol(numstr);
      printf("\n Input the new record`s name:");
      gets(p->name);
      if(p->number>0)                              /*ȷ��λ��*/
         {
           if(head==NULL)                          /*����ձ�*/
              {
                head=p;
		p->next=NULL;
		n++;
              }
	   else
	     {
	       while((p->number>p1->number)&&(p1->next!=NULL))
                 {
                   p2=p1;                          /*ȷ��λ��*/
                   p1=p1->next;
                 }
	       if(p->number<p1->number)
		 {
		   if(head==p1)                     /*�����ͷ*/
		     {
		       head=p;
		       p->next=p1;
		       n++;
		     }
		   else                            /*�������*/
		     {
		       p2->next=p;
		       p->next=p1;
		       n++;
		     }
		 }
               else if(p->number==p1->number)      /*����򸲸�*/
		  strcpy(p1->name,p->name);
	       else if(p1->next==NULL)             /*�����β*/
		 {
		   p1->next=p;
	           p->next=NULL;
	           n++;
	         }
	     }
	  }
      else
	 printf("\n Input wrong number! \n");       /*����ѧ��*/
      return(head);
    }
 void list(struct student *head)                    /*�����¼*/
    {
      struct student *p=head;
      int i=1;
      if(head!=NULL)
        {
	  printf("\n Now  %d records are:\n\n record \t number \t name \n",n);
             do{
		 printf("\n %6d \t %-16ld",i++,p->number);
                 puts(p->name);
                 p=p->next;
               }while(p!=NULL);
	}
      else
	 printf("\n\n It is empty! \n\n");
    }
 struct student *delete(struct student *head)       /*ɾ����¼*/
   {
     struct student *p1,*p2;
     long k;
     char numstr[20];
     printf("\n Input the number that you want to delete:");
     k=atol(gets(numstr));
     if(head==NULL)                                 /*�ձ�*/
       printf("\n this is an empty list!\n");
     else if(head->number==k)                       /*ɾ��ͷ*/
       {
	 p1=head;
	 head=head->next;
	 free(p1);                                  /*�ͷſռ�*/
         n--;
       }
     else                                           /*�Ǳ�ͷ*/
       {
	 p1=head;
	 while(p1->number!=k&&p1->next!=NULL)
	   {
	     p2=p1;                                 /*ȷ��λ��*/
	     p1=p1->next;
	   }
	 if(p1->number==k)                          /*������ɾ��*/
	   {
	     p2->next=p1->next;
	     free(p1);                              /*�ͷſռ�*/
	     n--;
           }
	 else                                       /*��ʾ������Ϣ*/
	   printf("\n The record is not in this list.\n");
	}
      return(head);
    }
 main()
   {
     struct student *head;
     char ch;
     int  flag=1;
     if(n==0)
        head=NULL;
     while(flag)                                   /*ͨ�������*/
        {
	  printf("\n Input 'N' or 'n' to input new record,'L' or 'l' to list all record,\n 'D' or 'd' to delete a record,other to exit:");
          ch=toupper(getchar());
          getchar();
          if(ch=='N')
            head=new(head);                        /*д������*/
          else if(ch=='L')
            list(head);                            /*��ʾ��¼*/
          else if(ch=='D')                         /*ɾ������*/ 
	    head=delete(head);
          else
            flag=0;
         }
      return;
    }