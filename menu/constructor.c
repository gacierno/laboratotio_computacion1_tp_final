#include "menu/menu.c"

const Menu MAIN_MENU;
const Menu CLIENTS_MENU;

void MenuConstructor(*m,title,options){
  m.title = title;
  m.show = _showMenu;
  m.options = options;
}

Menu constructClientsMenu(){

  MenuOption mostrar;
  mostrar.text        = "Lista de clientes";

  MenuOption crear;
  crear.text          = "Crear cliente";

  MenuOption baja;
  baja.text           = "Bajas";

  MenuConstructor(
    &CLIENTS_MENU,
    "Clients",
    [
      mostrar,
      crear,
      baja
    ]
  );

}

Menu constructNavigation(){

  // DEFINE CLIENT MENU
  constructClientsMenu();
  MenuOption client;
  clientOption.text       = CLIENTS_MENU.title;
  clientOption.function   = CLIENTS_MENU.show;

  // DEFINE MAIN MENU
  MenuConstructor(
    &MAIN_MENU,
    "Main Menu",
    [
      client
    ]
  );

  return MAIN_MENU;
}
