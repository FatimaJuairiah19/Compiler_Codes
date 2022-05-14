#include<stdio.h>

int main()
{
    FILE *p1,*p2;
    char c;
    int s=0,star=0,underCmntSec=0;

    p1=fopen("input_assignment.txt","w");
    printf("write the code (press 3 to exit):");
    while(1)
    {
        scanf("%c",&c);
        if(c=='3')
            break;
        else
            fputc(c,p1);

    }
    printf("End");
    fclose(p1);
    p1=fopen("input_assignment.txt","r");
    p2=fopen("Output_assignment.txt","w");
    if(!p1)
        printf("\nFile can't be opened!");
    else
    {

        while((c=fgetc(p1))!=EOF)
        {
            if(c=='/' && c++ =='/')
            {
                s=s+1;
            }
            if(c=='/' && c++ =='*')
            {
                 star++;
                 while((c=fgetc(p1))!=EOF){
                    if(c=='*' && c++=='/')
                    {
                         underCmntSec++;
                    }
                 }
            }

            if(s==2 && star==0 && c=='\n')
                s=0;

            if(s==2 && star==2 && c=='\n')
            {
                s=0;
                star=0;
                underCmntSec=0;
            }
            if(s==0 && star==0 && c!='\n' && underCmntSec==0)
                fputc(c,p2);


        }

    }
    fclose(p1);
    fclose(p2);
    return 0;

}
/*
#include<stdio.h>

int main(void)
{

//single line comment

printf (“Hello”);
/*multi
line
commment*/

//printf(“World”);
//return 0
