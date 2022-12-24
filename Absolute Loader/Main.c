#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

int starting_address,relocation_address,number_of_adderss_spaces,list_instructions[50];
char address_values[10][50],element[50];

void print_the_condition(){
	for(int i=0;i<number_of_adderss_spaces;i++){
		printf("%d    %s\n",list_instructions[i],address_values[i]);
	}
}

int main(){
	printf("Enter the Starting Address : ");
	scanf("%d",&starting_address);
	
	printf("Enter the number of address spaces required : ");
	scanf("%d",&number_of_adderss_spaces);
	
	for(int i=0;i<number_of_adderss_spaces;i++){
		list_instructions[i]=starting_address;
		printf("Enter the value at address %d  : ",starting_address);
		scanf("%s",&element);
		strcpy(address_values[i],element);
		starting_address+=1;
	}

	printf("\nYour Input is as follows :\n");
	print_the_condition();

	printf("\nEnter Relocating Address : ");
	scanf("%d",&relocation_address);

	for(int i=0;i<number_of_adderss_spaces;i++){
		list_instructions[i]=relocation_address;
		relocation_address+=1;
	}
	printf("\nFinal Output After Relocation : \n");
	print_the_condition();	
	
}