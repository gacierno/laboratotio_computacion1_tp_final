#include <stdio.h>
#include <stdlib.h>
#include "ventas.h"

int main()
{
    Venta nueva;
    nueva = alta_de_ventas();
    mostrar_una_venta( nueva );
    printf("Hello world!\n");
    return 0;
}
