#include<bits/stdc++.h>
using namespace std;
struct symbolTable
{
    int sl;
    char name[15];
    char idType[15];
    char dataType[15];
    char scope[15];
    char value[15];
}st[100];
char tokens[1000];
char temp[2];
int n;
int tot;
char keywords[32][20] = {"auto","break","case","char","const",
                         "continue","default","do","double","else",
                         "enum","extern","float","for","goto","if",
                         "int","long","register","return","short",
                         "signed","sizeof","static","struct","switch",
                         "typedef","union","unsigned","void","volatile",
                         "while"};

char operators[24][3]={ "+","-","/","*","=","==","%","++","--","+=","-=",">","<",">=","<=","!=","!","&&","||","&","|","^","<<",">>" };
char seperators[8][2]={ ",",";","(",")","[","]","{","}" };

FILE *p1,*p2,*p3;

int kw(char lexeme[])
{
    int found=0;
    for(int i=0;i<32;i++)
    {
        if((strcmp(lexeme,keywords[i]))==0)
        {
            found=1;
            break;
        }
    }
    return found;
}

int op(char lexeme[])
{
    int found=0;
    for(int i=0;i<24;i++)
    {
        if((strcmp(lexeme,operators[i]))==0)
        {
            found=1;
            break;
        }
    }
    return found;
}

int id(char lexeme[])
{
    int found=0;
    if(lexeme[0]=='_' || isalpha(lexeme[0]))
    {
        found=1;
        for(int i=1;i<strlen(lexeme);i++)
        {
            if(isalpha(lexeme[i]) || lexeme[i]=='_' || isdigit(lexeme[i]))
            {
                continue;
            }
            else
            {
                found=0;
                break;
            }
        }
    }
    return found;
}

int sep(char lex[])
{
    int found=0;
    for(int i=0;i<8;i++)
    {
        if((strcmp(lex,seperators[i]))==0)
        {
            found=1;
            break;
        }
    }
    return found;
}

int num(char lex[])
{
    int i=0, l=strlen(lex), s;
    if(isdigit(lex[i]))
    {
        s=1;
        i++;
    }
    else if(lex[i]=='.')
    {
        s=2;
        i++;
    }
    else s=0;
    if(s==1)
        for( ; i<l; i++)
        {
            if(isdigit(lex[i]))
                s=1;
            else
                if(lex[i]=='.')
                {
                    s=2;
                    i++;
                    break;
                }
                else
                {
                    s=0;
                    break;
                }
        }
    if(s==2)
        if(isdigit(lex[i]))
        {
            s=3;
            i++;
        }
        else
            s=0;
    if(s==3)
    for(; i<l; i++)
    {
        if(isdigit(lex[i]))
            s=3;
        else
        {
            s=0;
            break;
        }
    }
    if(s==1)
    {
       // fprintf(p2,"[num %s]",lex);
    }
    else if(s==3)
    {
        //fprintf(p2,"[num %s]",lex);
        s=1;
    }
    return s;
}

void removeComment()
{

    FILE *p1,*p2;
    char c;

    p1 = fopen("input1.c","w");
    printf("Write your code here : \n");

    while(1)
    {

        scanf("%c",&c);
        if(c == '\t')
            break;
        else
        {
            fputc(c, p1);
        }
    }

    fclose(p1);

    p1 = fopen("input1.c", "r");
    p2 = fopen("output.txt", "w");

    int sl = 0;
    int st = 0;

    if(!p1)
    {
        printf("\nFile not found!");
    }

    else
    {
        while((c = fgetc(p1)) != EOF)
        {
            if(c == '/')
            {
                sl++;
            }
            if(c == '*')
            {
                st++;
            }
            if(sl==2 && st==0 && c =='\n')
            {
                sl=0;
            }
            else if(sl==2 && st==2 && c == '\n')
            {
                sl=0;
                st=0;
            }
            else if(sl==0 && st==0 && c != '\n')
            {
                fputc(c, p2);
            }
        }
    }

    fclose(p1);
    fclose(p2);
}
void display()
{
    printf("\n\nSymbol Table: \n");
    cout<<setw(9)<<"Sl No."<<setw(9)<<"Name"<<setw(9)<<"Id Type"<<setw(9)<<"dataType"<<setw(9)<<"Scope"<<setw(9)<<"Value"<<endl;
    for(int i=0;i<100;i++)
    {
        if(st[i].sl==-1)
            break;
        cout<<setw(9)<<st[i].sl<<setw(9)<<st[i].name<<setw(9)<<st[i].idType<<setw(9)<<st[i].dataType<<setw(9)<<st[i].scope<<setw(9)<<st[i].value<<endl;
    }
}

