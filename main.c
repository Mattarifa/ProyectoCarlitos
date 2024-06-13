#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#define CURRENT_YEAR 2024

#define LONGITUD 20

int const consecionariaDNI = 12345678;

typedef struct {        //patente
	char letras[5];
	int numeros;

} Patente;

typedef struct {        //guardar autos en memoria
	Patente patente;
	char marca[30];
	char modelo[30];
	int anio;
	int kms;
	int dniTitular;
	float precioDeAdquisicion;
} AutoArchivo;

typedef struct {        //persona
	int dni;
	char nombre[40];
	int telefono;
	char direccion[50];
	char rol[11]; //comprador o vendedor

} Persona;

typedef struct {        //para agregar autos
	Patente patente;
	char marca[30];
	char modelo[30];
	int anio;
	int kms;
	Persona Titular;
	float precioDeAdquisicion;
} Auto;

typedef struct {        //fecha
	int dia;
	int mes;
	int anio;

} Fecha;

typedef struct {        //venta
	Fecha fecha;
	Patente autoAVender;
	float precioVenta;
	float ganancia;
	int dniComprador;
	int dniVendedor;

} Venta;

void iniciarPrograma();
void menu();
void registrarse();
int login(char*,char*);
void agregarAutoArchivo();
void agregarPersonas();
void mostrarAutoArchivo();
void mostrarPersonas();
void agregarVentas();
void mostrarVentas();
void modificarAuto(int);
void modificarPersona(int);
void infoPersona();
void infoAuto();
void verVentas();
void infoVenta(int);
void agregarAuto();
float recaudadoEnDeterminadoMes(int,int);
float mayorGanancia();
void Autos10anos();

int main()
{

    char usuario[LONGITUD + 1];
    char clave[LONGITUD + 1];
    int intento =0;
    int ingresa = 0;

    iniciarPrograma();



    return 0;
}
void iniciarPrograma(){
    char usuario[LONGITUD +1];
    char clave[ LONGITUD +1];
    int intento=0;
    int ingresa=0;
    int opcion;
   printf("\n\t\t-------------------------------------------------------\n");
    printf("\n\t\tSi desea registrarse ingrese 1, para logearse ingrese 2:\n ");
    printf("\n\t\t-------------------------------------------------------\n");
    scanf("%d",&opcion);
    fflush(stdin);
    switch(opcion){
    case 1:
        registrarse();
        printf("\n\tSi desea logearse ingrese 2, si desea salir ingrese 3: \n");
        scanf("%d",&opcion);
        fflush(stdin);
        if (opcion == 2){
        while(!ingresa && intento<3){
        ingresa=login(usuario,clave);
        if(!ingresa){
            printf("\n\tUsuario y/o contrasenia incorrectos");
            intento++;
        }else if(ingresa){
            menu();
        }
    }
        }
        break;
    case 2:
    while(!ingresa && intento<3){
        ingresa=login(usuario,clave);
        if(!ingresa){
            printf("\n\tUsuario y/o contrasenia incorrectos");
            intento++;
        }else if(ingresa){
            menu();
        }
    }
        break;

    case 3:
        printf("\n\tQue tenga un lindo dia :D");
    }
}

