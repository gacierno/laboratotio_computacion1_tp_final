#ifndef VENTAS_H_INCLUDED
#define VENTAS_H_INCLUDED

#define REGISTRO_VENTAS "ventas.bin"

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

Venta alta_de_ventas( void );
int cantidad_de_registros(char[]);

int get_idCliente(void);
int get_idProducto(void);

int canidad_producto_verificada( int );
void ingresar_fecha_validada( int*, int*, int* );

void mostrar_una_venta( Venta );

#endif // VENTAS_H_INCLUDED
