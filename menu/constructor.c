#include "menu/menu.c"

const Menu MAIN_MENU;
const Menu CLIENTS_MENU;

Menu constructClientsMenu(){
  CLIENTS_MENU.title = "Clients";

  MenuOption mostrar;
  mostrar.text = "Lista de clientes";

  MenuOption crear;
  crear.text = "Crear cliente";

  MenuOption baja;
  baja.text = "Bajas";

  CLIENTS_MENU.options = [
    mostrar,
    crear,
    baja
  ];
}

Menu constructNavigation(){

  // DEFINE MAIN MENU
  MAIN_MENU.title         = "Main Menu";

  // DEFINE CLIENT MENU
  constructClientsMenu()
  MenuOption client;
  clientOption.text       = CLIENTS_MENU.title;
  clientOption.function   = CLIENTS_MENU.show;

  // ASSIGN MENU OPTIONS
  MAIN_MENU.options = [
    client
  ];

  return MAIN_MENU;
}