void menu()
{
    char c='s';
    int a,pos;
    Auto* autos = NULL;
    int count = 0;

    int posAuto = 0;
    int posPersona = 0;
    int posVenta = 0;

    char patenteLetras[4];
    int patenteNumeros = 0;

    int dniPersona=0;

    int mes=0;
    int anio=0;

    while(c=='s')
    {
        printf("ingrese que desea hacer:\n");
        printf("____________________________\n");
        printf("Agregar un auto: \t(1) |\n");
        printf("Ver lista de autos: \t(2) |\n");
        printf("Modificar un auto: \t(3) |\n");
        printf("Ver info de un auto: \t(4) |\n");
        printf("Agregar una persona: \t(5) |\n");
        printf("Modificar una persona:\t(6) |\n");
        printf("ver lista de personas:\t(7) |\n");
        printf("ver info de persona:  \t(8) |\n");
        printf("ver autos en venta:  \t(9) |\n"); //con dni hardcodeado de consecionaria
        printf("Ver ventas:\t\t(10)|\n");
        printf("ver info de una venta:\t(11)|\n");
        printf("Agregar una venta:\t(12)|\n");
        printf("Recaudado en un mes\t(13)|\n");
        printf("Ver antiguedad de auto:\t(14)|\n");
        scanf("%d",&a);
        switch(a)
        {
            case 1:
                agregarAuto(&autos, &count);
                agregarAutoArchivo(autos, count);
                mostrarAutoArchivo();
            break;
            case 2:
                mostrarAutoArchivo();
            break;
            case 3:
                mostrarAutoArchivo();
                printf("ingrese la pos del auto a modificar:");
                scanf("%d", &posAuto);
                while(posAuto < 0)
                {
                    printf("Error: ingrese un numero mayor a 0: ");
                    scanf("%d", &posAuto);
                }
                modificarAuto(posAuto);
            break;
            case 4:
                mostrarAutoArchivo();
                printf("Ingrese las letras de la patente del auto que quiere ver:: ");
                fflush(stdin);
                scanf("%s", &patenteLetras[0]);
                printf("Ingrese los numeros de la petente del auto que quiere ver: ");
                scanf("%d", &patenteNumeros);
                while(patenteLetras[4] >= a)
                {
                    printf("ERROR: Ingrese letras validas: ");
                    fflush(stdin);
                    scanf("%s", &patenteLetras[0]);
                }
                while(patenteNumeros > 999)
                {
                    printf("ERROR: Ingrese numeros validos: ");
                    scanf("%d", &patenteNumeros);
                }
                infoAuto(patenteLetras, patenteNumeros);
            break;
            case 5:
                agregarPersonas();
                mostrarPersonas();
            break;
            case 6:
		mostrarPersonas();
                scanf("%d", &posPersona);
                while(posPersona < 0)
                {
                    printf("Error: ingrese un numero mayor a 0: ");
                    scanf("%d", &posPersona);
                }
                modificarPersona(posPersona);
            break;
            case 7:
                mostrarPersonas();
            break;
            case 8:
                mostrarPersonas();
                printf("Ingrese dni de la persona que quiera ver: ");
                scanf("%d", &dniPersona);
                while(dniPersona < 0)
                {
                    printf("ERROR: Ingrese un dni valido: ");
                    scanf("%d", &dniPersona);
                }
                infoPersona(dniPersona);
            break;
            case 9:
                verAutosEnVenta();
            break;
            case 10:
                verVentas();
            break;
            case 11:
                printf("Ingrese la posicion de la venta que quiera ver: ");
                scanf("%d", &posVenta);
                while(posVenta < 0)
                {
                    printf("ERROR: Ingrese nuevamente la posicion: ");
                    scanf("%d", &posVenta);
                }
                infoVenta(posVenta);
            break;
            case 12:
                agregarVentas();
            break;
            case 13:
                printf("ingrese mes:");
                scanf("%d",&mes);
                printf("ingrese anio:");
                scanf("%d",&anio);
                while(mes < 1 || mes > 12)
                {
                    printf("ERROR: Ingrese un mes valido: ");
                    scanf("%d", &mes);
                }
                while(anio < 1999 || anio > 2024)
                {
                    printf("ERROR: Ingrese un anio valido: ");
                    scanf("%d", &anio);
                }
                printf("%.2f",recaudadoEnDeterminadoMes(mes,anio));
            break;
            case 14:
                Autos10anos();
            break;
            default:

            break;
        }
        printf("\nDesea continuar en el menu?(s/n):");
        fflush(stdin);
        scanf("%c",&c);
        system("cls");
    }

}
void registrarse()
{
    FILE *archivos= fopen("cuentas.bin","ab");
    if(archivos==NULL)
    {
        printf("error");
    }

    char usuario[LONGITUD +1];
    char clave[LONGITUD+1];
    printf("\n\t\t\tREGISTRO\n");
    printf("\n\t\t\t--------\n");
    printf("\n\tIngrese un nombre de usuario: ");
    fgets(usuario,LONGITUD+1,stdin);
    usuario[strcspn(usuario, "\n")]='\0';///strcspn(usuario, "\n") devuelve la posición del primer carácter en usuario que es /n, /0 para eliminar el salto de linea

    printf("\n\tIngrese una contrasena: ");
    fgets(clave,LONGITUD+1,stdin);
    clave[strcspn(clave,"\n")]='\0';

    fwrite(usuario,sizeof(char),LONGITUD+1,archivos);
    fwrite(clave,sizeof(char),LONGITUD+1,archivos);
    printf("\n\t\t---------------------------------");
    printf("\n\t\tUsuario registrado correctamente");
    printf("\n\t\t---------------------------------");

    fclose(archivos);




}

