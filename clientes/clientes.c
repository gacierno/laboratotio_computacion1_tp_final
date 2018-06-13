#include "clientes.h"
#include <stdlib.h>
#include <stdio.h>


void createCliente(Cliente *c){
  FILE * file = fopen("clients.dat", "wb");
  if (file != NULL) {
    fwrite(c, sizeof(Cliente), 1, file);
    fclose(file);
  };
}

Cliente getClient(int target){
  FILE * file = fopen("clients.dat", "rb");
  Cliente c;
  int found = 0;
  if(file != NULL && found != 1){
    while(!feof(file)){
      fread(&c, sizeof(Cliente), 1, file);
      if(c.id == target){
        found = 1;
      }
    }
  }
  fclose(file);
  return c;
}
