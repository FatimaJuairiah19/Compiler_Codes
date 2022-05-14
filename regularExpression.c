
// Regular Expression
//(I)*a_dd+ where I=[a-z] and d=[0-9]

#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

int main(void)
{

    char a[100];
    printf("Input String:");
    printf("\n");
    gets(a);
    int len= strlen(a);
    int i,j,k,flag=0,uscore=0,check=0;


    if (isdigit(a[0]))
    {

        for(i=1; i<len; i++)
        {

            if(isdigit(a[i]) &&(uscore==0)){

                continue;

            }

            else if (a[i]=='_')
            {
                uscore=1;
                continue;
            }

            else if(isalpha(a[i]) && (uscore==0) && check<1){
                check++;
                continue;
            }
            else if((isalpha(a[i])) && (uscore==1))
            {
                break;
            }

           flag=1;
        }


    }

   if(flag==1)
        printf("string follows the pattern\n");
   else
        printf("string does not follow the pattern");

    return 0;

}
