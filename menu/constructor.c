#include <string.h>
#include "./menu.c"
#include "../clientes/clientes.c"
#include "../productos.c"
#include "../ventas/ventas.c"

Menu MAIN_MENU;
Menu CLIENTS_MENU;
Menu PRODUCTOS_MENU;
Menu VENTAS_MENU;

/*
  ================================
   CLIENTS MENU
  ================================
*/

void showClientsMenu(){
  _showMenu(&CLIENTS_MENU);
}

Menu constructClientsMenu(){

  strcpy(CLIENTS_MENU.title,"Clients");
  CLIENTS_MENU.show = showClientsMenu;
  CLIENTS_MENU.optionCount = 5;

  MenuOption mostrar;
  mostrar.function = &showAllClients;
  strcpy(mostrar.text,"Lista de clientes");
  CLIENTS_MENU.options[0] = mostrar;

  MenuOption crear;
  crear.function = &createClients;
  strcpy(crear.text,"Crear clientes");
  CLIENTS_MENU.options[1] = crear;


  MenuOption modificar;
  modificar.function = &modificarCliente;
  strcpy(modificar.text,"Modificar cliente");
  CLIENTS_MENU.options[2] = modificar;


  MenuOption baja;
  baja.function = &darDeBaja;
  strcpy(baja.text,"Bajas");
  CLIENTS_MENU.options[3] = baja;


  MenuOption volver;
  volver.function = MAIN_MENU.show;
  strcpy(volver.text,"Volver al menu principal");
  CLIENTS_MENU.options[4] = volver;

}

/*
  ================================
   PRODUCTOS MENU
  ================================
*/

void showProductosMenu(){
  _showMenu(&PRODUCTOS_MENU);
}

Menu constructProductosMenu(){

  strcpy(PRODUCTOS_MENU.title,"Productos");
  PRODUCTOS_MENU.show = showProductosMenu;
  PRODUCTOS_MENU.optionCount = 5;

  MenuOption mostrar;
  mostrar.function = &mostrarTodosProductos;
  strcpy(mostrar.text,"Lista de productos");
  PRODUCTOS_MENU.options[0] = mostrar;

  MenuOption crear;
  crear.function = &agregarProducto;
  strcpy(crear.text,"Crear producto");
  PRODUCTOS_MENU.options[1] = crear;


  MenuOption modificate;
  modificate.function = &modificar;
  strcpy(modificate.text,"Modificar producto");
  PRODUCTOS_MENU.options[2] = modificate;


  MenuOption baja;
  baja.function = bajaProducto;
  strcpy(baja.text,"Bajas");
  PRODUCTOS_MENU.options[3] = baja;


  MenuOption volver;
  volver.function = MAIN_MENU.show;
  strcpy(volver.text,"Volver al menu principal");
  PRODUCTOS_MENU.options[4] = volver;

}

/*
  ================================
   VENTAS MENU
  ================================
*/

void showVentasMenu(){
  _showMenu(&VENTAS_MENU);
}

Menu constructVentasMenu(){

    strcpy(VENTAS_MENU.title,"Ventas");
    VENTAS_MENU.show = showVentasMenu;
    VENTAS_MENU.optionCount = 6;

    MenuOption altaV;
    altaV.function = &ventas_menu_altas;
    strcpy(altaV.text,"Nueva Venta");
    VENTAS_MENU.options[0] = altaV;

    MenuOption anularV;
    anularV.function = &anular_venta;
    strcpy(anularV.text,"Anular Venta");
    VENTAS_MENU.options[1] = anularV;

    MenuOption listarVentasXCliente;
    listarVentasXCliente.function = &ventas_menu_lista_cliente;
    strcpy(listarVentasXCliente.text,"Listar Ventas por Cliente");
    VENTAS_MENU.options[2] = listarVentasXCliente;

    MenuOption listarVentasXMes;
    listarVentasXMes.function = &ventas_menu_lista_mes;
    strcpy(listarVentasXMes.text,"Listar Ventas del Mes");
    VENTAS_MENU.options[3] = listarVentasXMes;

    MenuOption promedioVentas;
    promedioVentas.function = &ventas_menu_promedio;
    strcpy(promedioVentas.text,"Promedio de ventas del mes");
    VENTAS_MENU.options[4] = promedioVentas;

    MenuOption volver;
    volver.function = MAIN_MENU.show;
    strcpy(volver.text,"Volver al menu principal");
    VENTAS_MENU.options[5] = volver;
}


/*
  ================================
   MAIN MENU
  ================================
*/

void showMainMenu(){
  _showMenu(&MAIN_MENU);
}

Menu constructMainMenu(){

  strcpy(MAIN_MENU.title,"MAIN MENU");
  MAIN_MENU.show = showMainMenu;
  MAIN_MENU.optionCount = 3;

  MenuOption client;
  strcpy(client.text,CLIENTS_MENU.title);
  client.function = CLIENTS_MENU.show;

  MenuOption producto;
  strcpy(producto.text,PRODUCTOS_MENU.title);
  producto.function = PRODUCTOS_MENU.show;

  MenuOption venta;
  strcpy( venta.text, VENTAS_MENU.title );
  venta.function = VENTAS_MENU.show;

  MAIN_MENU.options[0] = client;
  MAIN_MENU.options[1] = producto;
  MAIN_MENU.options[2] = venta;
}


/*
  ================================
   BUNDLE CONSTRUCTOR
  ================================
*/

Menu constructNavigation(){

  constructClientsMenu();
  constructProductosMenu();
  constructVentasMenu();
  constructMainMenu();

  return MAIN_MENU;
}
