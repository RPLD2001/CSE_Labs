#include<stdio.h>
<<<<<<< HEAD
int add(int a, int b)
{
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
=======
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
>>>>>>> a0870d672dc298e39bb10d70a7bab5df91d7435e
}