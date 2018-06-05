#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
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