void update(char *name,char *id, char *data,char *scope,char *val)
{
    int i=0;
    while(st[i].sl!=-1)
    {
        if(strcmp(name,st[i].name) == 0 && strcmp(id,st[i].idType) == 0 && strcmp(scope,st[i].scope) == 0)
        {
            if(strcmp(val,"")!=0)
                strcpy(st[i].value,val);

        }
        i++;
    }
}
int _search(char *name,char *id, char *data,char *scope,char *val)
{
    int i=0;
    int f=0;
    while(st[i].sl!=-1)
    {
        if(strcmp(name,st[i].name) == 0 && strcmp(id,st[i].idType) == 0 && strcmp(scope,st[i].scope) == 0)
        {
            if(strcmp(val,st[i].value)!=0)
            {
                f=1;

            }
            else
                f=-1;
        }
        i++;
    }
    return f;
}
void insertT(char *name,char *id, char *data,char *scope,char *val)
{
    n=-1;
    for(int i=0;i<100;i++)
    {
        if(st[i].sl!=-1)
            n++;
    }
    int f =_search(name,id,data,scope,val);
    if(f == 0)
    {
        n++;
        st[n].sl=n+1;
        strcpy(st[n].dataType,data);
        strcpy(st[n].idType,id);
        strcpy(st[n].scope,scope);
        strcpy(st[n].name,name);
        strcpy(st[n].value,val);
    }
    else if(f==1)
        update(name,id,data,scope,val);


}
void generateTable()
{
    char c;
    char data[50],idT[50],scope[50],name[50],val[50];
    strcpy(scope,"global");
    p2 = fopen("output.txt","r");
    p3 = fopen("identifiers.txt","w");
    while((c=fgetc(p2))!=EOF)
    {
        if(c=='[')
        {
            fputc(c,p3);
        }
        if(c=='[')
        {
            temp[0]=fgetc(p2);
            temp[1]=fgetc(p2);
            if(strcmp(temp,"id")==0)
            {
                fputs("id ",p3);
            }
        }
        if(c==' ')
        {
            while((c=fgetc(p2))!=']')
                fputc(c,p3);
            fputc(c,p3);

        }


    }
    fclose(p3);
    fclose(p2);
    p2 = fopen("identifiers.txt","r");
    p3 = fopen("temp.txt","w");
    printf("\nIdentifiers: \n");

    int j=0;
    while((c=fgetc(p2))!=EOF)
    {
        printf("%c",c);
        if(c!='[')
        {
            if(c==']')
                fputc(' ',p3);
            else
                fputc(c,p3);
        }
    }
    fclose(p2);
    fclose(p3);
    char lex[1000];
    int i;
    int state=0;
    j=0;
    p2 = fopen("temp.txt","r");
    int l=0;
    char t1[2];
    while((c=fgetc(p2))!=EOF)
    {
        char lex[50];
        int i=0,f=1;
        for(; c!=' ' && c!=EOF; i++)
        {
            lex[i]=c;
            t1[l]=c;
            if(l<1)
                l++;
            else
                l=0;
            c=fgetc(p2);

        }
        if(strlen(lex)>0)
        {

            lex[i]='\0';
            if(strcmp(lex,"id")!=0)
            {
                if(strcmp(lex,"void")==0 || strcmp(t1,"()")==0)
                {
                    f=-1;
                }
                else{
                    f=1;

                }
                int found=0;
                if(found==0)
                {
                    found=kw(lex);
                    if(kw(lex)==1)
                    {
                        found= 1;
                        if(strcmp(lex,"return")!=0)
                        {
                            strcpy(data,lex);
                            state = 1;
                        }
                    }
                }
                if(found==0 && id(lex)==1)
                {
                    found=1;
                    strcpy(name,lex);
                    if(state == 1)
                    {
                        state=2;
                    }
                    else
                        state = 0;
                }
                if(found==0)
                {
                    if(lex[0]=='(')
                    {
                        //printf("\n %c",lex[0]);
                        if(state==2)
                        {
                            strcpy(idT,"func");
                            if(f!=-1)
                                insertT(name,idT,data,"global",val);
                            strcpy(scope,name);
                            //printf("%s %s %s %s %f\n",name,idT,data,scope,val);
                            strcpy(name,"");
                            strcpy(idT,"");
                            strcpy(data,"");
                            //strcpy(scope,"");
                            strcpy(val,"");
                            state=0;
                        }
                        found=1;
                    }
                    else
                         strcpy(idT,"var");
                    state=0;
                }
                if(found==0)
                {
                    //printf("\n %c",lex[0]);
                    if(lex[0]==';' || num(lex)==1)
                    {
                        if(state==2)
                        {
                            strcpy(idT,"var");

                        }
                    }
                    state=0;
                }
                if(found==0)
                {

                    if(num(lex)==1)
                    {
                        strcpy(val,lex);
                    }
                }
                if(lex[0]==';' || lex[0]==')')
                {
                    if(f!=-1)
                        insertT(name,idT,data,scope,val);
                   // printf("%s %s %s %s %f\n",name,idT,data,scope,val);
                    strcpy(name,"");
                    strcpy(idT,"");
                    strcpy(data,"");
                    //strcpy(scope,"");
                    strcpy(val,"");
                    state=0;
                }
            }
        }
    }

}


