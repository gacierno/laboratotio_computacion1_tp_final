#include <stdlib.h>
#include <stdio.h>
#include "ventas.h"

/*

*   Ventas
*       Alta de Ventas
*           Buscar cliente
*           Buscar Producto
*           Dar de Alta la venta
*           Guardar en archivo la venta
*       Anulación de Venta
*       Listar ventas por cliente
*       Listar Ventas del mes
*       Mostrar promedio de ventas del mes (utilizar matrices)
*           La Matriz tiene que ser de 7*4 para obtener el promedio de ventas diario de los ultimos 28 dias
*       Validaciones:
*           No mostrar en listado de venta los productos con stock 0.
*           Validar en la venta que la cantidad no sobrepase el stock.
*           Al realizarse la venta restar la cantidad del stock del producto.
*           En la venta validar la fecha. Año válido. Mes válido y día válido de acuerdo al mes y al año. (Ojo en febrero, validar año bisiesto).

*/


Venta alta_de_ventas()
{
    Venta nueva_venta;

    // obtener id autoincrementado
    nueva_venta.id = 1 + cantidad_de_registros( REGISTRO_VENTAS );
    // buscar id cliente (por nombre??)
    nueva_venta.idCliente = get_idCliente();
    // buscar id producto
    nueva_venta.idProducto = get_idProducto();
    // cantidad
    nueva_venta.cantidad = canidad_producto_verificada( nueva_venta.idProducto );
    // fecha
    ingresar_fecha_validada( &nueva_venta.dia, &nueva_venta.mes, &nueva_venta.anio );
    // pagado
    // anulado
    return nueva_venta;
}

int cantidad_de_registros( char nombre_archivo[] )
{
    FILE *archivo_temp;
    int registros_encontrados = 0;

    archivo_temp = fopen( nombre_archivo, "rb" );

    if( archivo_temp != NULL )
    {
        fseek( archivo_temp, 0, SEEK_END);
        registros_encontrados = ftell( archivo_temp ) / sizeof(Venta); //se supone que dara un entero
    }

    fclose( archivo_temp );
    return registros_encontrados;
}

int get_idCliente()
{
    return 0;
}

int get_idProducto()
{
    return 0;
}

int canidad_producto_verificada( int id_producto )
{
    int cantidad = 0;
    int verificada = 0; //aun no esta verificada

    printf( "Ingrese la cantidad del producto vendido: \n" );
    scanf( "%d", &cantidad );

    //si la cantidad es valida
    return cantidad;
}

void ingresar_fecha_validada( int *dia, int *mes, int *anio )
{
    int invalida = 1; // aun no esta validada

    do
    {
        printf( "Ingrese el dia: \n" );
        fflush( stdin );
        scanf( "%d", dia );
        printf( "Ingrese el mes: \n" );
        fflush( stdin );
        scanf( "%d", mes);
        printf( "Ingrese el anio \n" );
        fflush( stdin );
        scanf( "%d", anio);

        //si se valida
        invalida = 0;
    }while( invalida );
}

void mostrar_una_venta( Venta actual )
{
    printf( "La venta cargada tiene el siguiente detalle: \n" );
    printf( "Numero:........%d\n", actual.id );
    printf( "Cliente:.......%d\n", actual.idCliente );
    printf( "%d de:.........%d\n", actual.cantidad, actual.idProducto );
    printf( "Fecha..:.......%.2d / %.2d / %.4d\n", actual.dia, actual.mes, actual.anio );
    printf( "Pagado:........%c\n", actual.pagado );
    printf( "Anulado:.......%c\n", actual.anular );
}
