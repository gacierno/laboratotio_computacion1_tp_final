#include <stdio.h>
#include "headers/menu.h"
#include "../clear-screen/clear-screen.c"

void _showMenu(Menu *m){

  // clearScreen();

  int i;
  int userOption;
  char enterKey;

  printf("\n===============================================");
  printf("\n%s\n", (*m).title);
  printf("===============================================");
  printf("\n\n");

  for(i = 0; i < (*m).optionCount ;i++){
    printf("%i) ", i);
    printf("%s\n", (*m).options[i].text);
  }

  printf("\n\nEnter option number: ");
  fflush(stdin);
  scanf("%i",&userOption);

  if(userOption > (*m).optionCount-1 || (*m).optionCount < 0){
    (*m).show();
  }else{
    (*m).options[userOption].function();
  }

}
