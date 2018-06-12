#include <stdlib.h>
#include <stdio.h>
#include "ventas.h"

Venta crear_nueva_venta(){
    FILE *datafile;
    Venta ultimaventa;
    Venta nuevaventa;
    int ultimoId = 0;

    datafile = fopen("ventas.dat", "rb");
    if(datafile != NULL)
    {
        while(!feof(datafile))
        {
            fread(&ultimaventa, sizeof(Venta), 1, datafile);
            if(ultimaventa.id > ultimoId)
            {
                ultimoId = ultimaventa.id;
            }
        }
    }
    fclose(datafile);
}