void modTkn()
{
    printf("\nModified Token Stream: \n\n");
    char c;
    char scp[15];
    int t1=0;
    strcpy(scp,"global");
    p1=fopen("modifiedToken.txt","w");
    p2=fopen("identifiers.txt","r");
    while((c=fgetc(p2))!=EOF)
    {

        if(c!=' ')
            fputc(c,p1);
        else
        {

            fputc(c,p1);
            char lex[50];
            int j=0;
            while((c=fgetc(p2))!=']')
            {
                lex[j]=c;
                j++;
            }
            lex[j]='\0';
            for(int i=0;i<tot;i++)
            {
                if(strcmp(st[i].name,lex)==0)
                   {

                       if(strcmp(st[i].idType,"func")==0)
                       {
                           fprintf(p1,"%d",st[i].sl);
                           if(t1==0)
                              strcpy(scp,st[i].name);

                       }
                       else
                       {
                           if(strcmp(st[i].scope,scp)==0)
                           {
                                 fprintf(p1,"%d",st[i].sl);
                           }
                       }

                   }
            }
            fputc(']',p1);


        }
    }
    fclose(p1);
    fclose(p2);
    p1=fopen("modifiedToken.txt","r");
    while((c=fgetc(p1))!=EOF)
        printf("%c",c);


}
int main()
{
    for(int i=0;i<100;i++)
        st[i].sl=-1;
    removeComment();
    char c,tempC;
    p1 = fopen("output.txt", "r");
    p3=fopen("lexemes.txt","w");
    if(!p1)
        printf("\nFile can't be opened!");
    else
    {
        c=fgetc(p1);
        while(c!=EOF)
        {
            tempC=c;
            fputc(c,p3);
            c=fgetc(p1);
            if(c==';'||c==','||c=='+'||c=='-'||c=='*'||c=='/'||c=='='|| c=='('||c==')' || c=='>' || c=='<' || c=='&' || c=='|' || c=='^' || c=='!'|| c=='{')
            {
                if(tempC!=' ')
                    fprintf(p3," %c",c);
                else
                    fputc(c,p3);
                tempC=c;
                c=fgetc(p1);
                if(c!=' ' && c!=EOF && c!='=' && c!=tempC)
                    fputc(' ',p3);
                else if(c=='='||c==tempC)
                {
                    fprintf(p3,"%c ",c);
                    c=fgetc(p1);
                }
            }
            else if(tempC==';'||tempC==','||tempC=='+'||tempC=='-'||tempC=='*'||tempC=='/'||tempC=='='|| tempC=='('||tempC==')' || tempC=='>' ||
            tempC=='<' || tempC=='&' || tempC=='|' || tempC=='^' || tempC=='!'|| tempC=='{' || tempC=='}')
            {
                if(c!=' ')
                    fputc(' ',p3);
            }
        }
    }
    fclose(p1);
    fclose(p3);
    p3 = fopen("lexemes.txt","r");
    p2 =fopen("lexemes1.txt","w");
    int syntaxSpace = 0;
    int codeStart = 0;
    while( (c = fgetc(p3)) != EOF ){
        if(c == 32 && syntaxSpace == 0 && codeStart == 1){
            fputc(32,p2);
            syntaxSpace = 1;
            continue;
        }
        else if(c == 32 && syntaxSpace == 1 && codeStart == 1){
            continue;
        }
        else if(c != 32){
            fputc(c,p2);
            codeStart = 1;
            syntaxSpace = 0;
        }
    }
    fclose(p3);
    fclose(p2);
    p3 = fopen("lexemes.txt","r");
    p2=fopen("output.txt","w");
    while((c=fgetc(p3))!=EOF){
        char lex[1000];
        int i=0;
        for(;c!=' ' && c!='\n' && c!=EOF;i++)
        {
            lex[i]=c;
            c=fgetc(p3);
        }
        if(strlen(lex)>0){
            lex[i]='\0';
            int found=0;
            if(found==0)
            {
                found=sep(lex);
                if(found==1)
                    fprintf(p2,"[sep %s]",lex);
            }
            if(found==0)
            {
                found=op(lex);
                if(found==1)
                    fprintf(p2,"[op %s]",lex);
            }
            if(found==0)
            {
                found=kw(lex);
                if(found==1)
                    fprintf(p2,"[kw %s]",lex);
            }
            if(found==0)
            {
                found=id(lex);
                if(found==1)
                    fprintf(p2,"[id %s]",lex);
            }
            if(found==0)
            {
                found=num(lex);
                if(found==1)
                    fprintf(p2,"[num %s]",lex);
            }
            if(found==0)
            {
                fprintf(p2,"[unkn %s]",lex);
            }
        }
        if(c==EOF)
            break;
    }
    fclose(p3);
    fclose(p2);

    printf("\n\nLexemes:\n\n");
    p3 = fopen("lexemes1.txt","r");
    while((c=fgetc(p3))!=EOF)
		printf("%c",c);
    fclose(p3);

    printf("\n\nOutput:\n\n");
    p2 = fopen("output.txt","r");
    int k=0;
    while((c=fgetc(p2))!=EOF)
		{
		    printf("%c",c);
		}
    fclose(p2);

    printf("\n");
    generateTable();
    display();
    modTkn();
    return 0;
}

