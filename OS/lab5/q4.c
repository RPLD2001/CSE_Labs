#include<stdio.h>
#include<stdlib.h>

int main(){
	FILE *fout;
	int num = 0;
	char filename[100];
	printf("Enter name of binary file to open: ");
	scanf("%s",filename);
	fout = fopen(filename, "wb+");

	printf("Enter any 3 numbers: \n");
	for(int i=0;i<3;i++){
		scanf("%d", &num);
		fwrite(&num, sizeof(int), 1, fout);
	}

	printf("Writing complete!\n");
	fclose(fout);

	printf("Now, reading the binary file...\n");

	fout = fopen(filename, "rb");

	for(int i=0;i<3;i++){
		fread(&num, sizeof(int), 1, fout);
		printf("%d\n", num);
	}
	fclose(fout);

	return 0;
}