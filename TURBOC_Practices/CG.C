#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>



void main(){
	FILE *inputPointer=NULL;
	FILE *outputPointer=NULL;
	char *result,codeline[50],*word,*var1,*var2,*var3,*op;


	inputPointer=fopen("CG_input.txt","r");
	outputPointer=fopen("CG_output.txt","w");
	result=fgets(codeline,50,inputPointer);
	while(result!=NULL){
		op=strtok(codeline," ");
		var1=strtok(NULL," ");
		var2=strtok(NULL," ");
		if(strcmp("=",op)==0){
			fputs("MOV ",outputPointer);
			fputs(var2,outputPointer);
			fputs(",",outputPointer);
			fputs(var1,outputPointer);
			fputs("\n",outputPointer);
		}
		else{
			var3=strtok(NULL," ");
			if(var3[strlen(var3)-1]=='\n'){
				var3[strlen(var3)-1]='\0';
			}
			fputs("MOV AX,",outputPointer);
			fputs(var1,outputPointer);
			fputs("\n",outputPointer);

			if(strcmp("+",op)==0){
				fputs("ADD AX,",outputPointer);

			}
			else if(strcmp("-",op)==0){
			   fputs("SUB AX,",outputPointer);
			}

			else if(strcmp("*",op)==0){
				fputs("MUL AX,",outputPointer);
			}

			else if(strcmp("/",op)==0){
				fputs("DIV AX,",outputPointer);
			}
			fputs(var2,outputPointer);
			fputs("\nMOV ",outputPointer);
			fputs(var3,outputPointer);
			fputs(",AX\n",outputPointer);


		}
		result=fgets(codeline,50,inputPointer);

	}








getch();
}