// #include "micro.h"
#include <stdio.h>

#define BLINK "\033[5m"
#define CHANGE "\033[7m"
#define RESET "\033[0m"
#define HIGHLIGHT "\033[1m"
// #define CLEAR "\033[2J"


void  print()
{
  printf(CHANGE HIGHLIGHT" █\n");
  printf("◥██◢██◣\n");
  printf(" █◤   ◥◣\n");
  printf(" ◢█    █\n");
  printf("◢◤█    ◢◤\n");
  printf("  █ ◥█◤\n");
  printf(" ◣\n");
  printf(" █ ◥◣\n");
  printf("◥████◣ ◥◣\n");
  printf("  █  █\n");
  printf(" ◢◤  █\n");
  printf("◢◤ ◥██\n");
  printf("◥███◣\n");
  printf("  ◢◤\n");
  printf(" ◢██◣\n");
  printf("    ◥◣\n");
  printf("◢██◣ █\n");
  printf("◥◣ █◢◤\n");
  printf(" ◥██◤\n");
  printf("\n" RESET);
}

int main() {
  print();
}