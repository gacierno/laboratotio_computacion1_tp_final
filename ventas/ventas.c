#include <stdlib.h>
#include <stdio.h>
#include "ventas.h"
#include "../productos.c"
#include "../clientes/clientes.h"

Menu VENTAS_MENU;

/*
FUNCIONES PARA MANEJAR FECHAS
*/
int fecha_valida( int dia, int mes, int anyo )
{
    int total_dias_mes; //28, 29, 30 o 31
    int anyo_biciesto = 0; // 0 no es biciesto
    int valido = 0; // todavia no es valido

    if( mes > 0 && mes < 13 )
    {
        if( anyo%400 == 0 || ( anyo%100 !=0 && anyo%4 == 0 ) )
        {
            anyo_biciesto = 1;
        }
        if( mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12 )
        {
            total_dias_mes = 31;
        }
        else if( mes != 2 )
        {
            total_dias_mes = 30;
        }
        else if( anyo_biciesto )
        {
            total_dias_mes = 28;
        }
        else
        {
            total_dias_mes = 29;
        }
        if( dia > 0 && dia < (total_dias_mes + 1) )
        {
            valido = 1; //validado
        }
    }
    return valido;
}

void ingresar_fecha_validada( int *dia, int *mes, int *anio )
{
    int valida = 0; // aun no esta validada
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
        valida = fecha_valida( *dia, *mes, *anio );
        if( !valida )
        {
            printf("\nIngrese una fecha valida \n");
        }
    }while( !valida );
}

/*
FUNCIONES PARA ALTA DE VENTAS
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
    FILE *archivo;
    archivo = fopen( nombre_archivo, "rb" );
    if( archivo != NULL)
    {
        fclose( archivo );
        if (venta_lista.id > cantidad_de_registros( nombre_archivo ))
        {
            archivo = fopen( nombre_archivo, "ab");
        }else{
            archivo = fopen( nombre_archivo, "rb+");
            fseek( archivo, ((venta_lista.id-1)*sizeof(Venta)), SEEK_SET);
        }
    }else{
        archivo = fopen( nombre_archivo, "wb" );
    }
    fwrite(&venta_lista, sizeof(Venta), 1, archivo);
    fclose(archivo);
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

void ingresar_pago( Venta *venta_actual )
{
    printf( "Esta venta ha sido pagada? \n" );
    fflush(stdin);
    scanf( "%c", &venta_actual->pagado );
}

/*
FUNCIONES PARA MANEJAR EL CLIENTE DE LA VENTA
*/
int get_idCliente()
{
    int id = 0;
    int dni = 0;
    do
    {
        printf( "Por favor ingrese el numero de documento del cliente \n");
        fflush( stdin );
        scanf( "%d", &dni );
        id = buscar_cliente_por_dni( dni ); //funcion de ../clientes/clientes.h
        if( id == -1 )
        {
            printf("El cliente seleccionado no existe por favor intente nuevamente \n");
        }
    }while( id == -1);
    printf("El id encontrado es %d\n", id);
    return id;
}

int buscar_cliente_por_dni( int dni_cli )
{
    int id = -1;
    int flag = 0;
    Cliente current_cli;
    FILE * archivo_clientes;
    archivo_clientes = fopen("clients.dat", "rb");
    if( archivo_clientes != NULL)
    {
        while( fread(&current_cli, sizeof(Cliente), 1, archivo_clientes)!=0 && flag == 0)
        {
            if( current_cli.dni == dni_cli )
            {
                flag = 1;
                id = current_cli.id;
            }
        }
    }
    return id;
}

/*
FUNCIONES PARA MANEJAR EL PRODUCTO DE LA VENTA
*/
int get_idProducto()
{
    int op = 0;
    int id_prod;
    Producto current_prod;
    int id_busca;
    char nombre[20];
    char control = 's';
    do
    {
        printf("\nPara buscar el producto elija el criterio de busqueda\n");
        printf("1> Buscar por nombre\n");
        printf("2> Buscar por id\n");
        fflush(stdin);
        scanf("%d", &op);
    }while( op!=1 && op!=2 );
    switch( op )
    {
    case 1:
        do
        {
            printf("Ingrese el nombre \n");
            fflush(stdin);
            fgets( nombre, 20, stdin);
            id_prod = buscar_producto_por_nombre( nombre );
            if(id_prod != 0){
                current_prod = get_producto_por_id( id_prod );
                mostrarProducto( current_prod );
            }
            printf("Desea hacer otra busqueda?\n");
            fflush(stdin);
            scanf("%c", &control);
        }while(control != 'n');
        break;
    case 2:
        do
        {
            printf("Ingrese el id \n");
            fflush(stdin);
            scanf("%d", &id_busca);
            id_prod = buscar_producto_por_id( id_busca );
            if(id_prod != 0){
                current_prod = get_producto_por_id( id_prod );
                mostrarProducto( current_prod );
            }
            printf("Desea hacer otra busqueda?\n");
            fflush(stdin);
            scanf("%c", &control);
        }while(control != 'n');
        break;
    }

    return id_prod;
}

