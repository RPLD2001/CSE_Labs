#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void *thread_code(void* args){
	int *arr=(int*)args;
	int lower_limit=arr[0];
	int upper_limit=arr[1];
	int *result=(int*)calloc(upper_limit+1,sizeof(int));
	while(lower_limit<upper_limit){
		int flag=0;
		if(lower_limit<=1){
			++lower_limit;
			continue;
		}
		for(int i=2;i<=lower_limit/2;++i){
			if(lower_limit%i==0){
				flag=1;
				break;
			}
		}
		if(flag==0)result[lower_limit]=1;
		++lower_limit;
	}
	return (void*)result;
}

int main(){
	int lower_limit,upper_limit;
	printf("Enter lower_limit:");
	scanf("%d",&lower_limit);
	printf("Enter upper_limit:");
	scanf("%d",&upper_limit);
	int packet[]={lower_limit,upper_limit},*result;
	pthread_t thread;
	pthread_create(&thread,0,&thread_code,(void*)packet);
	pthread_join(thread,(void**)&result);
	printf("The prime Numbers are:");
	for(int i=lower_limit;i<=upper_limit;i++){
		if(result[i])printf("%d    ",i);
	}
	printf("\n");
	return 0;
}