#include "clientes.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../clear-screen/clear-screen.c"

void createClient(){

  int _dni;
  char _nombre[20];
  char _apellido[20];
  char _telefono[20];
  char _domicilio[30];

  clearScreen();

  Cliente nuevoCliente = getLastClient();

  printf("=========================================\n");
  printf("NUEVO CLIENTE\n");
  printf("=========================================\n");

  if(nuevoCliente.id == -1){
    nuevoCliente.id = 0;
  }else{
    nuevoCliente.id++;
  };

  printf("\nDNI: ");
  fflush(stdin);
  scanf("%i",&_dni);
  nuevoCliente.dni = _dni;

  printf("\nNombre: ");
  fflush(stdin);
  scanf("%s",_nombre);
  strcpy(nuevoCliente.nombre,_nombre);

  printf("\nApellido: ");
  fflush(stdin);
  scanf("%s",_apellido);
  strcpy(nuevoCliente.apellido,_apellido);

  printf("\nTelefono: ");
  fflush(stdin);
  scanf("%s",_telefono);
  strcpy(nuevoCliente.telefono,_telefono);

  printf("\nDomicilio: ");
  fflush(stdin);
  scanf("%s",_domicilio);
  strcpy(nuevoCliente.domicilio,_domicilio);

  nuevoCliente.baja = 'n';

  FILE * file = fopen("clients.dat", "ab+");
  if (file != NULL) fwrite(&nuevoCliente, sizeof(Cliente), 1, file);
  fclose(file);

  printf("\n> CLIENTE CREADO EXITOSAMENTE:");
}

void createClients(){
  char control = 's';
  while(control == 's'){
    createClient();
    printf("\n\n\n--------------------------------\n");
    printf("Quiere agregar otro cliente?(s/n)\n");
    fflush(stdin);
    scanf("%s",&control);
  }
}

void printClient(Cliente c){
  printf("Id: %i\n", c.id );
  printf("DNI: %i\n", c.dni );
  printf("Nombre: %s\n", c.nombre );
  printf("Apellido: %s\n", c.apellido );
  printf("Telefono: %s\n", c.telefono );
  printf("Domicilio: %s\n", c.domicilio );
  printf("Baja: %s\n", &c.baja );

  printf("\n=====================================================================\n");
}

void showAllClients(){
  Cliente c;
  FILE * file;
  int lastID = getLastClient().id;

  if(lastID > -1){
    file = fopen("clients.dat", "rb+");
    if(file != NULL ){
      printf("\n=====================================================================\n");
      while(lastID != -1){
        fread(&c, sizeof(Cliente), 1, file);
        printClient(c);
        if(lastID == c.id) lastID = -1;
      }

    }
    fclose(file);
  }else{
    printf("Aun no se han ingresado clientes.");
  }
}

Cliente getLastClient(){
  FILE * file = fopen("clients.dat", "rb+");
  Cliente c;
  long size = 0;

  if(file != NULL ){
    fseek(file,sizeof(Cliente) * -1, SEEK_END);
    fread(&c, sizeof(Cliente) , 1, file);
  }else{
    c.id = -1;
  }
  fclose(file);
  return c;
}

Cliente getClientByDNI( int dni ){
  Cliente c;
  int found = -1;
  FILE * file;
  int lastID = getLastClient().id;
  if(lastID > -1){
    file = fopen("clients.dat", "rb");
    if(file != NULL ){

      while(c.id <= lastID && found == -1){
        fread(&c, sizeof(Cliente), 1, file);
        if(c.dni == dni){
          found = c.id;
        }
      }

    }
    fclose(file);
  }else{
    printf("Aun no se han ingresado clientes.");
  }
  c.id = found;
  return c;
}

void updateClient(Cliente *c,int dni){
  Cliente record = getClientByDNI(dni);
  (*c).id = record.id;
  FILE * file = fopen("clients.dat", "rb+");
  if (file != NULL){
    fseek(file, sizeof(Cliente) * (record.id), SEEK_SET );
    fwrite(c, sizeof(Cliente) , 1, file);
  } else {
    printf("Hubo un error al intentar guardar el archivo");
  }
  fclose(file);
}

Cliente disableClient(int dni){
  Cliente record = getClientByDNI(dni);
  record.baja = 's';
  updateClient(&record,dni);
  return record;
}

Cliente enableClient(int dni){
  Cliente record = getClientByDNI(dni);
  record.baja = 'n';
  updateClient(&record,dni);
  return record;
}
