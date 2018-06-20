#include <stdlib.h>
#include <stdio.h>
#include "ventas.h"

/*

*   Ventas
*       *Alta de Ventas
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

    nueva_venta.id = 1 + cantidad_de_registros( REGISTRO_VENTAS );
    nueva_venta.idCliente = get_idCliente();
    nueva_venta.idProducto = get_idProducto();
    nueva_venta.cantidad = canidad_producto_verificada( nueva_venta.idProducto );
    ingresar_fecha_validada( &nueva_venta.dia, &nueva_venta.mes, &nueva_venta.anio );
    ingresar_pago( &nueva_venta );
    nueva_venta.anular = 'n';
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

void guardar_venta_archivo( char nombre_archivo[], Venta venta_lista )
{
    FILE *archivo_temp;
    archivo_temp = fopen( nombre_archivo, "a+b" );
    if( archivo_temp != NULL)
    {
        if (venta_lista.id > cantidad_de_registros( nombre_archivo ))
        {
            printf("la venta NO NO NO existe \n");
            fseek(archivo_temp, 0, SEEK_END);
        }else{
            printf("la venta existe \n");
            printf("tamanyo%d\n", (venta_lista.id-1)*sizeof(Venta));
            system("pause");
            fseek( archivo_temp, ((venta_lista.id-1)*sizeof(Venta)), SEEK_SET);
            printf("posicion  %d\n", ftell(archivo_temp));
        }
        fwrite(&venta_lista, sizeof(Venta), 1, archivo_temp);
        fclose(archivo_temp);
    }
}

Venta buscar_venta_por_id( char nombre_archivo[], int id_venta )
{
    Venta venta_encontrada;
    int flag = 0;
    FILE *archivo_temp;
    archivo_temp = fopen( nombre_archivo, "rb" );
    if( archivo_temp != NULL )
    {
        while( !feof(archivo_temp) && flag == 0 )
        {
            if( fread(&venta_encontrada, sizeof(Venta), 1, archivo_temp)!=0 )
            {
                if( venta_encontrada.id == id_venta )
                {
                    flag = 1;
                }
            }
        }
        fclose(archivo_temp);
    }
    if( flag == 0 )
    {
        venta_encontrada.id = -1;
    }
    return venta_encontrada;
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

void ingresar_pago( Venta *venta_actual )
{
    printf( "Esta venta ha sido pagada? \n" );
    fflush(stdin);
    scanf( "%c", &venta_actual->pagado );
}

void anular_venta( )
{
    Venta current;
    int id_venta;

    do
    {
        printf("Ingrese el id dela venta que desea anualr\n");
        fflush(stdin);
        scanf("%d", &id_venta);
        current = buscar_venta_por_id( REGISTRO_VENTAS, id_venta );
        if(current.id < 1)
        {
            printf("No se ha encontrado la venta especificada por favor intente nuevamente.\n");
            printf("Presione ENTER para continuar\n");
            getchar();
        }
    }while( current.id < 1 );

    mostrar_una_venta( current );
    printf( "Desea anular esta venta? \n" );
    fflush(stdin);
    scanf( "%c", &current.anular );
    guardar_venta_archivo( REGISTRO_VENTAS, current );
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

void listar_ventas( char nombre_archivo[] )
{
    Venta venta_actual;
    FILE *archivo_temp;
    archivo_temp = fopen( nombre_archivo, "rb" );
    if( archivo_temp != NULL )
    {
        while( !feof(archivo_temp) )
        {
            printf("====================================\n");
            if( fread(&venta_actual, sizeof(Venta), 1, archivo_temp) != 0)
                mostrar_una_venta(venta_actual);
        }
        fclose(archivo_temp);
    }
}

void mostrar_opciones_ventas()
{
    printf("\n");
    printf("1- Nueva Venta \n");
    printf("2- Anular Venta \n");
    printf("3- Listar Venta por Cliente \n");
    printf("4- Listar Ventas del Mes \n");
    printf("5- Promedio de ventas del mes \n");
    printf("0- Volver al menu anterior \n");
    printf("Por favor elija su opcion: \n");
}

void ejecutar_venta( int op )
{
    Venta venta_actual;
    int id_venta;

    switch( op )
    {
    case 1:
        venta_actual = alta_de_ventas();
        guardar_venta_archivo( REGISTRO_VENTAS, venta_actual);
        break;
    case 2:
        anular_venta();
        break;
    case 99:
        listar_ventas( REGISTRO_VENTAS );
        break;
    }
}

int bucle_main_ventas()
{
    int opcion = 0;

    do
    {
        mostrar_opciones_ventas();
        fflush(stdin);
        scanf("%d", &opcion);
        ejecutar_venta(opcion);
    }while(opcion != 0);

    return opcion;
}
