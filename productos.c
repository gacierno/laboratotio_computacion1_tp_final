#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// NUEVO //////////////////////

Menu PRODUCTOS_MENU;

typedef struct{
    int id;
    char producto[20];
    int stock;
    float costo;
    float pvp;
    char baja; //‘s’ activo o ‘n’ inactivo
}Producto;


Producto nuevoProducto(void)
{
        Producto a;
        a.id=1 + contarRegistros("productos.bin");
        printf("La ID del producto es: %i\n",a.id);
        printf("Ingrese nombre del producto\n");
        scanf("%s",&a.producto);
        printf("Ingrese cantidad de productos\n");
        scanf("%i",&a.stock);
        printf("Ingrese costo del producto\n");
        scanf("%f",&a.costo);
        printf("Ingrese el precio de venta del producto\n");
        scanf("%f",&a.pvp);
        printf("El producto esta activo S/N\n");
        fflush(stdin);
        scanf("%c",&a.baja);
        return a;
}
void agregarProducto(void)
{
    Producto aux;
    char control = 's';
    FILE *arch;
    arch=fopen("producto.bin","rb");
    if(arch==NULL)
    {
        fclose(arch);
        fopen("producto.bin","wb");
    }
    else
    {
        fclose(arch);
        fopen("producto.bin","ab");
    }
    if (arch!=NULL)
    {
        while(control=='s')
        {
            aux=nuevoProducto();
            fwrite(&aux,sizeof(Producto),1,arch);
            printf("Desea ingresar otro producto? S/N\n");
            fflush(stdin);
            scanf("%c",&control);
        }
    }
    fclose(arch);
    PRODUCTOS_MENU.show();
}
int contarRegistros( void )
{
    int cant=0,div=0,total=0;
    //abrir el archivo lecctura
    FILE *arch;
    arch= fopen("producto.bin","rb");
    if(arch == NULL)
    {
        printf("El archivo no existe\n");
    }
    else
    {
      //ir hasta el final
    fseek(arch,0,SEEK_END);
    //contar cuanto bytes
    total=ftell(arch);
    //dividirlo por el tamanio del registro
      div=sizeof(Producto);
      cant=total/div;
    }
    fclose(arch);
    //dvolver el numero
    return cant;



}

void compararProductos(Producto *a,Producto *aux)
{
    char control;


    while (strcmp( (*a).producto,(*aux).producto )== 0)
    {
        printf("El nombre del producto esta repetido, desea modificarlo? s/n\n");
        fflush(stdin);
        scanf("%c",&control);
        if(control=='s')
        {
            printf("Ingrese un nombre nuevo para su producto\n");
            scanf("%s",a->producto);
        }
    }

}


void buscarProductos( Producto a )
{
    FILE *arch;
    arch = fopen("producto.bin","rb");
    Producto aux;
    if ( arch == NULL)
    {
        printf("El archivo no existe\n");
    }
    else
    {
        while((fread(&aux,sizeof(Producto),1,arch))>0)
        {

            compararProductos(&a,&aux);
        }
    }
    fclose(arch);
}
void guardarArchivo(Producto a)
{
    FILE *arch;
    arch= fopen("producto.bin","ab");
    buscarProductos(a);
    fwrite(&a,sizeof(Producto),1,arch);
    fclose(arch);
}
int buscarPorID( Producto a )
{
    //abrir el archivo en lectura
    //recorrer el archivo
    //comparar el producto a con el aux

    //comparar el producto a pasado por parametro con el aux
    //aux es el producto leido del archivo
    //si son iguales retornar la pos
    //si no encuentra retornar -1

    FILE *arch;
    arch = fopen("producto.bin","rb");
    Producto aux;
    int flag= -1;
    if ( arch == NULL)
    {
        printf("El archivo no existe\n");
    }
    else
    {
        while( (fread(&aux,sizeof(Producto),1,arch))>0 && flag==-1)
        {
            if(a.id == aux.id )
            {
                flag=a.id;
            }
        }
    }

    fclose(arch);
    return flag;
}
void bajaProducto(int pos)
{
    FILE *arch;
    Producto aux;
    arch=fopen("producto.bin", "r+b");
    if (arch == NULL)
    {
        printf("El archivo no existe\n");
    }
    else
    {
        if(pos<1)
        {
            printf("No se encontro el producto\n");
        }
        else
        {
            fseek(arch,sizeof(Producto)*(pos-1),SEEK_SET);
            fread(&aux,sizeof(Producto),1,arch);
            aux.baja='n';
            fseek(arch,sizeof(Producto)*pos-1,SEEK_SET);
            fwrite(&aux,sizeof(Producto),1,arch);
        }
    }

    fclose(arch);
    PRODUCTOS_MENU.show();
}

void modificarProducto(Producto *a)
{
    char control='s';
    int opcion;

    while (control=='s')
    {
        printf("Ingrese la opcion que desea cambiar\n 1 Nombre\n 2 Costo\n 3 Precio de valor del producto\n 4 Stock\n ");
        switch(opcion)
        {
            case 1:
            {
                printf("Ingrese nuevo producto\n");
                scanf("%s",a->producto);
            }
            case 2:
            {
                printf("Ingrese nuevo costo\n");
                scanf("%f",a->costo);
            }
            case 3:
            {
                printf("Ingrese nuevo precio de valor del producto\n");
                scanf("%f",a->pvp);
            }
            case 4:
            {
                printf("Ingrese nuevo stock\n");
                scanf("%i",a->stock);
            }
        }
        printf("Desea seguir modificando el producto? s/n\n");
        fflush(stdin);
        scanf("%c",&control);
    }
    PRODUCTOS_MENU.show();
}
void modificar(int pos)
{
    FILE *arch;
    arch= fopen("producto.bin","w+b");
    Producto a;
    if (arch == NULL)
    {
        printf("El archivo no existe\n");
    }
    else
    {
        if(pos<1)
        {
            printf("No se encontro el producto\n");
        }
        else
        {
            fseek(arch,sizeof(Producto)*pos-1,SEEK_SET);
            fread(&a,sizeof(Producto),1,arch);
            modificarProducto(&a);
            fseek(arch,sizeof(Producto)*pos-1,SEEK_SET);
            fwrite(&a,sizeof(Producto),1,arch);
        }
    }
}

void mostrarProducto( Producto uno )
{
    printf( "El producto cargado tiene el siguiente detalle: \n" );
    printf( "ID:........%i\n", uno.id );
    printf( "Producto:.......%s\n", uno.producto );
    printf( "Baja:.........%c\n", uno.baja );
    printf( "Stock..:.......%i\n", uno.stock );
    printf( "pvp:........%f\n", uno.pvp );
    printf( "Costo:.......%f\n", uno.costo );
}
void mostrarTodosProductos (char nombre[])
{
    Producto aux;
    FILE *arch;
    arch=fopen("producto.bin","rb");
    if(arch!= NULL)
    {
        while((fread(&aux,sizeof(Producto),1,arch))>0)
        {
            mostrarProducto(aux);
        }
    }
    fclose(arch);
    PRODUCTOS_MENU.show();
}
