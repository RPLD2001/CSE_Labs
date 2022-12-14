#include<stdio.h>

#include<stdlib.h>

#include<string.h>

int curr = 0;
char str[200];

/* 
	S->aAcBe
	A->bA'
	A'->bA' | e
	B->d
*/

void S();
void A();
void Aprime();
void B();

void invalid() {
  printf("ERROR!\n");
  exit(0);
}
void valid() {
  printf("SUCCESS!\n");
  exit(0);
}


void S(){
	if(str[curr]=='a'){
		curr++;
		A();
		if(str[curr]=='c'){
			curr++;
			B();
			if(str[curr]=='e'){
				curr++;
				valid();
			}
		}
	}
	else invalid();
}	

void A(){
	if(str[curr]=='b'){
		curr++;
		Aprime();
	}
}

void Aprime(){
	if(str[curr]=='b'){
		curr++;
		Aprime();
	}
	else return ;
}

void B(){
	if(str[curr]=='d'){
		curr++;
		valid();
	}
	else invalid();
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