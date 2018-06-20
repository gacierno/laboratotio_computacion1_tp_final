#include "clientes.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int fileExists( char filename[] ){
  int exists = 0;
  FILE * file = fopen("clients.dat", "r");
  if (file != NULL) exists = 1;
  return exists;
}

Cliente createClient(){

  int _dni;
  char _nombre[20];
  char _apellido[20];
  char _telefono[20];
  char _domicilio[30];

  Cliente nuevoCliente = getLastClient();

  nuevoCliente.id++;

  printf("\nDNI: ");
  fflush(stdin);
  scanf("%i",&_dni);
  nuevoCliente.dni = _dni;

  printf("\nNombre: ");
  fflush(stdin);
  fgets(_nombre,20,stdin);
  strcpy(nuevoCliente.nombre,_nombre);

  printf("\nApellido: ");
  fflush(stdin);
  fgets(_apellido,20,stdin);
  strcpy(nuevoCliente.apellido,_apellido);

  printf("\nTelefono: ");
  fflush(stdin);
  fgets(_telefono,20,stdin);
  strcpy(nuevoCliente.telefono,_telefono);

  printf("\nDomicilio: ");
  fflush(stdin);
  fgets(_domicilio,30,stdin);
  strcpy(nuevoCliente.domicilio,_domicilio);

  nuevoCliente.baja = 'n';

  return nuevoCliente;

}

void guardarCliente(Cliente c){
  printf("\nGUARDANDO CLIENTE:\n");
  printClient(c);
  char mode[] = "rb+";
  if(!fileExists("clients.dat")) strcpy(mode,"wb+");

  FILE * file = fopen("clients.dat", mode);
  fseek(file,sizeof(Cliente) * (c.id) , SEEK_SET);
  fwrite(&c, sizeof(Cliente) , 1, file);
  fclose(file);

  printf("\n> CLIENTE CREADO EXITOSAMENTE:");
}

void createClients(){
  char control = 's';
  while(control == 's'){

    printf("=========================================\n");
    printf("NUEVO CLIENTE\n");
    printf("=========================================\n");
    guardarCliente(createClient());
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
  printf("LAST CLIENT:");
  printClient(getLastClient());
  int lastID = getLastClient().id;

  if(lastID > -1 && fileExists("clients.dat")){
    file = fopen("clients.dat", "rb");

    printf("\n=====================================================================\n");
    while(lastID != -1){
      printf("%i LAST ID", lastID );
      fread(&c, sizeof(Cliente), 1, file);
      printClient(c);
      if(c.id >= lastID) lastID = -1;
    }

    fclose(file);
  }else{
    printf("Aun no se han ingresado clientes.");
  }
}

Cliente getLastClient(){
  Cliente c;
  FILE * file;
  int size = 0;

  if(fileExists("clients.dat")){
    file = fopen("clients.dat", "rb");
    size = ftell(file);
    printf("FILE SIZE: %d", size );
    printf("CLIENT SIZE: %d", sizeof(Cliente) );
    fseek(file,size - sizeof(Cliente), SEEK_SET);
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

void darDeBaja(){
  int dni;
  printf("Ingrese el DNI del cliente que quiere dar de baja:");
  fflush(stdin);
  scanf("%i",&dni );
  if(getClientByDNI(dni).id != -1){
    disableClient(dni);
  }
}

void modificarCliente(){
  int dni;
  Cliente c;
  printf("Ingrese el DNI del cliente que quiere modificar:");
  fflush(stdin);
  scanf("%i",&dni );
  c = getClientByDNI(dni);
  if(c.id != -1){
    printf("\nMODIFICAR CLIENTE:\n");
    printClient(c);
    printf("\n== NUEVOS DATOS:\n");
    guardarCliente(createClient());
  }else{
    printf("\nNo exite un cliente con DNI %i",dni);
  }
}