int login(char *usuario, char *clave)
{
    int flag=0;
    FILE*archi=fopen("cuentas.bin","rb");
    char archivoUsuario[LONGITUD+1];
    char archivoClave[LONGITUD+1];
    if (archi == NULL)
    {
        printf("Error al abrir el archivo\n");
        flag=1;
    }

    int i=0;

        printf ("\n\t\t\t\tINICIO DE SESION\n");
        printf ("\t\t\t\t----------------\n");
        printf("\n\tUSUARIO: ");
        fgets(usuario,LONGITUD+1,stdin);
        usuario[strcspn(usuario,"\n")]='\0';
        printf("\n\tCLAVE: ");

        while (1){
            char caracter = getch();
            if(caracter==13){
                clave[i]='\0';
                break;

            }else if(caracter == 8){
                if(i > 0){
                    i--;
                    printf("\b \b");
                }
            }else{
                if (i < LONGITUD){
                    printf("*");
                    clave[i]= caracter;
                    i++;
                }
            }
        }

         int autenticado=0;
    while (fread(archivoUsuario, sizeof(char), LONGITUD + 1, archi) &&
           fread(archivoClave, sizeof(char), LONGITUD + 1, archi)) {
        if (strcmp(usuario, archivoUsuario) == 0 && strcmp(clave, archivoClave) == 0) {
            autenticado=1;
            break;
        }
           }
        fclose(archi);
        return autenticado;
}
void verAutosEnVenta()
{
    AutoArchivo autoArch;
    FILE * archi = fopen("autosArch.bin","rb");

    if(archi!=NULL)
    {
        while(fread(&autoArch,sizeof(AutoArchivo),1,archi))
        {
            if(autoArch.dniTitular==consecionariaDNI)      //54123456
            {
                printf("-------------\n");
                printf("Patente:    %s-%d\n", autoArch.patente.letras, autoArch.patente.numeros);
                printf("Marca:      %s\n", autoArch.marca);
                printf("Modelo:     %s\n", autoArch.modelo);
            }
        }
        fclose(archi);
    }
    else
    {
        printf("No se pudo cargar la lista de autos");
    }
}
int buscarPersonaPorDNI(int dni, Persona* persona) {
    int flag = 0;
    Persona tempPersona;
    FILE* archivo = fopen("personas.bin", "rb");
    if (archivo != NULL) {
        while (fread(&tempPersona, sizeof(Persona), 1, archivo) > 0) {
            if (tempPersona.dni == dni) {
                *persona = tempPersona;
                flag = 1;
                break;
            }
        }
        fclose(archivo);
    } else {
        printf("NO se pudo abrir el archivo para buscar\n");
    }

    return flag;
}

