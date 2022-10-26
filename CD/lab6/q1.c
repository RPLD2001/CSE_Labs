#include<stdio.h>

#include<stdlib.h>

#include<string.h>

int curr = 0;
char str[200];

/* S-> a | > | (T)
   T-> ST'
   T'->,ST'|e
*/

void S();
void T();
void Tprime();

void invalid() {
  printf("ERROR!");
  exit(0);
}
void valid() {
  printf("SUCCESS!");
  exit(0);
}

void S() {
  if (str[curr] == 'a') {
    curr++;
    return;
  } else if (str[curr] == '>') {
    curr++;
    return;
  } else if (str[curr] == '(') {
    curr++;
    T();
    if (str[curr] == ')') {
      curr++;
      valid();
    } else invalid();
  } 
  else invalid();

}

void T() {
  S();
  Tprime();
}

void Tprime() {
  if (str[curr] == ',') {
    curr++;
    S();
    Tprime();
  } else return;
}

int main() {
  printf("Enter String: ");
  scanf("%s", str);
  S();
  if (str[curr] == '$')
    valid();
  else
    // printf("%c\n", str[curr]);
    invalid();
}