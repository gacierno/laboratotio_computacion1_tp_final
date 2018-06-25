#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// NUEVO //////////////////////

//Menu PRODUCTOS_MENU;

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
        fflush(stdin);
        fgets(&a.producto,30,stdin);
        fflush(stdin);
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
            guardarArchivo(aux);
            printf("Desea ingresar otro producto? S/N\n");
            fflush(stdin);
            scanf("%c",&control);
        }
    }
    fclose(arch);
//    PRODUCTOS_MENU.show();
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


Producto verificarNombre( Producto a )
{
    FILE *arch;
    arch = fopen("producto.bin","r+b");
    Producto aux;
    char nombre[30];
    if ( arch == NULL)
    {
        printf("El archivo no existe\n");
    }
    else
    {
        while((fread(&aux,sizeof(Producto),1,arch))>0)
        {

            //compararProductos(a,aux);
            while (strcmp( (a).producto,(aux).producto )== 0)
            {
                printf("Su producto esta repetido, modifiquelo\n");
                a=nuevoProducto();
            }
        }
    }
    fclose(arch);
    return a;
}
void guardarArchivo(Producto a)
{
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
        a=verificarNombre(a);
        fwrite(&a,sizeof(Producto),1,arch);
    }
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
void bajaProducto(void)
{
    int pos=0;
    Producto aux;
    printf("Ingrese id a bajar\n");
    scanf("%i",&pos);
    FILE *arch;
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
            fseek(arch,sizeof(Producto)*(pos-1),SEEK_SET);
            fwrite(&aux,sizeof(Producto),1,arch);
        }
    }

    fclose(arch);
    //PRODUCTOS_MENU.show();
}


void modificar(void)
{
    int pos=0;
    Producto a;
    printf("Ingrese ID del producto a modificar\n");
    scanf("%i",&pos);
    FILE *arch;
    arch= fopen("producto.bin","r+b");
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
            printf("Ingrese nombre del producto\n");
            fflush(stdin);
            fgets(&a.producto,30,stdin);
            fflush(stdin);
            printf("Ingrese cantidad de productos\n");
            scanf("%i",&a.stock);
            printf("Ingrese costo del producto\n");
            scanf("%f",&a.costo);
            printf("Ingrese el precio de venta del producto\n");
            scanf("%f",&a.pvp);
            printf("El producto esta activo S/N\n");
            fflush(stdin);
            scanf("%c",&a.baja);
            fseek(arch,sizeof(Producto)*(pos-1),SEEK_SET);
            fwrite(&a,sizeof(Producto),1,arch);
        }
    }
    fclose(arch);
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
void mostrarTodosProductos (void)
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
   // PRODUCTOS_MENU.show();
}

void menuProductos()
{
    int opcion=0;
    char control='s';
    while (control=='s')
    {
        printf("MENU DE PRODUCTOS\n\n 1 INGRESAR NUEVO PRODUCTO\n 2 BAJAR PRODUCTO\n 3 MODIFICAR PRODUCTO\n 4 LISTA DE PRODUCTOS\n 0 SALIR\n");
        scanf("%i",&opcion);
        switch(opcion)
        {
            case 1:
            {
                agregarProducto();
                break;
            }
            case 2:
            {
                bajaProducto();
                break;
            }
            case 3:
            {
                modificar();
                break;
            }
            case 4:
            {
                mostrarTodosProductos();
                break;
            }
            case 0:
            {
                return 0;
                break;
            }
            printf("Desea realizar otra operacion? S/N\n");
            fflush(stdin);
            scanf("%c",&control);
        }
    }
}


int main()
{
   menuProductos();
}
