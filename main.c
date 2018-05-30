#include "menu/menu.c"

// DEFINE MAIN MENU
Menu createMainMenu( Menu *m ){
  m.title = "Main Menu";

  MenuOption clientOption;
  MenuOption productsOption;

  clientOption.text       = "Clients";
  productsOption.text     = "Products";
  clientOption.function   = setMenu("clients");
  productsOption.function = setMenu("products");

  m.options = [
    clientOption,
    productsOption
  ];
}

int main(){

  Menu mainMenu;
  mainMenu = createMainMenu(&mainMenu);

  return 0;
}
