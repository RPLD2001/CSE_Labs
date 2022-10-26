#include<stdio.h>

#include<stdlib.h>

#include<string.h>

int curr = 0;
char str[200];

/*
	S->(L) | a
	L->SL'
	L'->,SL' | e
*/

void invalid() {
  printf("ERROR!\n");
  exit(0);
}
void valid() {
  printf("SUCCESS!\n");
  exit(0);
}

void S();
void L();
void Lprime();

void S(){
	if(str[curr]=='('){
		curr++;
		L();
		if(str[curr]==')'){
			curr++;
			valid();
		}
	}
	else if(str[curr]=='a'){
		curr++;
		valid();
	}
	else invalid();
}

void L(){
	S();
	Lprime();
}

void Lprime(){
	if(str[curr]==','){
		S();
		Lprime();
	}
	else return ;
}

int main() {
  printf("Enter String: ");
  scanf("%s", str);
  S();
  if (str[curr] == '$')
    valid();
  else
    printf("%c\n", str[curr]);
    invalid();
}

