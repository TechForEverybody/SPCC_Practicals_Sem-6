#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 10
char KEYWORDS[MAX][MAX]={
 "void",
 "if",
 "while",
 "include",
 "define",
 "switch",
 "int",
 "char",
 "double",
 "float"
};

void main(){
	FILE *inputPointer=NULL;
	char *result,codeline[50];
	static char comparing_string[50];
	static int i,j,counter,iskeyword;
	clrscr();
	inputPointer=fopen("lexi.c","r");
	result=fgets(codeline,50,inputPointer);
	while(result!=NULL){
//		printf("%s",codeline);
		for(i=0;i<strlen(codeline);i++){
//			printf("%c",codeline[i]);
			if(codeline[i]=='\n' || codeline[i]=='\t' || codeline[i]=='\0' || codeline[i]==' '){
//				printf("%c",codeline[i]);
			} else{
//				printf("%c",codeline[i]);
				if(isdigit(codeline[i])){
					printf("\n %c",codeline[i]);
					for(j=i+1;j<strlen(codeline);j++){
						if(isdigit(codeline[j])==0 && codeline[j]!='.'){
							break;
						}
						else{
							i++;
							printf("%c",codeline[j]);
						}
					}
					printf(" --> Literal");
				}
				else if(isalnum(codeline[i])){
					printf("");
					counter=0;
					comparing_string[counter++]=codeline[i];
					for(j=i+1;j<strlen(codeline);j++){
						if(isalnum(codeline[j])==0 && codeline[j]!='.'){
							break;
						}
						else{
							i++;
							comparing_string[counter++]=codeline[j];
						}
					}
					iskeyword=0;
					for(j=0;j<MAX;j++){
						if(strcmp(comparing_string,KEYWORDS[j])==0){
							iskeyword=1;
							break;
						}
					}
					if(iskeyword==1){
					 printf("\n%s --> Keyword",comparing_string);
					}
					else{
					 printf("\n%s --> Identifier",comparing_string);
					}
				  for(j=0;j<counter;j++){
						comparing_string[j]='\0';
				  }

				}
				else{
					printf("\n %c --> Terminal",codeline[i]);
				}
			}
		}
		result=fgets(codeline,50,inputPointer);
	}


  fclose(inputPointer);
  free(result);

getch();
}