int canidad_producto_verificada( int id_producto )
{
    int cantidad = 0;
    Producto current_prod;
    FILE *archivo_prods;

    archivo_prods = fopen("producto.bin", "rb+");

    fseek( archivo_prods, (long)(id_producto-1)*sizeof(Producto), SEEK_SET );
    fread(&current_prod, sizeof(Producto), 1, archivo_prods);

    do
    {
        printf( "Ingrese la cantidad del producto vendido: \n" );
        fflush(stdin);
        scanf( "%d", &cantidad );
        if( cantidad > current_prod.stock )
        {
            printf(" ingrese una cantidad valida \n");
        }
    }while( cantidad > current_prod.stock );

    current_prod.stock = current_prod.stock - cantidad;
    fseek( archivo_prods, (long)(id_producto-1)*sizeof(Producto), SEEK_SET );
    fwrite( &current_prod, sizeof(Producto), 1, archivo_prods);
    fclose(archivo_prods);
    return cantidad;
}

/*
FUNCIONES PARA ANULAR LA VENTA
*/
void anular_venta( )
{
    Venta current;
    int id_venta;
    char anulacion;
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
    scanf( "%c", &anulacion );
    if( anulacion == 's' || anulacion == 'S')
    {
        current.anular = 'a';
    }
    else
    {
        current.anular = 'n';
    }
    guardar_venta_archivo( REGISTRO_VENTAS, current );
}

/*
FUNCIONES PARA VISUALIZAR LAS VENTAS
*/
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
        while( fread(&venta_actual, sizeof(Venta), 1, archivo_temp) != 0 )
        {
            printf("====================================\n");
            mostrar_una_venta(venta_actual);
        }
        fclose(archivo_temp);
    }
}

void listar_ventas_por_cliente( char nombre_archivo[], int id_cliente )
{
    Venta venta_actual;
    int contador = 0;
    FILE *archivo_temp;
    archivo_temp = fopen( nombre_archivo, "rb" );
    if( archivo_temp != NULL )
    {
        while(  fread(&venta_actual, sizeof(Venta), 1, archivo_temp) != 0 )
        {
            if( venta_actual.idCliente == id_cliente )
            {
                contador ++;
                printf("====================================\n");
                mostrar_una_venta(venta_actual);
            }
        }
        fclose(archivo_temp);
    }
    printf("====================================\n");
    printf("\nSe han encontrado %d registros de ventas para el cliente %d\n", contador, id_cliente);
}

void listar_ventas_por_mes( char nombre_archivo[], int mes, int anyo )
{
    Venta venta_actual;
    int contador = 0;
    FILE *archivo_temp;
    archivo_temp = fopen( nombre_archivo, "rb" );
    if( archivo_temp != NULL )
    {
        while(  fread(&venta_actual, sizeof(Venta), 1, archivo_temp) != 0 )
        {
            if( venta_actual.mes == mes && venta_actual.anio == anyo )
            {
                contador ++;
                printf("====================================\n");
                mostrar_una_venta(venta_actual);
            }
        }
        fclose(archivo_temp);
    }
    printf("\nSe han encontrado %d registros de ventas para el mes %.2d\n", contador, mes);
}

/*
FUNCIONES PARA REALIZAR CALCULOS
*/
float calcular_total_diario( char nombre_archivo[], int dia, int mes, int anyo )
{
    float total = 0;
    float precio_aux = 1;
    Venta actual;
    FILE *archivo;

    archivo = fopen( nombre_archivo, "rb");
    if( archivo != NULL )
    {
        while( fread(&actual, sizeof(Venta), 1, archivo) != 0 )
        {
            if( actual.anio == anyo && actual.mes == mes && actual.dia == dia && actual.anular != 's' )//es decir q es el mismo dia
            {
                precio_aux = obtener_precio( actual.idProducto );
                total = total + actual.cantidad * precio_aux;
            }
        }
        fclose(archivo);
    }

    return total;
}

float obtener_precio( int id_prod )
{
    Producto current;
    current = get_producto_por_id( id_prod );
    return current.pvp;
}

