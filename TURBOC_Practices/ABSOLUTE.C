#include<stdlib.h>
#include<conio.h>
#define MAX 10
static char instruction_values[MAX][MAX];
static int starting_address,relocating_address,number_of_addresses;
void main(){
	static int i=0;
	clrscr();
	printf("Enter The Starting Address : ");
	scanf("%d",&starting_address);
	printf("Enter number of address values : ");
	scanf("%d",&number_of_addresses);
	for(i=0;i<number_of_addresses;i++){
		printf("Enter The Value at address %d : ",i+starting_address);
		scanf("%s",instruction_values[i]);
	}
	printf("\n\nAddress and values before relocation : ");
	for(i=0;i<number_of_addresses;i++){
		printf("\n%d  %s ",i+starting_address,instruction_values[i]);
	}
	printf("\n\n\nEnter The Relocating Address : ");
	scanf("%d",&relocating_address);
	printf("\n\nAddress and values after relocation : ");
	for(i=0;i<number_of_addresses;i++){
		printf("\n%d  %s ",i+relocating_address,instruction_values[i]);
	}
getch();
}

