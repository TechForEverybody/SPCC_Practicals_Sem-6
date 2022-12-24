#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
	FILE *ALP = NULL;
	FILE *MOT = NULL;
	FILE *POT = NULL;
	FILE *ST = NULL;
	FILE *MC=NULL;
	char *result, codeline[50], *words[10], word[50], *motresult, *potresult, motline[50], potline[50], *motword, *potword;
	static int starting_address = 2000, i;
	static int issymbol = 1;
	clrscr();
	ALP = fopen("ALPFILE.txt", "r");
	ST = fopen("ST.txt", "w");
	MC=fopen("MC.txt","w");
	result = fgets(codeline, 50, ALP);
	while (result != NULL)
	{
		words[0] = strtok(codeline, " ");
		words[1] = strtok(NULL, " ");
		fprintf(MC,"%d",starting_address);
		fputs(" ",MC);
		for (i = 0; i < 2; i++)
		{

		issymbol=1;
			strcpy(word, words[i]);
					if(word[strlen(word)-1]=='\n'){
						word[strlen(word)-1]='\0';
				}

			printf("%s", word);
			MOT = fopen("MOT.txt", "r");
			motresult = fgets(motline, 50, MOT);
			while (motresult != NULL)
			{
				motword = strtok(motline, " ");
				if (strcmp(word, motword) == 0)
				{
					motword=strtok(NULL," ");
					fputs(motword,MC);
					fputs(" ",MC);
					printf("matched with mot %s", word);
					issymbol = 0;
					break;
				}
				motresult = fgets(motline, 50, MOT);
			}
			fclose(MOT);
			POT = fopen("POT.txt", "r");
			potresult = fgets(potline, 50, MOT);
			while (potresult != NULL)
			{
				potword = strtok(potline, " ");
				if (strcmp(word, potword) == 0)
				{
					printf("matched with pot %s", word);
					issymbol = 0;

				}
				potresult = fgets(potline, 50, POT);
			}
			fclose(POT);
			if (issymbol == 1)

			{
				printf("It is a Symbol --> %s", word);
				fputs(word	, ST);
				fputs(" ", ST);
				fputs(" VAR ", ST);
				//putw(starting_address,ST);
				fprintf(ST,"%d",starting_address);
				fputs("\n", ST);
				fputs("____",MC);
			}
			starting_address++;
		}
		fputs("\n",MC);
		result = fgets(codeline, 50, ALP);
	}

	fclose(ALP);
	fclose(MOT);
	fclose(POT);
	fclose(ST);

	getch();

}
