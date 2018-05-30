# laboratotio_computacion1_tp_final
TP programacion UTM primer cuatrimestrre

### Objetivos

* Gestionar las ventas por clientes y control de stock y guardarlos en un archivo binario.

### Objetivos teoricos

* Estructuras
* Arreglos
* Matrices
* Archivos

### Metodologia de trabajo

* Trabajo colaborativo
* Trabajo en equipo de minimo 2 integrantes y maximo 3
* En el caso de dos integrantes cada uno deberá hacerse responsable de la mitad del trabajo y mediante  un cuadro indicar cuáles fueron las tareas que cada uno cumplió.
* En el caso de ser 3 integrantes cada uno debe realizar un ABM
* En el caso de que cada uno de los integrantes no pueda seguir las opciones son:
  * Hacerse responsable de las tareas del compañero o 
  * Cumplir cada uno con las partes asignadas en un primer momento

### Estructuras

```
typedef struct{
    int id;
    int dni;
    char nombre[20];
    char apellido[20];
    char teléfono[20];
    char domicilio[30];
    char baja; //‘s’ o ‘n’
}Cliente;

typedef struct{
    int id;
    char producto[20];
    int stock;
    float costo;
    float pvp;
    char baja; //‘s’ o ‘n’
}Producto;

typedef struct{
    int id;
    int idCliente;
    int idProducto;
    int cantidad;
    int dia;
    int mes;
    int anio;
    char pagado
    char anular; //‘a’
}Venta;
```

## Autores
* **Acierno German Eliseo**
* **Amilcar Leonel**
* **Errobidart Gaspar Gabriel**