void agregarAuto(Auto** autos, int* count) {
    Auto autito;
    Persona titular;
    char seguir = 's';

    while (seguir == 's') {
        printf("Ingrese las letras de la patente: ");
        scanf("%s", autito.patente.letras);

        printf("Ingrese los numeros de la patente: ");
        scanf("%d", &autito.patente.numeros);

        printf("Ingrese la marca del auto: ");
        scanf("%s", autito.marca);

        printf("Ingrese el modelo del auto: ");
        scanf("%s", autito.modelo);

        printf("Ingrese el anio del auto: ");
        scanf("%d", &autito.anio);

        printf("Ingrese el kilometraje del auto: ");
        scanf("%d", &autito.kms);

        printf("Ingrese DNI del titular del auto: ");
        scanf("%d", &autito.Titular.dni);

        if (buscarPersonaPorDNI(autito.Titular.dni, &titular) || autito.Titular.dni == consecionariaDNI)
            {
            if (autito.Titular.dni != consecionariaDNI)
            {
                autito.Titular = titular;
                strcpy(autito.Titular.rol, "comprador");
            }
            else
            {
                strcpy(autito.Titular.nombre, "Concesionaria");
                autito.Titular.telefono = 0;
                strcpy(autito.Titular.direccion, "Dirección de la Concesionaria");
                strcpy(autito.Titular.rol, "vendedor");
            }

            printf("Ingrese el precio de adquisicion del auto: ");
            scanf("%f", &autito.precioDeAdquisicion);

            *autos = realloc(*autos, (*count + 1) * sizeof(Auto));
            if (*autos == NULL)
            {
                printf("Error de asignacion de memoria\n");
                exit(1);
            }
            (*autos)[*count] = autito;
            (*count)++;
        }
        else
            {
            printf("ERROR: El titular con DNI %d no existe\n", autito.Titular.dni);
            }
        printf("¿Desea continuar? (s/n): ");
        scanf("%c", &seguir);
        fflush(stdin);
        system("cls");
    }
}
void agregarAutoArchivo(Auto* autos, int count) {
    AutoArchivo autoArch;
    FILE* archivo = fopen("autosArch.bin", "ab");
    if (archivo != NULL) {
        for (int i = 0; i < count; i++) {
            strncpy(autoArch.patente.letras, autos[i].patente.letras, sizeof(autoArch.patente.letras));
            autoArch.patente.numeros = autos[i].patente.numeros;
            strncpy(autoArch.marca, autos[i].marca, sizeof(autoArch.marca));
            strncpy(autoArch.modelo, autos[i].modelo, sizeof(autoArch.modelo));
            autoArch.anio = autos[i].anio;
            autoArch.kms = autos[i].kms;
            autoArch.dniTitular = autos[i].Titular.dni;
            autoArch.precioDeAdquisicion = autos[i].precioDeAdquisicion;

            fwrite(&autoArch, sizeof(AutoArchivo), 1, archivo);
        }
        fclose(archivo);
    } else {
        printf("error no se pudo abrir el catalogo\n");
    }
}

void agregarPersonas()
{
    Persona p;
    char c='s';
    FILE* archivo = fopen("personas.bin","wb");
    if (archivo != NULL) {
        while (c == 's' || c == 'S') {
            printf("Ingrese el DNI: ");
            scanf("%d", &p.dni);

            printf("Ingrese el nombre y apellido: ");
            scanf(" %39[^\n]", p.nombre);

            printf("Ingrese el telefono: ");
            scanf("%d", &p.telefono);

            printf("Ingrese la direccion de la persona(con numeros): ");
            scanf(" %49[^\n]", p.direccion);

            printf("Ingrese el rol (comprador o vendedor): ");
            scanf(" %10s", p.rol);
            fwrite(&p, sizeof(Persona), 1, archivo);

            printf("Desea seguir agregando personas? (s/n): ");
            scanf("%c", &c);
            while (getchar() != '\n');

            system("cls");
        }

        fclose(archivo);
    }
    else
    {
        printf("error no se pudo abrir el catalogo");
    }
}

void mostrarAutoArchivo()
{
    AutoArchivo autoArch;
    FILE* archivo = fopen("autosArch.bin", "rb");

    if(archivo!=NULL)
    {
        while(fread(&autoArch, sizeof(AutoArchivo), 1, archivo) > 0)
        {
            printf("-------------\n");
            printf("Patente:    %s-%d\n", autoArch.patente.letras, autoArch.patente.numeros);
            printf("Marca:      %s\n", autoArch.marca);
            printf("Modelo:     %s\n", autoArch.modelo);
        }
        fclose(archivo);
    } else
    {
        printf("error");
    }
}

void mostrarPersonas()
{
    Persona p;
    int i=1;
    FILE* archivo = fopen("personas.bin", "rb");

    if(archivo!=NULL)
    {
        while(fread(&p, sizeof(Persona), 1, archivo) > 0)
        {

            printf("-------------\n");
            printf("reg:%d\n",i++);
            printf("Dni:    \t%d\n", p.dni);
            printf("Nombre:      \t%s\n", p.nombre);
        }
        fclose(archivo);
    } else
    {
        printf("error");
    }
}