float calcular_promedio_mensual()
{
    float promedio = 0.0;
    float suma = 0;
    int dia_0 = 1, mes_0, anyo_0;
    float matriz_mes[4][7];
    int f = 0, c = 0;

    printf("Ingrese el mes y el anyo que desea calular el promedio \n");
    printf("Mes: \n");
    fflush( stdin );
    scanf( "%d", &mes_0 );
    printf("Anyo: \n");
    fflush( stdin );
    scanf( "%d", &anyo_0 );

    for( f = 0; f < 4; f++ )
    {
        for( c = 0; c < 7; c++ )
        {
            matriz_mes[f][c] = calcular_total_diario( REGISTRO_VENTAS, dia_0, mes_0, anyo_0 );
            dia_0++;
        }
    }

    for( f = 0; f < 4; f++ )
    {
        for( c = 0; c < 7; c++ )
        {
            suma = suma + matriz_mes[f][c];
        }
    }
    promedio = suma / 28;

    return promedio;
}

/*
FUNCIONES PARA MANEJAR EL SUBMENU VENTAS
*/
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
    int id_client;
    int m_dia, m_mes, m_anyo;

    switch( op )
    {
    case 1:
        venta_actual = alta_de_ventas();
        guardar_venta_archivo( REGISTRO_VENTAS, venta_actual);
        break;
    case 2:
        anular_venta();
        break;
    case 3:
        id_client = get_idCliente();
        listar_ventas_por_cliente( REGISTRO_VENTAS, id_client );
        break;
    case 4:
        ingresar_fecha_validada( &m_dia, &m_mes, &m_anyo);
        listar_ventas_por_mes( REGISTRO_VENTAS, m_mes, m_anyo );
        break;
    case 5:
        printf( "\nEl promedio mensual es %f", calcular_promedio_mensual() );
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

int buscar_producto_por_nombre( char nombre_producto[])
{
    Producto existente;
    int existe = 0;
    FILE *archivo_prods;
    archivo_prods = fopen( "producto.bin", "rb" );
    if( archivo_prods != NULL )
    {
        while( fread( &existente, sizeof(Producto), 1, archivo_prods ) != 0 && existe == 0 )
        {
            if( strcmpi(existente.producto, nombre_producto) == 0  )
            {
                existe = 1;
            }
        }
    }else{
        existente.id = 0;
    }
    return existente.id;
}
int buscar_producto_por_id( int id_buscar )
{
    Producto existente;
    int existe = 0;
    FILE *archivo_prods;
    archivo_prods = fopen( "producto.bin", "rb" );
    if( archivo_prods != NULL )
    {
        while( existe == 0 && fread( &existente, sizeof(Producto), 1, archivo_prods ) != 0 )
        {
            if( existente.id == id_buscar )
            {
                existe = 1;
            }
        }
        fclose(archivo_prods);
    }else{
        existente.id = 0;
    }
    return existente.id;
}

Producto get_producto_por_id( int id_buscar )
{
    Producto existente;
    int existe = 0;
    FILE *archivo_prods;
    archivo_prods = fopen( "producto.bin", "rb" );
    if( archivo_prods != NULL )
    {
        while( existe == 0 && fread( &existente, sizeof(Producto), 1, archivo_prods ) != 0 )
        {
            if( existente.id == id_buscar )
            {
                existe = 1;
            }
        }
        fclose(archivo_prods);
    }
    return existente;
}

/*  IMPLEMENTACION PARA EL MENU INTEGRADOR  */

void ventas_menu_altas( void )
{
    Venta venta_actual;
    venta_actual = alta_de_ventas();
    guardar_venta_archivo( REGISTRO_VENTAS, venta_actual);
    system("pause");
    VENTAS_MENU.show();
}
void ventas_menu_lista_cliente( void )
{
    int id_client;
    id_client = get_idCliente();
    listar_ventas_por_cliente( REGISTRO_VENTAS, id_client );
    system("pause");
    VENTAS_MENU.show();
}
void ventas_menu_lista_mes( void )
{
    int m_dia, m_mes, m_anyo;
    ingresar_fecha_validada( &m_dia, &m_mes, &m_anyo);
    listar_ventas_por_mes( REGISTRO_VENTAS, m_mes, m_anyo );
    system("pause");
    VENTAS_MENU.show();
}
void ventas_menu_promedio( void )
{
    printf( "\nEl promedio mensual es %.2f \n", calcular_promedio_mensual() );
    system("pause");
    VENTAS_MENU.show();
}


