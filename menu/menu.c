#include <stdio.h>
#include "headers/menu.h"

void _showMenu(Menu *m){

  system("cls");

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

  printf("\n\nIngrese la opcion deseada: ");
  fflush(stdin);
  scanf("%i",&userOption);

  if(userOption > (*m).optionCount-1 || (*m).optionCount < 0){
    (*m).show();
  }else{
    (*m).options[userOption].function();
  }

}
