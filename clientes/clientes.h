#ifndef VENTAS_H_INCLUDED
#define VENTAS_H_INCLUDED

typedef struct{
    int id;
    int dni;
    char nombre[20];
    char apellido[20];
    char telefono[20];
    char domicilio[30];
    char baja;
}Cliente;

Cliente getCliente( int );
Cliente getClientes( void );
void createCliente(Cliente *);
void deleteCliente(Cliente);
void replaceCliente(Cliente);


#endif // VENTAS_H_INCLUDED
