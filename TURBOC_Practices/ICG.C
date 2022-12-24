#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
static char input[50];
static char sorted_operators[50];
static char tempvar='A';

void main(){
	int i,j,k,counter=0;

	clrscr();
	printf("Enter The Sring : ");
	scanf("%s",&input);
	printf("\nInput String is w = %s\n",input);
	for(i=0;i<strlen(input);i++){
		if(input[i]=='/'){
			sorted_operators[counter++]='/';
		}
	}
	for(i=0;i<strlen(input);i++){
		if(input[i]=='*'){
			sorted_operators[counter++]='*';
		}
	}
	for(i=0;i<strlen(input);i++){
		if(input[i]=='+'){
			sorted_operators[counter++]='+';
		}
	}
   for(i=0;i<strlen(input);i++){
		if(input[i]=='-'){
			sorted_operators[counter++]='-';
		}
	}
	printf("\nSorted Operators -> %s\n\n\n",sorted_operators);

	for(i=0;i<strlen(sorted_operators);i++){
		for(j=0;j<strlen(input);j++){
			if(sorted_operators[i]==input[j]){
				printf("%15s \t",input);
				printf("%c = %c %c %c\n",tempvar,input[j-1],input[j],input[j+1]);
				input[j-1]=tempvar++;
				for(k=j;k<strlen(input)-2;k++){
					input[k]=input[k+2];
				}
				for(j=strlen(input)-2;j<strlen(input);j++){
					input[k]='\0';
				}
			}

		}

	}
	printf("\n W = %c",tempvar-1);

getch();
}