void agregarVentas()
{
    Venta v;
    char c='s';
    FILE* archivo = fopen("ventas.bin","wb");
    if(archivo!=NULL)
    {
        while(c=='s')
        {
            printf("ingrese dia, mes y anio de la venta:\n");
            scanf("%d %d %d",&v.fecha.dia, &v.fecha.mes, &v.fecha.anio);

            printf("ingrese las letras de la patente del auto a vender\n");
            fflush(stdin);
            scanf("%s",v.autoAVender.letras);
            printf("ingrese los numeros de la patente del auto a vender\n");
            scanf("%d",&v.autoAVender.numeros);

            printf("ingrese el precio de la venta\n");
            scanf("%f",&v.precioVenta);

            printf("ingrese la ganancia de la venta\n");
            scanf("%f",&v.ganancia);

            printf("ingrese el dni del comprador\n");
            scanf("%d",&v.dniComprador);

            printf("ingrese el dni del vendedor\n");
            scanf("%d",&v.dniVendedor);

            printf("desea continuar?(s/n)\n");
            fflush(stdin);
            scanf("%c",&c);

            fwrite(&v,sizeof(Venta),1,archivo);
        }

        fclose(archivo);
    }
    else
    {
        printf("error no se pudo abrir el catalogo");
    }
}

void mostrarVentas()
{
    Venta v;
    FILE* archivo = fopen("ventas.bin", "rb");

    if(archivo!=NULL)
    {
        while(fread(&v, sizeof(Venta), 1, archivo) > 0)
        {
            printf("-------------\n");
            printf("Fecha:        %d/%d/%d\n", v.fecha.dia, v.fecha.mes, v.fecha.anio);
            printf("Patente:      %s-%d\n", v.autoAVender.letras, v.autoAVender.numeros);
            printf("PrecioVenta:  %.2f\n", v.precioVenta);
            printf("Ganancia:     %.2f\n", v.ganancia);
            printf("DniComprador: %d\n", v.dniComprador);
            printf("DniVendedor:  %d\n", v.dniVendedor);
        }
        fclose(archivo);
    } else
    {
        printf("error");
    }
}
void modificarAuto(int pos)
{

   FILE *archivo = fopen("autosArch.bin", "r+b");
   AutoArchivo autoArch;
    char i;
    char seguir = 's';

    if(archivo!=NULL)
    {
        fseek(archivo, (pos-1)*sizeof(AutoArchivo), SEEK_SET);
        fread(&autoArch, sizeof(AutoArchivo), 1, archivo);
        fseek(archivo, (pos-1)*sizeof(AutoArchivo), SEEK_SET);
        while (seguir == 's')
        {
            printf("Que dato desea modificar? (p(patente)/m(marca)/x(modelo)/a(anio)/k(kms)/d(dni)/v(precio)): ");
            fflush(stdin);
            scanf("%c", &i);

            switch(i)
            {
                case 'p':
                        printf("Ingrese la patente: ");
                        fflush(stdin);
                        scanf("%s %d", autoArch.patente.letras, &autoArch.patente.numeros);
                break;
                case 'm':
                        printf("Ingrese una nueva marca: "),
                        fflush(stdin);
                        scanf("%s", autoArch.marca);
                break;
                case 'x':
                        printf("Ingrese un nuevo modelo: ");
                        fflush(stdin);
                        scanf("%s", autoArch.modelo);
                break;
                case 'a':
                        printf("Ingrese nuevo anio: ");
                        scanf("%d", &autoArch.anio);
                break;
                case 'k':
                        printf("Ingrese los kms: ");
                        scanf("%d", &autoArch.kms);
                break;
                case 'd':
                        printf("Ingrese el dni: ");
                        scanf("%d", &autoArch.dniTitular);
                break;
                case 'v':
                        printf("Ingrese el nuevo precio: ");
                        scanf("%f", &autoArch.precioDeAdquisicion);
                break;
                default:
                        printf("Error \n");
            }
            printf("Desea continuar? (s/n): ");
            fflush(stdin);
            scanf("%c", &seguir);
        }
        fseek(archivo, (pos-1)*sizeof(AutoArchivo), SEEK_SET);
        fwrite(&autoArch, sizeof(AutoArchivo),1,archivo);
        fclose(archivo);
    }
        else
        {
            printf("error a  ");
        }
}
void modificarPersona(int pos)
{

   FILE *archivo = fopen("personas.bin", "r+b");
   Persona persona;
    char i;
    char seguir = 's';

    if(archivo!=NULL)
    {
        fseek(archivo, (pos-1)*sizeof(Persona), SEEK_SET);
        fread(&persona, sizeof(Persona), 1, archivo);

        while (seguir == 's')
        {
            printf("Que dato desea modificar? n(nombre)/d(direccion)/x(dni)/t(telefono)/r(rol): ");
            fflush(stdin);
            scanf("%c", &i);

            switch(i)
            {
                case 'n':
                        printf("Ingrese nuevo nombre y apellido: ");
                        scanf(" %39[^\n]", persona.nombre);

                break;
                case 'd':
                        printf("Ingrese una nueva direccion: "),
                        scanf(" %29[^\n]", persona.direccion);
                break;
                case 'x':
                        printf("Ingrese un nuevo dni: ");
                        fflush(stdin);
                        scanf("%d", &persona.dni);
                break;
                case 't':
                        printf("Ingrese nuevo telefono: ");
                        scanf("%d", &persona.telefono);
                break;
                case 'r':
                        printf("Ingrese un nuevo rol(c/v): ");
                        scanf(" %10s", persona.rol);
                        while(strcmp(persona.rol,"comprador")!=0 && strcmp(persona.rol,"vendedor")!=0)
                        {
                        printf("Ingrese un caracter valido(c/v): ");
                        fflush(stdin);
                        scanf("%s", persona.rol);
                        }
                break;
                default:
                        printf("Error \n");
            }
            printf("Desea continuar? (s/n): ");
            fflush(stdin);
            scanf("%c", &seguir);
        }
        fseek(archivo, (pos-1)*sizeof(Persona), SEEK_SET);
        fwrite(&persona, sizeof(Persona),1,archivo);
        fclose(archivo);
    }
        else
        {
            printf("error a  ");
        }
}

