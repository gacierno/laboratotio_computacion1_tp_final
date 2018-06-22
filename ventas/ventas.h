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
    char anular; //�a� o 'n'
}Venta;

int fecha_valida( int, int, int );

Venta alta_de_ventas( void );
int cantidad_de_registros(char[]);
void guardar_venta_archivo( char[], Venta );
Venta buscar_venta_por_id( char[], int );

int get_idCliente(void);
int get_idProducto(void);

int canidad_producto_verificada( int );
void ingresar_fecha_validada( int*, int*, int* );
void ingresar_pago( Venta* );
void anular_venta( void );

void mostrar_una_venta( Venta );
void listar_ventas( char[] );
void listar_ventas_por_cliente( char[], int );
void listar_ventas_por_mes( char[], int, int );

int calcular_total_diario( char[], int, int, int );
int calcular_promedio_mensual( void );

void mostrar_opciones_ventas( void );
void ejecutar_venta( int );

int bucle_main_ventas( void );

#endif // VENTAS_H_INCLUDED
