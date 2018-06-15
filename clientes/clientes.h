typedef struct{
    int id;
    int dni;
    char nombre[20];
    char apellido[20];
    char telefono[20];
    char domicilio[30];
    char baja;
}Cliente;

void createCliente(Cliente *);
void createClients( void );
void printClient(Cliente);
void showAllClients( void );
Cliente getLastClient( void );
Cliente getClientByDNI( int );
Cliente disableClient(int);
Cliente enableClient(int);
void updateClient(Cliente *,int);
