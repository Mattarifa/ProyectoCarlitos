#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define LONGITUD 20

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
	char apellido[40];
	int telefono;
	char direccion[30];
	char rol[10]; //comprador o vendedor

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

int main()
{

    char usuario[LONGITUD + 1];
    char clave[LONGITUD + 1];
    int intento =0;
    int ingresa = 0;

    //login(usuario, clave, &intento, &ingresa);
    //registrarse();
    menu();



    return 0;
}
void menu()
{
    char c='s';
    int a;
    while(c=='s')
    {
        printf("ingrese que desea hacer:");
        scanf("%d",&a);
        switch(a)
        {
            case 1:
                //modificarAuto(1);
                agregarAutoArchivo();
                mostrarAutoArchivo();
            break;
            case 2:
                //agregarPersonas();
                //modificarPersona(0);
                mostrarPersonas();
            break;
            case 3:
                    infoPersona();
            break;
            case 4:
                mostrarAutoArchivo();
                    infoAuto();
            break;
            case 5:
                agregarVentas();
                verVentas();
            break;
            case 6:
                infoVenta(0);
            break;
            case 7:
                agregarAuto();
            break;
            default:

            break;
        }
        printf("desea continuar?(s/n):");
        fflush(stdin);
        scanf("%c",&c);
    }
}
void registrarse()
{
    FILE *archivos= fopen("personas.bin","ab");
    if(archivos==NULL)
    {

    }
    else
    {
        printf("error");
    }
}

