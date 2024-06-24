#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

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
	long long int telefono;
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
void modificarAuto(Auto**,int*);
void modificarPersona(int);
void infoPersona();
void infoAuto();
void verVentas();
void infoVenta();
void agregarAuto(Auto**,int*);
void recaudadoEnDeterminadoMes(int,int);
float mayorGanancia();
void Autos10anos();
int buscarAutoPorPatente(AutoArchivo*,char[],int,int*);
int buscarPersonaPorDNI(int,Persona*);
void cambiar_titular(int,int);
float precioAdquisicion(int);

int main(){
    iniciarPrograma();
    return 0;
}
void iniciarPrograma() {
    char usuario[LONGITUD + 1];
    char clave[LONGITUD + 1];
    int intento = 0;
    int ingresa = 0;
    char entrada[50];
    int opcion1, opcion2;

    while (1) {
        printf("\n\t\t-------------------------------------------------------\n");
        printf("\n\t\tSi desea registrarse ingrese 1, para logearse ingrese 2:\n ");
        printf("\n\t\tPara salir ingrese 3:\n");
        printf("\n\t\t-------------------------------------------------------\n");
        printf("\n\t\tOpcion: ");

        // Leer la entrada completa
        fgets(entrada, sizeof(entrada), stdin);

        // Parsear las opciones
        if (sscanf(entrada, "%d %d", &opcion1, &opcion2) != 1) {
            printf("\n\t\tOpcion incorrecta, ingrese una opcion valida.\n");
            continue; // Volver al inicio del bucle
        }


        switch (opcion1) {
            case 1:
                registrarse();
                break;
            case 2:
                intento = 0;
                while (!ingresa && intento < 3) {
                    ingresa = login(usuario, clave);
                    if (!ingresa) {
                        printf("\n\tUsuario y/o contraseña incorrectos");
                        intento++;
                    } else {
                        menu();
                        return;
                    }
                }
                break;
            case 3:
                printf("\n\tQue tenga un lindo día :D");
                return;
            default:
                printf("\n\tOpción incorrecta, ingrese una opción válida.\n");
                break;
        }


        if (opcion2 == 2 && opcion1 == 1) {
            while (!ingresa && intento < 3) {
                ingresa = login(usuario, clave);
                if (!ingresa) {
                    printf("\n\tUsuario y/o contraseña incorrectos");
                    intento++;
                } else {
                    menu();
                    return;
                }
            }
        } else if (opcion2 == 3 && opcion1 == 1) {
            printf("\n\tQue tenga un lindo día :D");
            return;
        } else if (opcion2 != 0 && opcion2 != 2 && opcion2 != 3) {
            printf("\n\tOpción incorrecta, ingrese una opción válida.\n");
        }
    }
}
void menu(){

    char c='s';
    int a,dni;
    Auto* autos;
    autos = (Auto*) malloc (1 * sizeof(Auto));
    int count = 0;

    int posAuto = 0;
    int posPersona = 0;
    int posVenta = 0;

    char patenteLetras[4];
    int patenteNumeros = 0;

    int dniPersona=0;

    int mes=0;
    int anio=0;
    int hayAutos;

    long long int tempDNI;

    system("cls");
    while(c=='s')
    {
        printf("\n\tingrese que desea hacer:\n");
        printf("\t____________________________\n");
        printf("\tAgregar un auto: \t(1) |\n");
        printf("\tVer lista de autos: \t(2) |\n");
        printf("\tModificar un auto: \t(3) |\n");
        printf("\tVer info de un auto: \t(4) |\n");
        printf("\tAgregar una persona: \t(5) |\n");
        printf("\tModificar una persona:\t(6) |\n");
        printf("\tver lista de personas:\t(7) |\n");
        printf("\tver info de persona:  \t(8) |\n");
        printf("\tver autos en venta:  \t(9) |\n"); //con dni hardcodeado de consecionaria
        printf("\tVer ventas:\t\t(10)|\n");
        printf("\tver info de una venta:\t(11)|\n");
        printf("\tVender un auto:\t\t(12)|\n");         //listo
        printf("\tRecaudado en un mes\t(13)|\n");
        printf("\tVer antiguedad de auto:\t(14)|\n");
        printf("\tVer la mayor ganancia:\t(15)|\n");
        printf("\tSi desea salir:\t\t(16)|\n");
        printf("\t____________________________|\n\n");
        printf("\tOpcion:");
        scanf("%d",&a);
        switch(a)
        {
            case 1:
                agregarAuto(&autos, &count);
                agregarAutoArchivo(autos, count);           //listo
                mostrarAutoArchivo();
            break;
            case 2:
                mostrarAutoArchivo();                   //listo
            break;
            case 3:
                mostrarAutoArchivo();
                modificarAuto(&autos,&count);
            break;
            case 4:                                                   //listo
                mostrarAutoArchivo();
                printf("Ingrese las letras de la patente del auto que quiere ver: ");
                scanf("%s", &patenteLetras);
                fflush(stdin);

                while(strlen(patenteLetras)!=3)
                {
                    printf("Error: Ingrese letras validas a la patente: ");
                    scanf("%s", &patenteLetras);
                    fflush(stdin);
                }

                printf("Ingrese los numeros de la petente del auto que quiere ver: ");
                scanf("%d", &patenteNumeros);
                fflush(stdin);

                while(patenteNumeros > 999 || patenteNumeros <100 || patenteNumeros > INT_MAX || patenteNumeros < INT_MIN)
                {
                    printf("ERROR: Ingrese numeros de 3 digitos: ");
                    scanf("%d", &patenteNumeros);
                    fflush(stdin);
                }
                infoAuto(patenteLetras, patenteNumeros);
            break;
            case 5:                                     //listo
                agregarPersonas();
                mostrarPersonas();
            break;
            case 6:                                     // listo
                mostrarPersonas();
                printf("Ingrese el dni de la persona que desea modificar:");
                scanf("%lld",&tempDNI);
                while(tempDNI < 1000000 || tempDNI > 999999999 || tempDNI > INT_MAX || tempDNI < INT_MIN)
                {
                    printf("Error: dni invalido o fuera de rango\n");
                    printf("Ingrese un dni valido:");
                    scanf("%lld", &tempDNI);
                }
                dni = (int)tempDNI;
                modificarPersona(dni);
            break;
            case 7:
                mostrarPersonas();                       //listo
            break;
            case 8:                                        //listo

                mostrarPersonas();
                printf("Ingrese dni de la persona que quiera ver: ");
                scanf("%lld", &tempDNI);
                fflush(stdin);
                while(tempDNI < 1000000 || tempDNI > 999999999 || tempDNI > INT_MAX || tempDNI < INT_MIN)
                {
                    printf("ERROR: Dni invalido o fuera de rango\n");
                    printf("Ingrese un dni valido: ");
                    scanf("%d", &dniPersona);
                }
                dniPersona=(int)tempDNI;
                infoPersona(dniPersona);
            break;
            case 9:                                       //listo
                verAutosEnVenta(&hayAutos);
                if(hayAutos!=1)
                {
                    printf("No hay stock\n");
                }
            break;
            case 10:                                     //listo
                verVentas();

            break;
            case 11:                                    //listo
                verVentas();
                infoVenta();
            break;
            case 12:                                    //listo
                agregarVentas();
            break;
            case 13:                                    //listo
                verVentas();
                printf("ingrese mes:");
                scanf("%d",&mes);

                while(mes < 1 || mes > 12 || mes>INT_MAX || mes<INT_MIN)
                {
                    printf("ERROR:  mes no valido o fuera de rango\n");
                    printf("Ingrese un mes valido:");
                    scanf("%d", &mes);
                    fflush(stdin);
                }
                printf("ingrese anio:");
                scanf("%d",&anio);
                fflush(stdin);
                while(anio < 1990 || anio > 2024 || anio>INT_MAX || anio<INT_MIN)
                {
                    printf("ERROR: anio no valido o fuera de rango\n");
                    printf("Ingrese un anio valido:");
                    scanf("%d", &anio);
                    fflush(stdin);
                }
                recaudadoEnDeterminadoMes(mes,anio);
            break;
            case 14:                                    //listo
                Autos10anos();
            break;
            case 15:                                        //listo
                    printf("La mayor ganancia fue de %.2f pesos",mayorGanancia());
            break;
		  case 16:                                          //listo
            printf("\n\tHasta pronto");
            return;

            default:
		    printf("\n\tIngrese una opcion valida o presione n para salir");

            break;
        }
        printf("\nDesea continuar en el menu?(s/n):");
        fflush(stdin);
        scanf("%c",&c);
        system("cls");
    }

}
int usuario_existe(const char* usuario) {
    FILE *archivo = fopen("cuentas.bin", "rb");
    if (archivo == NULL) {
        return 0;
    }

    char usuario_existente[LONGITUD + 1];
    char clave[LONGITUD + 1];

    while (fread(usuario_existente, sizeof(char), LONGITUD + 1, archivo) == LONGITUD + 1) {
        fread(clave, sizeof(char), LONGITUD + 1, archivo); // leer la clave correspondiente
        if (strcmp(usuario_existente, usuario) == 0) {
            fclose(archivo);
            return 1;
        }
    }

    fclose(archivo);
    return 0;
}
void registrarse() {
    char usuario[LONGITUD + 1];
    char clave[LONGITUD + 1];

    while (1) {
        printf("\n\t\t\tREGISTRO\n");
        printf("\n\t\t\t--------\n");
        printf("\n\tIngrese un nombre de usuario (max %d caracteres): ", LONGITUD);
        fgets(usuario, LONGITUD + 1, stdin);
        usuario[strcspn(usuario, "\n")] = '\0';

        if (strlen(usuario) == LONGITUD) {
            printf("\n\tNombre de usuario demasiado largo. Intente de nuevo.\n");
            while (getchar() != '\n');
            continue;
        }

        if (usuario_existe(usuario)) {
            printf("\n\tEl nombre de usuario ya está en uso. Por favor, elija otro.\n");
            continue; // Vuelve a intentar registrarse
        }

        printf("\n\tIngrese una contrasena (max %d caracteres): ", LONGITUD);
        fgets(clave, LONGITUD + 1, stdin);
        clave[strcspn(clave, "\n")] = '\0';

        if (strlen(clave) == LONGITUD) {
            printf("\n\tContrasena demasiado larga. Intente de nuevo.\n");
            while (getchar() != '\n');
            continue;
        }

        FILE *archivo = fopen("cuentas.bin", "ab");
        if (archivo == NULL) {
            printf("Error al abrir el archivo");
            return;
        }

        fwrite(usuario, sizeof(char), LONGITUD + 1, archivo);
        fwrite(clave, sizeof(char), LONGITUD + 1, archivo);
        printf("\n\t\t---------------------------------");
        printf("\n\t\tUsuario registrado correctamente");
        printf("\n\t\t---------------------------------");

        fclose(archivo);
        break;
    }
}
int login(char *usuario, char *clave) {
    int flag = 0;
    FILE* archi = fopen("cuentas.bin", "rb");
    char archivoUsuario[LONGITUD + 1];
    char archivoClave[LONGITUD + 1];
    if (archi == NULL)
    {
        printf("Error al abrir el archivo\n");
        flag = 1;
    }

    int i = 0;

    printf ("\n\t\t\t\tINICIO DE SESION\n");
    printf ("\t\t\t\t----------------\n");
    printf("\n\tUSUARIO: ");
    fgets(usuario, LONGITUD + 1, stdin);
    usuario[strcspn(usuario, "\n")] = '\0';
    printf("\n\tCLAVE: ");

    while (1) {
        char caracter = getch();
        if (caracter == 13) {  // Enter
            clave[i] = '\0';
            break;
        } else if (caracter == 8) {  // Backspace
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else {
            if (i < LONGITUD) {
                printf("*");
                clave[i] = caracter;
                i++;
            }
        }
    }

    int autenticado = 0;
    while (fread(archivoUsuario, sizeof(char), LONGITUD + 1, archi) &&
           fread(archivoClave, sizeof(char), LONGITUD + 1, archi)) {
        if (strcmp(usuario, archivoUsuario) == 0 && strcmp(clave, archivoClave) == 0) {
            autenticado = 1;
            break;
        }
    }
    fclose(archi);
    return autenticado;
}
void verAutosEnVenta(int *flag){
    AutoArchivo autoArch;
    FILE * archi = fopen("autosArch.bin","rb");

    if(archi!=NULL)
    {
        *flag=0;
        while(fread(&autoArch,sizeof(AutoArchivo),1,archi))
        {
            if(autoArch.dniTitular==consecionariaDNI)
            {
                printf("-------------\n");
                printf("Patente:    %s-%d\n", autoArch.patente.letras, autoArch.patente.numeros);
                printf("Marca:      %s\n", autoArch.marca);
                printf("Modelo:     %s\n", autoArch.modelo);
                *flag=1;
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
int buscarAutoPorPatente(AutoArchivo* autito,char letrasPatente[4],int numeroPatente,int *pos) {
    int flag = 0;
    AutoArchivo tempAuto;
    FILE* archivo = fopen("autosArch.bin", "r+b");
    if (archivo != NULL) {
            *pos=0;
        while (fread(&tempAuto, sizeof(AutoArchivo), 1, archivo) > 0) {
            (*pos)++;
            if (strcmp(tempAuto.patente.letras,letrasPatente)==0 && tempAuto.patente.numeros==numeroPatente && tempAuto.dniTitular==consecionariaDNI) {
                *autito = tempAuto;
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
void cambiar_titular(int pos, int dni) {
    FILE *archivo = fopen("autosArch.bin", "r+b");
   AutoArchivo autoArch;

    if(archivo!=NULL)
    {
        fseek(archivo, (pos-1)*sizeof(AutoArchivo), SEEK_SET);
        fread(&autoArch, sizeof(AutoArchivo), 1, archivo);


                autoArch.dniTitular = dni;

        fseek(archivo, (pos-1)*sizeof(AutoArchivo), SEEK_SET);
        fwrite(&autoArch, sizeof(AutoArchivo),1,archivo);
        fclose(archivo);
    }
        else
        {
            printf("Error: No se pudo abrir el archivo.\n");
        }
}
void agregarAuto(Auto** autos, int* count) {
    Auto autito;
    Persona titular;
    char seguir = 's';

    while (seguir == 's' || seguir == 'S') {
       printf("Ingrese las letras de la patente: ");
        scanf("%s", autito.patente.letras);
        while(strlen(autito.patente.letras)!=3)
        {
            printf("Error: Ingrese letras validas a la patente: ");
            fflush(stdin);
            scanf("%s", &autito.patente.letras);
        }

        printf("Ingrese los numeros de la patente: ");
        scanf("%d", &autito.patente.numeros);
        while(autito.patente.numeros < 100 || autito.patente.numeros > 999 || autito.patente.numeros > INT_MAX || autito.patente.numeros < INT_MIN)
        {
            printf("Error: ingrese numeros validos para la patente: ");
            scanf("%d", &autito.patente.numeros);
        }

        printf("Ingrese la marca del auto: ");
        scanf("%s", autito.marca);
        while(strlen(autito.marca)<4)
        {
            printf("Error: Ingrese una marca valida: ");
            fflush(stdin);
            scanf("%s", &autito.marca);
        }

        printf("Ingrese el modelo del auto: ");
        scanf("%s", &autito.modelo);
        fflush(stdin);
        while(strlen(autito.modelo)<=3)
        {
            printf("Error: Ingrese un modelo valido: ");
            scanf("%s", &autito.modelo);
            fflush(stdin);
        }

        printf("Ingrese el anio del auto: ");
        scanf("%d", &autito.anio);
        fflush(stdin);

        while(autito.anio < 1900 || autito.anio > 2024 || autito.anio > INT_MAX || autito.anio < INT_MIN)
        {
            printf("Error: Ingrese un anio valido para el auto: ");
            scanf("%d", &autito.anio);
            fflush(stdin);
        }

        printf("Ingrese el kilometraje del auto: ");
        scanf("%d", &autito.kms);
        fflush(stdin);

        while(autito.kms < 0 || autito.kms > INT_MAX || autito.kms < INT_MIN)
        {
            printf("Error: Ingrese un kilometraje valido para el auto: ");
            scanf("%d", &autito.kms);
            fflush(stdin);
        }

        printf("Ingrese DNI del titular del auto: ");
        scanf("%d", &autito.Titular.dni);
        fflush(stdin);
        while(autito.Titular.dni < 1000000 || autito.Titular.dni> 999999999 || autito.Titular.dni > INT_MAX || autito.Titular.dni < INT_MIN)
        {
            printf("Error: Ingresa un dni valido (mayor a 1 millon): ");
            scanf("%d", &autito.Titular.dni);
            fflush(stdin);
        }


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
            fflush(stdin);
            while(autito.precioDeAdquisicion < 0)
            {
                printf("Error: Ingrese un precio de adquisicion valido: ");
                scanf("%f", &autito.precioDeAdquisicion);
                fflush(stdin);
            }


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
        printf("Desea agregar mas autos? (s/n): ");
        scanf("%c", &seguir);
        fflush(stdin);
        system("cls");
    }
}
void agregarAutoArchivo(Auto* autos, int count) {
    AutoArchivo autoArch;
    FILE* archivo = fopen("autosArch.bin", "ab");
    if (archivo != NULL) {
        strncpy(autoArch.patente.letras, autos[count - 1].patente.letras, sizeof(autoArch.patente.letras));
        autoArch.patente.numeros = autos[count - 1].patente.numeros;
        strncpy(autoArch.marca, autos[count - 1].marca, sizeof(autoArch.marca));
        strncpy(autoArch.modelo, autos[count - 1].modelo, sizeof(autoArch.modelo));
        autoArch.anio = autos[count - 1].anio;
        autoArch.kms = autos[count - 1].kms;
        autoArch.dniTitular = autos[count - 1].Titular.dni;
        autoArch.precioDeAdquisicion = autos[count - 1].precioDeAdquisicion;

        fwrite(&autoArch, sizeof(AutoArchivo), 1, archivo);
        fclose(archivo);
    } else {
        printf("error no se pudo abrir el catalogo\n");
    }
}
void agregarPersonas(){
    Persona p;
    long long int tempDNI;
    char c='s';
    FILE* archivo = fopen("personas.bin","ab");
    if (archivo != NULL) {
        while (c == 's' || c == 'S') {
            printf("Ingrese el DNI: ");
            scanf("%lld", &tempDNI);
            while (getchar() != '\n');

             while(tempDNI < 1000000 || tempDNI > 999999999 || tempDNI>INT_MAX || tempDNI<INT_MIN)
            {
                printf("\nERROR Dni invalido o fuera de rango \n");
                printf("\nIngrese un dni valido: ");
                scanf("%lld", &tempDNI);
                printf("\n");
                fflush(stdin);
            }
            p.dni = (int)tempDNI;

            printf("Ingrese el nombre y apellido: ");
            scanf(" %39[^\n]", p.nombre);
            fflush(stdin);

            while(strlen(p.nombre)>39)
                {
                    printf("Error: Ingrese un nombre no tan largo: ");
                    scanf(" %39[^\n]", p.nombre);
                    fflush(stdin);
                }

            printf("Ingrese el telefono: ");
            scanf("%lld", &p.telefono);
            while(p.telefono < 1000000 || p.telefono > 9999999999)
            {
                printf("Error: Ingrese un telefono valido: ");
                scanf("%lld", &p.telefono);
                fflush(stdin);
            }

            printf("Ingrese la direccion de la persona(con numeros): ");
            scanf(" %49[^\n]", p.direccion);
            fflush(stdin);

            while(strlen(p.direccion)>49)
                {
                    printf("Error: Direccion muy larga o fuera de rango: ");
                    scanf(" %49[^\n]", &p.direccion);
                    fflush(stdin);
                }

            strcpy(p.rol,"comprador");

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
void mostrarAutoArchivo(){
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
        printf("Error no se pudo abrir el archivo");
    }
}
void mostrarPersonas(){
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
        printf("\n");
        fclose(archivo);
    } else
    {
        printf("error");
    }
}
void agregarVentas(){
    Venta v;
    Persona p;
    AutoArchivo autito;
    char c='s';
    char c2='s';
    int pos,hayAutos;
    long long int tempDNI;
    FILE* archivo = fopen("ventas.bin","ab");
    if(archivo!=NULL)
    {
        while(c=='s')
        {
            system("cls");
            mostrarPersonas();
            printf("-------------\n");
            printf("\ningrese el dni del comprador: ");
            scanf("%lld",&tempDNI);
            fflush(stdin);

            while(tempDNI < 1000000 || tempDNI > 999999999 || tempDNI > INT_MAX || tempDNI < INT_MIN)
            {
                printf("\nERROR Dni invalido o fuera de rango \n");
                printf("\ningrese un dni valido: ");
                scanf("%lld", &tempDNI);
                printf("\n");
                fflush(stdin);
            }
            v.dniComprador = (int)tempDNI;

            if (buscarPersonaPorDNI(v.dniComprador, &p) && v.dniComprador != consecionariaDNI)
            {

                system("cls");
                verAutosEnVenta(&hayAutos);
                if(hayAutos==1)
                {
                    printf("-------------\n");

                    printf("Ingrese las letras de la patente del auto a vender: ");
                    scanf("%s", v.autoAVender.letras);
                    fflush(stdin);

                    while(strlen(v.autoAVender.letras)!=3)
                    {
                        printf("Error: Ingrese letras validas a la patente: ");
                        scanf("%s", &v.autoAVender.letras);
                        fflush(stdin);
                    }

                    printf("Ingrese los numeros de la patente del auto a vender: ");
                    scanf("%d", &v.autoAVender.numeros);
                    fflush(stdin);

                    while(v.autoAVender.numeros < 100 || v.autoAVender.numeros > 999 || v.autoAVender.numeros > INT_MAX || v.autoAVender.numeros < INT_MIN)
                    {
                        printf("Error: ingrese numeros validos para la patente: ");
                        scanf("%d", &v.autoAVender.numeros);
                        fflush(stdin);
                    }
                    pos = 0;

                    while(!buscarAutoPorPatente(&autito,v.autoAVender.letras,v.autoAVender.numeros,&pos)) // verificar que exista y que no este vendido ese auto
                    {
                        printf("Error: La patente ingresada no se encontro en el sistema\n");
                        printf("Desea intentar con otra pantente?(s/n): ");
                        scanf(" %c",&c2);
                        fflush(stdin);
                        if(c2 != 's' && c2 != 'S')
                        {
                            break;
                        }
                        else
                        {
                            printf("Ingrese las letras de la patente del auto a vender: ");
                            scanf("%s", v.autoAVender.letras);
                            fflush(stdin);

                            while(strlen(v.autoAVender.letras)!=3)
                            {
                                printf("Error: Ingrese letras validas a la patente: ");
                                scanf("%s", &v.autoAVender.letras);
                                fflush(stdin);
                            }

                            printf("Ingrese los numeros de la patente del auto a vender: ");
                            scanf("%d", &v.autoAVender.numeros);
                            fflush(stdin);

                            while(v.autoAVender.numeros < 100 || v.autoAVender.numeros > 999)
                            {
                                printf("Error: ingrese numeros validos para la patente: ");
                                scanf("%d", &v.autoAVender.numeros);
                                fflush(stdin);
                            }

                            pos=0;
                        }
                    }
                    if(c2=='s' || c2=='S')
                    {
                        cambiar_titular(pos,v.dniComprador);
                        printf("ingrese dia, mes y anio de la venta: \n");
                        printf("Dia:");
                        scanf("%d",&v.fecha.dia);
                        fflush(stdin);
                        while(v.fecha.dia > 31 || v.fecha.dia < 1)
                        {
                            printf("Error: ingrese un dia valido\n");
                            printf("Dia:");
                            scanf("%d",&v.fecha.dia);
                            fflush(stdin);
                        }
                        printf("Mes:");
                        scanf("%d",&v.fecha.mes);
                        fflush(stdin);
                        while(v.fecha.mes > 12 || v.fecha.mes < 1)
                        {
                            printf("Error: ingrese un mes valido\n");
                            printf("Mes:");
                            scanf("%d",&v.fecha.mes);
                            fflush(stdin);
                        }
                        printf("Anio:");
                        scanf("%d",&v.fecha.anio);
                        fflush(stdin);
                        while(v.fecha.anio > 2024 || v.fecha.anio<1990)
                        {
                            printf("Error: ingrese un anio no mayor a 2024 ni menor a 1990\n");
                            printf("Anio:");
                            scanf("%d",&v.fecha.anio);
                            fflush(stdin);
                        }


                        printf("ingrese el precio de la venta: ");
                        scanf("%f",&v.precioVenta);
                        fflush(stdin);

                        v.ganancia = v.precioVenta-precioAdquisicion(pos);

                        if(v.ganancia<0)
                        {
                            v.ganancia=0;
                        }

                        v.dniVendedor=consecionariaDNI;

                        fwrite(&v,sizeof(Venta),1,archivo);

                    }
                }
                else
                {
                     printf("No hay autos en stock\n");
                }
            }
        else
            {
                printf("ERROR: El titular con DNI %d no existe\n", v.dniComprador);
            }

            printf("\nDesea continuar en la funcion vender?(s/n)\n");
            scanf(" %c",&c);
            fflush(stdin);
            system("cls");
        }

        fclose(archivo);
    }
    else
    {
        printf("error no se pudo abrir el catalogo");
    }
}
float precioAdquisicion(int pos){
    AutoArchivo autito;
    float pAdquisicion;
    FILE * archivo = fopen("autosArch.bin","rb");

    if(archivo!=NULL)
    {
         fseek(archivo, (pos-1)*sizeof(AutoArchivo), SEEK_SET);
        fread(&autito, sizeof(AutoArchivo), 1, archivo);


                pAdquisicion = autito.precioDeAdquisicion;

        fclose(archivo);
    }
    else
    {
        printf("Error: No se pudo abrir el archivo");
    }
    return pAdquisicion;
}
void mostrarVentas(){
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
        printf("\n");
        fclose(archivo);
    } else
    {
        printf("error");
    }
}
void modificarAuto(Auto** autos,int* count){
  AutoArchivo autoArch;
    FILE *archivo = fopen("autosArch.bin", "r+b");
    Patente patente;
    char opcion;
    int encontrado = 0;

    if (archivo != NULL) {
        printf("Ingrese las letras de la patente: ");
        scanf("%s", patente.letras);
        fflush(stdin);
        while (strlen(patente.letras) != 3) {
            printf("Error: Ingrese letras validas a la patente: ");
            scanf("%s", patente.letras);
            fflush(stdin);
        }

        printf("Ingrese los numeros de la patente: ");
        scanf("%d", &patente.numeros);
        fflush(stdin);
        while (patente.numeros < 100 || patente.numeros > 999) {
            printf("Error: ingrese numeros validos para la patente: ");
            scanf("%d", &patente.numeros);
            fflush(stdin);
        }

        while (fread(&autoArch, sizeof(AutoArchivo), 1, archivo) > 0) {
            if (strcmp(autoArch.patente.letras, patente.letras) == 0 && autoArch.patente.numeros == patente.numeros) {
                encontrado = 1;
                break;
            }
        }

        if (encontrado) {
            fseek(archivo, -sizeof(AutoArchivo), SEEK_CUR);

            do {
                printf("Que dato desea modificar? (p(patente)/m(marca)/x(modelo)/a(anio)/k(kms)/d(dni)/v(precio)): ");
                fflush(stdin);
                scanf("%c", &opcion);

                switch (opcion) {
                    case 'p':
                        printf("Ingrese las nuevas letras de la patente: ");
                        scanf("%s", autoArch.patente.letras);
                        fflush(stdin);
                        while (strlen(autoArch.patente.letras) != 3) {
                            printf("Error: Ingrese letras validas a la patente: ");
                            scanf("%s", autoArch.patente.letras);
                            fflush(stdin);
                        }

                        printf("Ingrese los nuevos numeros de la patente: ");
                        scanf("%d", &autoArch.patente.numeros);
                        fflush(stdin);
                        while (autoArch.patente.numeros < 100 || autoArch.patente.numeros > 999) {
                            printf("Error: ingrese numeros validos para la patente: ");
                            scanf("%d", &autoArch.patente.numeros);
                            fflush(stdin);
                        }
                        break;
                    case 'm':
                        printf("Ingrese la nueva marca del auto: ");
                        scanf("%s", autoArch.marca);
                        fflush(stdin);
                        break;
                    case 'x':
                        printf("Ingrese el nuevo modelo del auto: ");
                        scanf("%s", autoArch.modelo);
                        fflush(stdin);
                        break;
                    case 'a':
                        printf("Ingrese el nuevo anio del auto: ");
                        scanf("%d", &autoArch.anio);
                        fflush(stdin);
                        while (autoArch.anio < 1900 || autoArch.anio > 2024) {
                            printf("Error: Ingrese un anio valido para el auto: ");
                            scanf("%d", &autoArch.anio);
                            fflush(stdin);
                        }
                        break;
                    case 'k':
                        printf("Ingrese el nuevo kilometraje del auto: ");
                        scanf("%d", &autoArch.kms);
                        fflush(stdin);
                        break;
                    case 'd':
                        mostrarPersonas();
                        printf("Ingrese DNI del nuevo titular del auto: ");
                        scanf("%d", &autoArch.dniTitular);
                        fflush(stdin);
                        break;
                    case 'v':
                        printf("Ingrese el nuevo precio de adquisicion del auto: ");
                        scanf("%f", &autoArch.precioDeAdquisicion);
                        fflush(stdin);
                        break;
                    default:
                        printf("Error: Debe ingresar una de las opciones\n");
                }

                printf("Desea seguir modificando? (s/n): ");
                fflush(stdin);
                scanf("%c", &opcion);
            } while (opcion == 's' || opcion == 'S');

            fwrite(&autoArch, sizeof(AutoArchivo), 1, archivo);
        } else {
            printf("\nERROR: No se encontro el auto con esa patente\n");
        }

        fclose(archivo);
    } else {
        printf("Error al abrir el archivo\n");
    }
}
void modificarPersona(int dni){

   FILE *archivo = fopen("personas.bin", "r+b");
   Persona persona;
    char i;
    char seguir = 's';
    int encontrado=0;

    if(archivo!=NULL)
    {
        while( fread(&persona, sizeof(Persona), 1, archivo)>0)
        {
            if(persona.dni==dni)
            {
                encontrado=1;
                fseek(archivo, -sizeof(Persona), SEEK_CUR);
                break;
            }
        }
        if(encontrado)
        {
            while (seguir == 's' || seguir=='S')
            {
                printf("Que dato desea modificar? n(nombre)/d(direccion)/x(dni)/t(telefono)/r(rol): ");
                scanf(" %c", &i);
                fflush(stdin);

                switch(i)
                {
                    case 'n':
                            printf("Ingrese nuevo nombre y apellido: ");
                            scanf(" %39[^\n]", persona.nombre);
                            fflush(stdin);
                    break;
                    case 'd':
                            printf("Ingrese una nueva direccion: "),
                            scanf(" %29[^\n]", persona.direccion);
                            fflush(stdin);
                    break;
                    case 'x':
                            printf("Ingrese un nuevo dni: ");
                            scanf("%d", &persona.dni);
                            fflush(stdin);
                    break;
                    case 't':
                            printf("Ingrese nuevo telefono: ");
                            scanf("%lld", &persona.telefono);
                            fflush(stdin);
                    break;
                    case 'r':
                            printf("Ingrese un nuevo rol(c/v): ");
                            scanf(" %10s", persona.rol);
                            fflush(stdin);

                            while(strcmp(persona.rol,"comprador")!=0 && strcmp(persona.rol,"vendedor")!=0)
                            {
                            printf("Ingrese un caracter valido(c/v): ");
                            scanf("%s", persona.rol);
                            fflush(stdin);
                            }
                    break;
                    default:
                            printf("Error \n");
                }
                printf("Quiere modificar otro dato? (s/n): ");
                scanf("%c", &seguir);
                fflush(stdin);
            }
                fseek(archivo, -sizeof(Persona), SEEK_CUR);
                fwrite(&persona, sizeof(Persona),1,archivo);
        }
        else
        {
            printf("\nERROR: No se encontro la persona con DNI %d\n", dni);
        }
        fclose(archivo);
    }
    else
    {
        printf("ERROR: No se pudo abrir el archivo");
    }
}
void infoPersona (int dni){
    FILE* archi = fopen("personas.bin", "rb");

    Persona persona;
    int encontro=0;

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
                printf("Telefono: \t%lld\n", persona.telefono);
                printf("Rol:     \t%s\n", persona.rol);
                encontro=1;
            }
        }
    fclose(archi);
    if(encontro==0)
    {
        printf("\nNo se encontro a la persona\n");
    }
    }else
    {
        printf("ERROR: No se pudo abrir el  archivo");
    }

}
void infoAuto (char letras[],int num){

    FILE* archi = fopen("autosArch.bin", "rb");
    AutoArchivo autoArch;
    int encontro=0;
    if(archi != NULL)
    {
        while(fread(&autoArch, sizeof(AutoArchivo), 1, archi)>0)
        {
            if(strcmp(autoArch.patente.letras,letras)==0 && autoArch.patente.numeros==num)
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
void verVentas (){
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
    printf("\n");
    fclose(archi);
    }else
    {
        printf("ERROR: No se pudo abrir el archivo");
    }
}
void infoVenta (){
    FILE* archi = fopen("ventas.bin", "rb");
    Venta ventas;
    int seEncontro=0;
    char patLetras[4];
    int patNum;
    int dia,mes,anio;

    if(archi != NULL)
    {
        printf("ingrese dia, mes y anio de la venta: \n");
        printf("Dia:");
        scanf("%d",&dia);
        fflush(stdin);
        while(dia > 31 && dia < 1)
            {
                printf("Error: ingrese un dia valido");
                printf("Dia:");
                scanf("%d",&dia);
                fflush(stdin);
            }
        printf("Mes:");
        scanf("%d",&mes);
        fflush(stdin);
        while(mes > 12 && mes < 1)
            {
                printf("Error: ingrese un mes valido");
                printf("Mes:");
                scanf("%d",&mes);
                fflush(stdin);
            }
        printf("Anio:");
        scanf("%d",&anio);
        fflush(stdin);
        while(anio > 2024 && anio<1990)
            {
                printf("Error: ingrese un anio no mayor a 2024 ni menor a 1990");
                printf("Anio:");
                scanf("%d",&anio);
                fflush(stdin);
            }
            //patente
            printf("Ingrese las letras de la patente del auto que se vendio: ");
            scanf("%s", patLetras);
            fflush(stdin);

        while(strlen(patLetras)!=3)
            {
                printf("Error: Ingrese 3 letras de la patente: ");
                scanf("%s", &patLetras);
                fflush(stdin);
            }

            printf("Ingrese los numeros de la patente del auto que se vendio: ");
            scanf("%d", &patNum);
            fflush(stdin);

        while(patNum < 100 || patNum > 999 || patNum > INT_MAX || patNum < INT_MIN)
            {
                printf("Error: Numero de la patente invalida o fuera de rango\n");
                printf("Ingrese numeros validos para la patente: ");
                scanf("%d", &patNum);
                fflush(stdin);
            }


        while(fread(&ventas, sizeof(Venta), 1, archi)>0)
        {
            if(ventas.fecha.dia==dia && ventas.fecha.mes==mes && ventas.fecha.anio==anio && strcmp(ventas.autoAVender.letras,patLetras)==0 && ventas.autoAVender.numeros==patNum)
            {
            printf("\nFecha:        %d/%d/%d", ventas.fecha.dia, ventas.fecha.mes, ventas.fecha.anio);
            printf("\nPatente:      %s-%d", ventas.autoAVender.letras, ventas.autoAVender.numeros);
            printf("\nDNI comprador:%d", ventas.dniComprador);
            printf("\nDNI vendedor: %d", ventas.dniVendedor);
            printf("\nPrecio Venta: %.2f", ventas.precioVenta);
            printf("\nGanancia:     %.2f\n", ventas.ganancia);
            seEncontro=1;
            }
        }
        if(seEncontro==0)
        {
            printf("No se encontro una venta con esas caracteristicas\n");
        }
    fclose(archi);
    }else
    {
        printf("ERROR: No se pudo abrir el archivo");
    }
}
void recaudadoEnDeterminadoMes (int mes, int anio){
    FILE* archi = fopen("ventas.bin", "rb");
    Venta ventas;
    float suma=0;
    int encontro=0;

    if(archi != NULL)
    {
       while(fread(&ventas, sizeof(Venta), 1, archi)>0)
       {
           if(ventas.fecha.mes == mes && ventas.fecha.anio == anio)
            {
                suma += ventas.ganancia;
                encontro=1;
            }
       }
       if(encontro==1)
       {
           printf("Lo recaudado en el mes %d del anio %d fue %.2f \n",mes,anio, suma);
       }
       else
       {
           printf("No se encontraron ventas en esa fecha\n");
       }
    fclose(archi);
    }else
    {
        printf("ERROR: No se pudo abrir el archivo");
    }
}
float mayorGanancia (){
    FILE* archi = fopen("ventas.bin", "rb");

    Venta ventas;
    float mayor=0;

    if(archi != NULL)
    {
        while(fread(&ventas, sizeof(Venta), 1, archi)>0)
        {
            if(ventas.ganancia > mayor)
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
            if (CURRENT_YEAR - autoTemp.anio <= 10) {
                if (conta < 100) {
                    autos[conta].dniTitular = autoTemp.dniTitular;
                    autos[conta].anio = autoTemp.anio;
                    autos[conta].kms = autoTemp.kms;
                    autos[conta].precioDeAdquisicion = autoTemp.precioDeAdquisicion;
                    strcpy(autos[conta].marca,autoTemp.marca);
                    strcpy(autos[conta].modelo,autoTemp.modelo);
                    strcpy(autos[conta].patente.letras,autoTemp.patente.letras);
                    autos[conta].patente.numeros = autoTemp.patente.numeros;
                    conta++;
                } else {
                    printf("Error: Se alcanzó el límite de almacenamiento de autos.\n");
                    break;
                }
            }
            printf("Anios de autos %d\n",autoTemp.anio);
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
