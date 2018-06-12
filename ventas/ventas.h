#ifndef VENTAS_H_INCLUDED
#define VENTAS_H_INCLUDED

typedef struct{
    int id;
    int idCliente;
    int idProducto;
    int cantidad;
    int dia;
    int mes;
    int anio;
    char pagado;
    char anular; //‘a’
}Venta;

Venta crear_nueva_venta( void );


#endif // VENTAS_H_INCLUDED
