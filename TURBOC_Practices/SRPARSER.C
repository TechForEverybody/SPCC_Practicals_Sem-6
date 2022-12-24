#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 10
char GRAMMER[MAX][MAX];
static char input[MAX];
static char STACK[MAX];
int TOP=-1,number_of_productions;
void main(){
	static int i,j,k,l,m,n,counter,pre;
	static char comparing_string[MAX];
	i=j=k=l=m=n=counter=0;
	clrscr();
	printf("Enter Number of Productions: ");
	scanf("%d",&number_of_productions);
	for(i=0;i<number_of_productions;i++){
		printf("Enter Production %d  E->",i+1);
		scanf("%s",&GRAMMER[i]);
	}
	printf("Enter The input string : ");
	scanf("%s",&input);
	for(i=0;i<strlen(input);i++){
		STACK[++TOP]=input[i];
		printf("$ ");
		for(j=0;j<strlen(input);j++){
			if(j<=TOP){
				printf("%2c",STACK[j]);
			}
			else{
				printf("  ");
			}
		}
		printf("\t");
		for(j=0;j<strlen(input);j++){
			if(j>i){
				printf("%2c",input[j]);
			}
			else{
				printf("  ");
			}
		}
		printf(" $");

		printf("\t shift %c\n",input[i]);
		check_again:

		for(k=TOP;k>=0;k--){
			counter=0;
			for(l=k;l<=TOP;l++){
				comparing_string[counter++]=STACK[l];
			}
//			printf("\n%s\n",comparing_string);
			for(l=0;l<5;l++){
				if(strcmp(GRAMMER[l],comparing_string)==0){
						printf("$ ");
		for(j=0;j<strlen(input);j++){
			if(j<=TOP){
				printf("%2c",STACK[j]);
			}
			else{
				printf("  ");
			}
		}
		printf("\t");
		for(j=0;j<strlen(input);j++){
			if(j>i){
				printf("%2c",input[j]);
			}
			else{
				printf("  ");
			}
		}
		printf(" $");

					printf("\treducing %s with E->%s\n",comparing_string,GRAMMER[l]);
					pre=TOP;
					TOP=TOP-strlen(comparing_string)+1;
					STACK[TOP]='E';
					for(m=TOP+1;m<=pre;m++){
						STACK[m]='\0';
					}
					for(m=0;m<counter;m++){
						comparing_string[m]='\0';
					}
					goto check_again;
				}


			}
			for(l=0;l<counter;l++){
				comparing_string[l]='\0';
			}


		}



//		printf("\n");
	}
						printf("$ ");
		for(j=0;j<strlen(input);j++){
			if(j<=TOP){
				printf("%2c",STACK[j]);
			}
			else{
				printf("  ");
			}
		}

		if(STACK[TOP]=='E' || TOP==0){
			printf("\n STRING IS ACCEPTED");
		}else{
		 printf("\n STRING IS REJECTED");
		}



 getch();
}