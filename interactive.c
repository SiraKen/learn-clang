#include <stdio.h>

int main() {

  char name[4];
  int age;

  printf("What is your name?\n");
  scanf("%s", name);

  printf("How old are you?\n");
  scanf("%d", &age);

  printf("Hello %s, you are %d years old.\n", name, age);

  return 0;
}
