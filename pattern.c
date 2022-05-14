
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(void)
{

    char a[100];
    printf("Input String");
    printf("\n");
    gets(a);
    int len = strlen(a);
    int i,j,k, flag = 0,checkPrev=0, uscore=0;

    if(a[0]=='c')
    {

        for(i=1; i<len; i++)
        {

            if(isalpha(a[i]))
                continue;
            else if (a[i]=='_')
            {
                uscore=1;
                continue;
            }


            else if((isdigit(a[i])) && (uscore==1))
            {
                for(j=1; j<i; j++)
                {
                    if(a[j]=='_')
                        checkPrev=1;


                }
            }
             else{
               break;
            }
            //continue;


        }
        flag =1;

    }

    if(flag==1 && checkPrev==1)
        printf("string follow the pattern\n");
    else
        printf("string does not follow the pattern");

    return 0;
}

