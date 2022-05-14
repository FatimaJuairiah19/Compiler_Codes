#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char keywords[32][20] = {"auto","break","case","char","const",
                         "continue","default","do","double","else",
                         "enum","extern","float","for","goto","if",
                         "int","long","register","return","short",
                         "signed","sizeof","static","struct","switch",
                         "typedef","union","unsigned","void","volatile",
                         "while","main"
                        };

char operators[24][3]={"+","-","/","*","=","==","%","++","--","+=","-=",">","<",">=","<=","!=","!","&&","||","&","|","^","<<",">>"};
char seperators[8][2]={",",";","(",")","[","]","{","}"};

FILE *p1,*p2,*p3;

int kw(char lexeme[]){
    int got=0;
    for(int i=0;i<32;i++){
        if((strcmp(lexeme,keywords[i]))==0){
            got=1;
            break;
        }
    }
    if(got==1)
        fprintf(p2,"[kw %s]",lexeme);
    return got;
}

int op(char lexeme[]){
    int got=0;
    for(int i=0;i<24;i++){
        if((strcmp(lexeme,operators[i]))==0){
            got=1;
            break;
        }
    }
    if(got==1)
        fprintf(p2,"[op %s]",lexeme);
    return got;
}

int id(char lexeme[]){
    int got=0;
    if(lexeme[0]=='_' || (lexeme[0]>='A' && lexeme[0]<='z')){
        got=1;
        for(int i=1;i<strlen(lexeme);i++){
            if((lexeme[0]>='A' && lexeme[0]<='z') || lexeme[i]=='_' || isdigit(lexeme[i])){
                continue;
            }
            else{
                got=0;
                break;
            }
        }
    }
    if(got==1)
        fprintf(p2,"[id %s]",lexeme);
    return got;
}

int sep(char lex[]){
    int got=0;
    for(int i=0;i<8;i++){
        if((strcmp(lex,seperators[i]))==0){
            got=1;
            break;
        }
    }
    if(got==1)
        fprintf(p2,"[sep %s]",lex);
    return got;
}


int numLiteral(char lex[]){
    int i=0, l=strlen(lex), s;
    if(isdigit(lex[i])) {
        s=1;
        i++;
    }
    else if(lex[i]=='.') {
        s=2;
        i++;
    }
    else s=0;
    if(s==1)
        for( ; i<l; i++){
            if(isdigit(lex[i]))
                s=1;
            else
                if(lex[i]=='.') {
                    s=2;
                    i++;
                    break;
                }
                else {
                    s=0;
                    break;
                }
        }
    if(s==2)
        if(isdigit(lex[i])) {
            s=3;
            i++;
        }
        else
            s=0;
    if(s==3)
    for(; i<l; i++) {
        if(isdigit(lex[i]))
            s=3;
        else {
            s=0;
            break;
        }
    }
    if(s==1){
        fprintf(p2,"[num %s]",lex);
    }
    else if(s==3){
        fprintf(p2,"[num %s]",lex);
        s=1;
    }
    return s;
}


int main(){
    char c,tempC;
     int s=0,star=0,underCmntSec=0,i;

    p1=fopen("input_assignment.txt","w");
    printf("write the code (press $ to exit):");
    while(1)
    {
        scanf("%c",&c);
        if(c=='$')
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
    p1 = fopen("Output_assignment.txt","r");
    p3=fopen("lexemes.txt","w");
    if(!p1)
        printf("\nFile can't be opened!");
    else
    {
        c=fgetc(p1);
        while(c!=EOF){
            tempC=c;
            fputc(c,p3);
            c=fgetc(p1);
            if(c==';'||c==','||c=='+'||c=='-'||c=='*'||c=='/'||c=='='|| c=='('||c==')' || c=='>' || c=='<' ||
               c=='&' || c=='|' || c=='^' || c=='!'|| c=='{'){
                if(tempC!=' ')
                    fprintf(p3," %c",c);
                else
                    fputc(c,p3);
                tempC=c;
                c=fgetc(p1);
                if(c!=' ' && c!=EOF && c!='=' && c!=tempC)
                    fputc(' ',p3);
                else if(c=='='||c==tempC){
                    fprintf(p3,"%c ",c);
                    c=fgetc(p1);
                }
            }
            else if(tempC==';'||tempC==','||tempC=='+'||tempC=='-'||tempC=='*'||tempC=='/'||tempC=='='||
            tempC=='('||tempC==')' || tempC=='>' || tempC=='<' || tempC=='&' || tempC=='|' ||
            tempC=='^' || tempC=='!'|| tempC=='{' || tempC=='}'){
                if(c!=' ')
                    fputc(' ',p3);
            }
        }
    }
    fclose(p1);
    fclose(p3);
    p3 = fopen("lexemes.txt","r");
    p2=fopen("output.txt","w");
    while((c=fgetc(p3))!=EOF){
        char lex[1000];

        for(i=0;c!=' ' && c!='\n' && c!=EOF;i++){
            lex[i]=c;
            c=fgetc(p3);
        }
        if(strlen(lex)>0){
            lex[i]='\0';
            int got=0;
            if(got==0)
                got=sep(lex);
            if(got==0)
                got=op(lex);
            if(got==0)
                got=kw(lex);
            if(got==0)
                got=id(lex);
            if(got==0)
                got=numLiteral(lex);
            if(got==0){
                fprintf(p2,"[unkn %s]",lex);
            }
        }
        if(c==EOF)
            break;
    }
    fclose(p3);
    fclose(p2);
    printf("Input:\n\n");
    p1 = fopen("Output_assignment.txt","r");
    while((c=fgetc(p1))!=EOF)
		printf("%c",c);
    fclose(p1);
    printf("\n\nLexemes:\n\n");
    p3 = fopen("lexemes.txt","r");
    while((c=fgetc(p3))!=EOF)
		printf("%c",c);
    fclose(p3);
    printf("\n\nOutput:\n\n");
    p2 = fopen("output.txt","r");
    while((c=fgetc(p2))!=EOF)
		printf("%c",c);
    fclose(p2);
    printf("\n");
    return 0;
}
