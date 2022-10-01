#include<stdio.h>

#include<stdlib.h>

#include<string.h>

int curr = 0;
char str[200];

/*
	S->UVW
	U->(S) | aSb | d
	V->aV | e
	W->cW | e
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
void U();
void V();
void W();

void S(){
	U();
	V();
	W();
}	

void U(){
	if(str[curr]=='('){
		curr++;
		S();
		if(str[curr]==')'){
			curr++;
			valid();
		}
		else invalid();

	}
	else if(str[curr]=='a'){
		curr++;
		S();
		if(str[curr]=='b'){
			curr++;
			valid();
		}
		else invalid();
	}
	else if(str[curr]=='d'){
		curr++;
		valid();
	}
	else invalid();
}

void V(){
	if(str[curr]=='a'){
		curr++;
		V();
	}
	else return ;
}
void W(){
	if(str[curr]=='c'){
		curr++;
		W();
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
