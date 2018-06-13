// #include "./menu/constructor.c"
//
// int main(){
//   constructNavigation();
//   MAIN_MENU.show(&MAIN_MENU);
//   return 0;
// }
#include <stdlib.h>
#include <stdio.h>
#include "./clientes/clientes.c"

int main(){
  Cliente testClient;
  testClient.id = 0;
  testClient.dni = 1234;
  strcpy(testClient.nombre,"Peperino");
  strcpy(testClient.apellido,"Poporo");
  strcpy(testClient.telefono,"12345");
  strcpy(testClient.domicilio,"Calle falsa 123");
  testClient.baja = 'n';

  createCliente(&testClient);
  Cliente target = getClient(0);
  printf("Cliente: %s\n", target.nombre );
  return 0;
}
