#include<stdio.h>
int add(int a,int b){
  int sum;
  sum=a+b;
  return sum;
}
int main(){
  int a[30],b,c,s;
  b=2;
  c=18;
  a[0]=-18;
  if(a[0]<=0)
    s=add(a,b);
  else add(b,a);
  printf("sum is %d",s);
}