void infoPersona (int dni)
{
    FILE* archi = fopen("personas.bin", "rb");

    Persona persona;

    if(archi != NULL)
    {
        while(fread(&persona, sizeof(Persona), 1, archi)>0)
        {
            if(dni == persona.dni)
            {
                printf("-------------\n");
                printf("Dni:    \t%d\n", persona.dni);
                printf("Nombre:      \t%s\n", persona.nombre);
                printf("Direccion:  \t%s\n", persona.direccion);
                printf("Telefono: \t%d\n", persona.telefono);
                printf("Rol:     \t%s\n", persona.rol);
            }
        }
    fclose(archi);
    }else
    {
        printf("ERROR: No se pudo abrir el  archivo");
    }

}


void infoAuto (char letras[],int num)
{
    FILE* archi = fopen("autosArch.bin", "rb");

    AutoArchivo autoArch;

    int encontro=0;

    if(archi != NULL)
    {

        printf("p:%s-\n",letras);


        printf("n:%d",num);

        while(fread(&autoArch, sizeof(AutoArchivo), 1, archi)>0)
        {
            if(strcmp(letras, autoArch.patente.letras)==0 && autoArch.patente.numeros==num)
                {
                    encontro=1;
                    printf("-------------\n");
                    printf("Patente:            %s-%d\n", autoArch.patente.letras, autoArch.patente.numeros);
                    printf("Marca:              %s\n", autoArch.marca);
                    printf("Modelo:             %s\n", autoArch.modelo);
                    printf("Kms:                %d\n", autoArch.kms);
                    printf("DniTitular:         %d\n", autoArch.dniTitular);
                    printf("PrecioAdquisicion:  %.2f\n", autoArch.precioDeAdquisicion);
                    printf("Anio:               %d\n", autoArch.anio);
                }

        }
        if(encontro==0)
                {

                    printf("\nNo se encontro el auto");
                }

     fclose(archi);
    }else
    {
        printf("ERROR: No se pudo abrir el archivo");
    }
}