void login(char *usuario, char *clave, int *intento, int *ingresa, char caracter)
{
    int i=0;
    do{
        printf ("\n\t\t\tINICIO DE SESION\n");
        printf ("\t\t\t----------------\n");
        printf("\n\tUSUARIO: ");
        gets(usuario);
        printf("\tCLAVE: ");
        while (caracter = getch()){
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

    if(strcmp(usuario,"c")== 0 && strcmp(clave,"carlitos")== 0){
        *ingresa =1;
        printf ("\n\t\tBIENVENIDO A INMOBILIARIA CURSED\n");
        printf ("\t\t----------------------------------\n");

    }else{
        printf ("\n\t\tUSUARIO Y/O CONTRASENIA INCORRECTOS\n");
        (*intento)++;

    }
    }while (*intento <3 && *ingresa == 0);
}

void agregarAutoArchivo()
{
    AutoArchivo autoArch;
    char c='s';
    FILE* archivo = fopen("autosArch.bin","ab");
    if(archivo!=NULL)
    {
        while(c=='s')
        {
            printf("ingrese las letras de la patente: ");
            scanf("%s",&autoArch.patente.letras);
            printf("ingrese los numeros de la patente: ");
            scanf("%d",&autoArch.patente.numeros);

            printf("ingrese la marca del auto: ");
            scanf("%s",&autoArch.marca);

            printf("ingrese el modelo del auto: ");
            scanf("%s",&autoArch.modelo);

            printf("ingrese el anio del auto: ");
            scanf("%d",&autoArch.anio);

            printf("ingrese el kilometraje del auto: ");
            scanf("%d",&autoArch.kms);

            printf("ingrese el dni del titular del auto: ");
            scanf("%d",&autoArch.dniTitular);

            printf("ingrese el precio de adquisicion del auto: ");
            scanf("%f",&autoArch.precioDeAdquisicion);

            printf("desea continuar?(s/n): ");
            fflush(stdin);
            scanf("%c",&c);

            fwrite(&autoArch,sizeof(AutoArchivo),1,archivo);
            system("cls");
        }

        fclose(archivo);
    }
    else
    {
        printf("error no se pudo abrir el catalogo");
    }
}
void agregarPersonas()
{
    Persona p;
    char c='s';
    FILE* archivo = fopen("personas.bin","ab");
    if(archivo!=NULL)
    {
        while(c=='s')
        {
            printf("ingrese el dni: ");
            fflush(stdin);
            scanf("%d",&p.dni);
            printf("ingrese el nombre: ");
            fflush(stdin);
            scanf("%s",&p.nombre);
            printf("ingrese el apellido: ");
            fflush(stdin);
            scanf("%s",&p.apellido);

            printf("ingrese telefono: ");
            fflush(stdin);
            scanf("%d",&p.telefono);

            printf("ingrese la direccion de la persona: ");
            fflush(stdin);
            scanf("%s",&p.direccion);

            printf("ingrese el rol: ");
            scanf("%s",&p.rol);

            printf("desea continuar?(s/n): ");
            fflush(stdin);
            scanf("%c",&c);

            fwrite(&p,sizeof(Persona),1,archivo);
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
    FILE* archivo = fopen("personas.bin", "rb");

    if(archivo!=NULL)
    {
        while(fread(&p, sizeof(Persona), 1, archivo) > 0)
        {
            printf("-------------\n");
            printf("Dni:    \t%d\n", p.dni);
            printf("Nombre:      \t%s\n", p.nombre);
            printf("Apellido:      \t%s\n", p.apellido);
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
            scanf("%s",&v.autoAVender.letras);
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
        fseek(archivo, (pos)*sizeof(AutoArchivo), SEEK_SET);
        fread(&autoArch, sizeof(AutoArchivo), 1, archivo);

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
                        scanf("%s %d", &autoArch.patente.letras, &autoArch.patente.numeros);
                break;
                case 'm':
                        printf("Ingrese una nueva marca: "),
                        fflush(stdin);
                        scanf("%s", &autoArch.marca);
                break;
                case 'x':
                        printf("Ingrese un nuevo modelo: ");
                        fflush(stdin);
                        scanf("%s", &autoArch.modelo);
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
                        scanf("%d", &autoArch.precioDeAdquisicion);
                break;
                default:
                        printf("Error \n");
            }
            printf("Desea continuar? (s/n): ");
            fflush(stdin);
            scanf("%c", &seguir);
        }
        fseek(archivo, (pos)*sizeof(AutoArchivo), SEEK_SET);
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
        fseek(archivo, (pos)*sizeof(Persona), SEEK_SET);
        fread(&persona, sizeof(Persona), 1, archivo);

        while (seguir == 's')
        {
            printf("Que dato desea modificar? n(nombre)/d(direccion)/x(dni)/t(telefono)/r(rol): ");
            fflush(stdin);
            scanf("%c", &i);

            switch(i)
            {
                case 'n':
                        printf("Ingrese nuevo nombre: ");
                        fflush(stdin);
                        scanf("%s", &persona.nombre);
                break;
                case 'd':
                        printf("Ingrese una nueva direccion: "),
                        fflush(stdin);
                        scanf("%s", &persona.direccion);
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
                        scanf("%s", &persona.rol);
                        while(strcmp(persona.rol,"comprador")!=0 && strcmp(persona.rol,"vendedor")!=0)
                        {
                        printf("Ingrese un caracter valido(c/v): ");
                        fflush(stdin);
                        scanf("%s", &persona.rol);
                        }
                break;
                default:
                        printf("Error \n");
            }
            printf("Desea continuar? (s/n): ");
            fflush(stdin);
            scanf("%c", &seguir);
        }
        fseek(archivo, (pos)*sizeof(Persona), SEEK_SET);
        fwrite(&persona, sizeof(Persona),1,archivo);
        fclose(archivo);
    }
        else
        {
            printf("error a  ");
        }
}

void infoPersona ()
{
    FILE* archi = fopen("personas.bin", "rb");

    Persona persona;
    int i=0;

    if(archi != NULL)
    {
        printf("Ingrese el dni de la persona: ");
        scanf("%d", &i);

        while(fread(&persona, sizeof(Persona), 1, archi)>0)
        {
            if(i == persona.dni)
            {
                printf("-------------\n");
                printf("Dni:    \t%d\n", persona.dni);
                printf("Nombre:      \t%s\n", persona.nombre);
                printf("Apellido:      \t%s\n", persona.apellido);
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


void infoAuto ()
{
    FILE* archi = fopen("autosArch.bin", "rb");

    AutoArchivo autoArch;
    char letras[5];
    int num=0;
    int encontro=0;

    if(archi != NULL)
    {
        printf("Ingrese las letras de la patente: ");
        fflush(stdin);
        scanf("%s", &letras);
        printf("Ingrese los numeros de la patente: ");
        scanf("%d", &num);

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

    if(archi != NULL)
    {
        fseek(archi, sizeof(Venta)*pos, SEEK_SET);
        fread(&ventas, sizeof(Venta), 1, archi);
        printf("\nFecha:        %d/%d/%d", ventas.fecha.dia, ventas.fecha.mes, ventas.fecha.anio);
        printf("\nPatente:      %s-%d", ventas.autoAVender.letras, ventas.autoAVender.numeros);
        printf("\nDNI comprador:%d", ventas.dniComprador);
        printf("\nDNI vendedor: %d", ventas.dniVendedor);
        printf("\nPrecio Venta: %.2f", ventas.precioVenta);
        printf("\nGanancia:     %.2f", ventas.ganancia);

    fclose(archi);
    }else
    {
        printf("ERROR: No se pudo abrir el archivo");
    }
}

void agregarAuto ()
{
    FILE* archi = fopen("autos", "wb");

    Auto autito;
    char seguir = 's';

    if(archi != NULL)
    {
        while(seguir=='s')
        {
            printf("ingrese las letras de la patente: ");
            fflush(stdin);
            scanf("%s",&autito.patente.letras);
            printf("ingrese los numeros de la patente: ");
            scanf("%d",&autito.patente.numeros);

            printf("ingrese la marca del auto: ");
            fflush(stdin);
            scanf("%s",&autito.marca);

            printf("ingrese el modelo del auto: ");
            fflush(stdin);
            scanf("%s",&autito.modelo);

            printf("ingrese el anio del auto: ");
            scanf("%d",&autito.anio);

            printf("ingrese el kilometraje del auto: ");
            scanf("%d",&autito.kms);

            printf("ingrese el nombre del titular del auto: ");
            scanf("%s",&autito.Titular.nombre);

            printf("ingrese el apellido del titular del auto: ");
            fflush(stdin);
            scanf("%s", &autito.Titular.apellido);

            printf("ingrese dni del titular del auto: ");
            scanf("%d", &autito.Titular.dni);

            printf("ingrese telefono del titular del auto: ");
            scanf("%d", &autito.Titular.telefono);

            printf("ingrese direccion del titular del auto: ");
            scanf("%s", &autito.Titular.direccion);

            printf("ingrese el precio de adquisicion del auto: ");
            scanf("%f",&autito.precioDeAdquisicion);

            strcpy(autito.Titular.rol, "comprador");

            printf("desea continuar?(s/n): ");
            fflush(stdin);
            scanf("%c",&seguir);

            fwrite(&autito,sizeof(Auto),1,archi);
            system("cls");
        }
    fclose(archi);
    }
    else
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

}

