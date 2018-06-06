#include "menu-option.h"

typedef struct{
  char title[100];
  MenuOption options[10];
  void (*show)();
  int optionCount;
} Menu;
