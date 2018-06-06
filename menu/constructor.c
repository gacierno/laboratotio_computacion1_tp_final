#include <string.h>
#include "./menu.c"

Menu MAIN_MENU;
Menu CLIENTS_MENU;

void MenuConstructor(Menu *m,char title[], int optionCount){
  strcpy(m->title,title);
  m->show = _showMenu;
  m->optionCount = optionCount;
}

Menu constructClientsMenu(){

  MenuConstructor(
    &CLIENTS_MENU, // MENU
    "Clients", // TITLE
    3 // OPTION COUNT
  );


  MenuOption mostrar;
  strcpy(mostrar.text,"Lista de clientes");
  CLIENTS_MENU.options[0] = mostrar;

  MenuOption crear;
  strcpy(crear.text,"Crear cliente");
  CLIENTS_MENU.options[1] = crear;

  MenuOption baja;
  strcpy(baja.text,"Bajas");
  CLIENTS_MENU.options[2] = baja;

}

Menu constructNavigation(){

  // DEFINE CLIENT MENU
  constructClientsMenu();
  MenuOption client;
  strcpy(client.text,CLIENTS_MENU.title);
  client.function   = CLIENTS_MENU.show;

  // DEFINE MAIN MENU
  MenuConstructor(
    &MAIN_MENU,
    "Main Menu",
    1
  );

  MAIN_MENU.options[0] = client;

  return MAIN_MENU;
}
