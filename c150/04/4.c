#include "stdio.h"
#include "stdlib.h"                 /*Ӧ��random������randomize����/  
#include "ctype.h"                  /*Ӧ��toupper����*/
main()
  {
    int count,                      /*��������*/
        number,                     /*���������*/
        guess;                      /*��������*/
    char yes='Y';
    printf("\nNow let us play the game.\n Guess the number:");
    while(toupper(yes)=='Y')
      {
         count=0;
         randomize();
         number=random(100)+1;                             /*���������*/
         do{
              do{
                  printf("\nInput an integer number(1-100):");
                  scanf("%d",&guess);
                 }while(!(guess>=1&&guess<=100));
               if(guess<number)
                   printf("\nYour answer is LOW,try again.");
               if(guess>number)
                   printf("\nYour answer is HIGH,try again."); /*������Ϣ*/
               count++;
               if(count==15)
                  {
                     printf("\nThia is the %d times!Think it hard next!");
                     exit(0);                               /*15���˳�*/
                    }
	     }while(!(guess==number));                      /*��ֵ�ж�*/
           if(count<=7)
             {
               printf("\nYou have got it in %d times.\n",count);
               printf("\nCongretulations!");
             }
                else
             {
               printf("\nYou got it in %d times.\n",count);
               printf("\nI bet you can do it better");
              }
            printf("\n NEXT?(Y/N):");                         /*������Ϸ*/
            scanf(" %c",&yes);
        }
}