void verVentas ()
{
    FILE* archi = fopen("ventas.bin", "rb");

    Venta ventas;

    if(archi != NULL)
    {
        printf("\n\tVENTAS:\n");
        while(fread(&ventas, sizeof(Venta), 1, archi)>0)
        {
            printf("\nFecha:   %d / %d / %d", ventas.fecha.dia, ventas.fecha.mes, ventas.fecha.anio);
            printf("\nPatente: %s-%d\n", ventas.autoAVender.letras, ventas.autoAVender.numeros);
        }

    fclose(archi);
    }else
    {
        printf("ERROR: No se pudo abrir el archivo");
    }
}

void infoVenta (int pos)
{
    FILE* archi = fopen("ventas.bin", "rb");
    Venta ventas;
    int aux;

    aux= ftell(archi)/sizeof(Venta);
    if(archi != NULL)
    {
        fseek(archi, sizeof(Venta)*pos, SEEK_SET);
        fread(&ventas, sizeof(Venta), 1, archi);
        if(pos <= aux)
        {
        printf("\nFecha:        %d/%d/%d", ventas.fecha.dia, ventas.fecha.mes, ventas.fecha.anio);
        printf("\nPatente:      %s-%d", ventas.autoAVender.letras, ventas.autoAVender.numeros);
        printf("\nDNI comprador:%d", ventas.dniComprador);
        printf("\nDNI vendedor: %d", ventas.dniVendedor);
        printf("\nPrecio Venta: %.2f", ventas.precioVenta);
        printf("\nGanancia:     %.2f\n", ventas.ganancia);

        }
        else
        {
            printf("esa posicion no existe\n");
        }
    fclose(archi);
    }else
    {
        printf("ERROR: No se pudo abrir el archivo");
    }
}

float recaudadoEnDeterminadoMes (int mes, int anio)
{
    FILE* archi = fopen("ventas.bin", "rb");

    Venta ventas;
    float suma=0;

    if(archi != NULL)
    {
       while(fread(&ventas, sizeof(Venta), 1, archi)>0)
       {
           if(ventas.fecha.mes == mes && ventas.fecha.anio == anio)
            {
                suma += ventas.ganancia;
            }
       }
    fclose(archi);
    }else
    {
        printf("ERROR: No se pudo abrir el archivo");
    }
    return suma;
}

float mayorGanancia ()
{
    FILE* archi = fopen("ventas.bin", "rb");

    Venta ventas;
    float mayor=0;

    if(archi != NULL)
    {
        while(fread(&ventas, sizeof(Venta), 1, archi)>0)
        {
            if(mayor < ventas.ganancia)
            {
                mayor = ventas.ganancia;
            }
        }
    fclose(archi);
    }else
    {
        printf("ERROR: No se pudo abrir el archivo");
    }
return mayor;
}

void Autos10anos() {
    AutoArchivo autos[100];
    FILE *archi = fopen("autosArch.bin", "rb");
    int conta = 0;

    if (archi != NULL) {
        AutoArchivo autoTemp;
        while (fread(&autoTemp, sizeof(AutoArchivo), 1, archi) > 0) {
            if (CURRENT_YEAR - autoTemp.anio < 10) {
                if (conta < 100) {
                    autos[conta] = autoTemp;
                    conta++;
                } else {
                    printf("Error: Se alcanzó el límite de almacenamiento de autos.\n");
                    break;
                }
            }
        }
        fclose(archi);


        for (int i = 0; i < conta - 1; i++) {
            for (int j = i + 1; j < conta; j++) {
                if (autos[i].anio < autos[j].anio) {
                    AutoArchivo temp = autos[i];
                    autos[i] = autos[j];
                    autos[j] = temp;
                }
            }
        }


        for (int k = 0; k < conta; k++) {
            printf("Patente:    %s-%d\n", autos[k].patente.letras, autos[k].patente.numeros);
            printf("Marca:      %s\n", autos[k].marca);
            printf("Modelo:     %s\n", autos[k].modelo);
            printf("Anio:       %d\n", autos[k].anio);
            printf("Kms:        %d\n", autos[k].kms);
            printf("DniTitular: %d\n", autos[k].dniTitular);
            printf("PrecioAdq:  %.2f\n\n", autos[k].precioDeAdquisicion);
        }
    } else {
        printf("Error: No se pudo abrir el archivo autosArch.bin.\n");
    }
}
