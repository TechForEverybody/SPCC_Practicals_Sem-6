#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
int passnumber=2;

void main(){
FILE *ALPPointer=NULL;
FILE *MNTPointer=NULL;
FILE *MDTPointer=NULL;
FILE *IFPointer=NULL;
FILE *OUTPUTPointer=NULL;
char *result,*mntresult,*mdtresult,*ifresult,codeline[50],mntline[50],mdtline[50],*word,*mntword,*mdtword;
char *macroname,*mntindex,backupline[50];
char index='1';
static int is_macro_call_encountered=0;
clrscr();
switch(passnumber){
 case 1:
 ALPPointer=fopen("ALP.txt","r");
 MNTPointer=fopen("MNT.txt","w");
 MDTPointer=fopen("MDT.txt","w");
 IFPointer=fopen("IF.txt","w");

 result=fgets(codeline,50,ALPPointer);
 while(result!=NULL){
			strcpy(backupline,codeline);
		   word=strtok(codeline," ");
		   if(strcmp("MACRO",word)==0){
				macroname=strtok(NULL," ");
				if(macroname[strlen(macroname)-1]=='\n'){
					macroname[strlen(macroname)-1]='\0';
				}
				fputs(macroname,MNTPointer);
				fputs(" 0 #",MNTPointer);
				fputc(index,MNTPointer);
				fputs("\n",MNTPointer);
				result=fgets(codeline,50,ALPPointer);
				fputs("#",MDTPointer);
				fputc(index++,MDTPointer);
				fputs("\n",MDTPointer);
				while(result!=NULL && strcmp(codeline,"MEND")!=0 && strcmp(codeline,"MEND\n")!=0){
					 fputs(codeline,MDTPointer);
					 result=fgets(codeline,50,ALPPointer);

				}
				fputs("MEND\n",MDTPointer);
		   }
		   else{
				printf("%s",backupline);
				fputs(backupline,IFPointer);
		   }
 result=fgets(codeline,50,ALPPointer);

 }

 break;
 case 2:
	IFPointer=fopen("IF.txt","r");
	OUTPUTPointer=fopen("OUTPUT.txt","w");
	 result=fgets(codeline,50,IFPointer);
	 while(result!=NULL){
		strcpy(backupline,codeline);
		word=strtok(codeline," ");
			if(word[strlen(word)-1]=='\n'){
		 word[strlen(word)-1]='\0';
		}
//		printf("\nword -> %s and length is %d",word,strlen(word));

		is_macro_call_encountered=0;
		 MNTPointer=fopen("MNT.txt","r");
		 mntresult=fgets(mntline,50,MNTPointer);
		 while(mntresult!=NULL){
				mntword=strtok(mntline," ");
				if(strcmp(word,mntword)==0){
//					printf("\n Macro call is encountered for  %s",word);
					mntindex=strtok(NULL," ");
					mntindex=strtok(NULL," ");
					is_macro_call_encountered=1;
					break;
				}

			 mntresult=fgets(mntline,50,MNTPointer);
		 }
		 fclose(MNTPointer);
		 if(is_macro_call_encountered==1){
			MDTPointer=fopen("MDT.txt","r");
			mdtresult=fgets(mdtline,50,MDTPointer);
			while(mdtresult!=NULL){
				if(strcmp(mntindex,mdtline)==0){
					mdtresult=fgets(mdtline,50,MDTPointer);
					while(mdtresult!=NULL && strcmp(mdtline,"MEND")!=0 && strcmp(mdtline,"MEND\n")!=0){
							printf("%s",mdtline);
							fputs(mdtline,OUTPUTPointer);
							mdtresult=fgets(mdtline,50,MDTPointer);

						}
				}

				mdtresult=fgets(mdtline,50,MDTPointer);

			}
			fclose(MDTPointer);
		 }
		 else{
				printf("%s",backupline);
				fputs(backupline,OUTPUTPointer);
		 }



		result=fgets(codeline,50,IFPointer);

   }


 break;



}







fclose(ALPPointer);
fclose(MNTPointer);
fclose(MDTPointer);
fclose(IFPointer);
fclose(OUTPUTPointer);
free(result);
free(mntresult) ;
free(mdtresult);
free(ifresult);
free(word);
free(mntword);
free(mdtword);

 getch();
}