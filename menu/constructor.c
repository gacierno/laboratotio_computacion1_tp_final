#include <string.h>
#include "./menu.c"
#include "../clientes/clientes.c"

Menu MAIN_MENU;
Menu CLIENTS_MENU;


/*
  ================================
   CLIENTS MENU
  ================================
*/

void showClientsMenu(){
  _showMenu(&CLIENTS_MENU);
}

Menu constructClientsMenu(){

  strcpy(CLIENTS_MENU.title,"Clients");
  CLIENTS_MENU.show = showClientsMenu;
  CLIENTS_MENU.optionCount = 4;

  MenuOption mostrar;
  mostrar.function = showAllClients;
  strcpy(mostrar.text,"Lista de clientes");
  CLIENTS_MENU.options[0] = mostrar;

  MenuOption crear;
  crear.function = createClients;
  strcpy(crear.text,"Crear clientes");
  CLIENTS_MENU.options[1] = crear;


  MenuOption modificar;
  modificar.function = modificarCliente;
  strcpy(modificar.text,"Modificar cliente");
  CLIENTS_MENU.options[2] = modificar;


  MenuOption baja;
  baja.function = darDeBaja;
  strcpy(baja.text,"Bajas");
  CLIENTS_MENU.options[3] = baja;

}

/*
  ================================
   MAIN MENU
  ================================
*/

void showMainMenu(){
  _showMenu(&MAIN_MENU);
}

Menu constructMainMenu(){

  strcpy(MAIN_MENU.title,"MAIN MENU");
  MAIN_MENU.show = showMainMenu;
  MAIN_MENU.optionCount = 1;

  MenuOption client;
  strcpy(client.text,CLIENTS_MENU.title);
  client.function = CLIENTS_MENU.show;

  MAIN_MENU.options[0] = client;
}


/*
  ================================
   BUNDLE CONSTRUCTOR
  ================================
*/

Menu constructNavigation(){

  constructClientsMenu();
  constructMainMenu();

  return MAIN_MENU;
}
