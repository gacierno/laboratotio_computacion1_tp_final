#include "./menu/constructor.c"

int main(){
  constructNavigation();
  MAIN_MENU.show(&MAIN_MENU);
  return 0;
}

// #include <stdlib.h>
// #include <stdio.h>
// #include "./clientes/clientes.c"
//
// int main(){
  // createClients();
  //
  // Cliente last = getLastClient();
  // Cliente test = getClientByDNI(37030992);
  //
  // updateClient(&test,last.dni);
  // showAllClients();

  // printClient(disableClient(37030992));

//   return 0;
// }
