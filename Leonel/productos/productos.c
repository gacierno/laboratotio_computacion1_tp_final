#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// NUEVO //////////////////////


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

int contarRegistros( char ar[] )
{
    int cant=0,div=0,total=0;
    //abrir el archivo lecctura
    FILE *arch;
    arch= fopen(ar,"rb");
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

    while ( (*a).id == (*aux).id )
    {
        printf("La id esta repetida, modificala \n");
        fflush(stdin);
        scanf("%c",&control);
        if(control=='s')
        {
            printf("Ingrese una nueva ID\n");
            scanf("%i",a->id);
        }
    }
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


void buscarProductos(char ar[], Producto a )
{
    FILE *arch;
    arch = fopen(ar,"rb");
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
void guardarArchivo(char ar[],Producto a)
{
    FILE *arch;
    arch= fopen(ar,"ab");
    buscarProductos(ar,a);
    fwrite(&a,sizeof(Producto),1,arch);
    fclose(arch);
}
int buscarPorID(char ar[], Producto a )
{
    //abrir el archivo en lectura
    //recorrer el archivo
    //comparar el producto a con el aux

    //comparar el producto a pasado por parametro con el aux
    //aux es el producto leido del archivo
    //si son iguales retornar la pos
    //si no encuentra retornar -1

    FILE *arch;
    arch = fopen(ar,"rb");
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
void bajaProducto(char ar[],int pos)
{
    FILE *arch;
    Producto aux;
    arch=fopen(ar, "r+b");
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

}
void modificar(char ar[],int pos)
{
    FILE *arch;
    arch= fopen(ar,"w+b");
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
int main()
{
    Producto nuevo;
    char palabra[]="productos.bin";
    nuevo = nuevoProducto();
    guardarArchivo(palabra,nuevo);
    printf("%i",sizeof(Producto));
    return 0;
}





//  VIEJO //////////////////////

/*typedef struct{
    int id;
    char producto[20];
    int stock;
    float costo;
    float pvp;
    char baja; //‘s’ o ‘n’
}Producto;

void cargarProducto(char ar[],Producto a,FILE *arch)
{
    char control='s';
    Producto aux;

    if(fopen(arch,"rb")==NULL)
    {
        printf("El archivo no existe\n");


    }
    else
    {
        arch=fopen(ar,"w+b");
        if (fopen(ar,"w+b")==NULL)
        {
            printf("Error\n");
        }
        else
        {
            printf("Se creo correctamente\n");
        }


    while(control=='s')
    {
        printf("Ingrese ID del producto\n");
        scanf("%i",&a.id);
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


         while(!feof(arch))
        {
            fread(&aux,sizeof(Producto),1,arch);        //se hace un bucle infinito despues de ingresar el primer producto
             printf("prueba\n\n");


            if (a.id==aux.id)
            {
                printf("La id esta repetida, desea modificarla? s/n\n");
                fflush(stdin);
                scanf("%c",&control);
                if(control=='s')
                {
                    printf("Ingrese una nueva ID\n");
                    scanf("%i",&a.id);
                }
            }
            else if (strcmp(a.producto,aux.producto)==0)
            {
                printf("El nombre del producto esta repetido, desea modificarlo? s/n\n");
                fflush(stdin);
                scanf("%c",&control);
                if(control=='s')
                {
                    printf("Ingrese un nombre nuevo para su producto\n");
                    scanf("%s",&a.producto);
                }
            }
            else
            {
                fwrite(&a,sizeof(Producto),1,arch);
            }
            printf("Desea ingresar otro producto? S/N\n");
            fflush(stdin);
            scanf("%c",&control);
        }

    }
    fclose(arch);
    }
}
void buscarProducto(char ar[],Producto a,FILE *arch)
{
    char buscado[30];
    Producto aux;
    int pos=0;
    printf("Ingrese el nombre del producto a buscar\n");
    scanf("%s",&buscado);

    if(fopen(arch,"rb")==NULL)
    {
        printf("El archivo no existe\n");
    }
    else
    {
        fopen(arch,"w+b");
        while(!feof(arch))
        {
            rewind (arch);
            pos=fread(&a,sizeof(Producto),1,arch)
            if(strcmp(buscado,a.producto)==0)
            {
                printf("El producto a sido encontrado, ACTIVO: %c \n",a.baja)
                printf("Desea modificarlo? S/N\n");
                fflush(stdin);
                scanf("%c",&control);
                if(control=='s')
                {
                    if (a.baja=='n')
                    {
                        a.baja='s';
                    }
                    else
                    {
                        a.baja='n';
                    }
                    fseek (bin , (long) (-1) * sizeof (Producto), SEEK_CUR);
                }
                else
                {
                    printf("El producto no se modificara\n");
                }
            }
            else
            {
                printf("EL producto no se encontro\n");
            }
        }
        fclose(arch);
    }
}
int main()
{
    char archivo[30]="Productos.bin";
    FILE *arch;
    Producto leo;
    cargarProducto(archivo,leo);
    buscarProducto(archivo,leo,arch)
    printf("prueba\n\n");
    return 0;
}
*/
