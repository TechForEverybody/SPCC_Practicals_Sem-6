#include "MAIN.h"
#include<stdio.h>
#include<conio.h>

void main(){
	int num1,num2,addition;
	clrscr();
	printf("Enter Value of num1 : ");
	scanf("%d",&num1);

	printf("Enter Value of num2 : ");
	scanf("%d",&num2);
	addition=add(num1,num2);
	printf("\nADDITION OF num1 and num2 is %d",addition);
	getch();
}