#include<stdio.h>
#include<stdlib.h>

void main(){
	int *arr=calloc(5,sizeof(int));
	for(int i=0;i<5;i++){
		*(arr+i)=i*i;
		printf("\n%d\t",*(arr+i));
	}
}