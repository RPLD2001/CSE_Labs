#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void *add_odd(void* args){
	int *arr=(int*)args;
	int n=arr[0];
	int *res=(int*)malloc(sizeof(int));
	*res=0;
	for(int i=1;i<=n;i++){
		if(arr[i]%2!=0)
			*res+=arr[i];
	}
	return (void*)res;
}
void *add_even(void* args){
	int *arr=(int*)args;
	int n=arr[0];
	int *res=(int*)malloc(sizeof(int));
	*res=0;
	for(int i=1;i<=n;i++){
		if(arr[i]%2==0)
			*res+=arr[i];
	}
	return (void*)res;
}

int main(){
	int n;
	printf("Enter number of integers: ");
	scanf("%d",&n);
	int* arr=(int*)calloc(n+1,sizeof(int)),*resEven,*resOdd;
	arr[0]=n;
	printf("Enter the elements:");
	for(int i=0;i<n;i++){
		scanf("%d",&arr[i+1]);
	}
	pthread_t threadOdd, threadEven;
	pthread_create(&threadOdd, 0, &add_odd, (void*)arr);
	pthread_create(&threadEven, 0, &add_even, (void*)arr);
	pthread_join(threadOdd, (void**)&resOdd);
	pthread_join(threadEven, (void**)&resEven);
	printf("The Sum of Odd numbers is: %d\n", *resOdd);
	printf("The Sum of Even numbers is: %d\n", *resEven);
	return 0;
}