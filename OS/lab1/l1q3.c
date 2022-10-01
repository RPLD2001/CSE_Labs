#include<stdio.h>
#include<stdlib.h>
#include<errno.h>



int main(){
	int a = 13;
	float b = 10.23;
	char c = 'E';
	char str[] = "Rajpreet Lal Das";
	printf("a = %d, b = %f, c = %c, str = %s, Hexadecimal for a = %x\n",a,b,c,str,a);
	errno = EPERM;
	printf("Error Access Number : %m\n");
}