#include <stdio.h>
#include <conio.h>
main(){
	int ar[100],i,n,j,counter;
	for(i=0;i<=n;i=i+1){
		n=n/2;
	}
	for(i=0;i<n;i=i+1){
		counter=0;
		for(j=2;j<i;j=j+1){
			if(i%j==0){
				counter=1;
			}
		}
		if(counter==0){
			while(n!=0){
				n=n%10;
			}
		}
		else{n=n*2;} 
	}
}