#include <stdio.h>
#include "headers/menu.h"

void _showMenu(Menu *m){


  system("clear");
  system("cls");

  int i;
  int userOption;

  printf("===============================================");
  printf("\n%s\n", (*m).title);
  printf("===============================================");
  printf("\n\n");

  for(i = 0; i < (*m).optionCount ;i++){
    printf("%i) ", i);
    printf("%s\n", (*m).options[i].text);
  }

  printf("\n\n Enter option number: ");
  fflush(stdin);
  scanf("%i",&userOption);

  if(userOption > (*m).optionCount-1 || (*m).optionCount < 0){
    printf("Selected option is invalid.\nPress any ENTER to try again.");
    fflush(stdin);
    scanf("%i",&userOption);
    _showMenu(m);
  }else{
    (*m).options[userOption].function();
  }

}
