#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#define CURRENT_YEAR 2024
#define LONGITUD 20

typedef struct {        //patente
	char letras[3];
	int numeros;

} Patente;

typedef struct {        //autoArchivo
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
	char direccion[30];
	char rol[10]; //comprador o vendedor

} Persona;

typedef struct {        //auto
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
void registrarse();
void login(char*,char*,int*,int*);
void agregarAutoArchivo();
void agregarPersonas();
void mostrarAutoArchivo();
void mostrarPersonas();
void agregarVentas();
void mostrarVentas();
int main()
{

    char usuario[LONGITUD + 1];
    char clave[LONGITUD + 1];
    char Archivlogin[]="personas.bin";
    char ArchivAutos[]="autosArch.bin";
    int intento =0;
    int ingresa = 0;
    registrarse();
    login(usuario, clave, &intento, &ingresa);



    return 0;
}
void registrarse()
{
    FILE *archivos= fopen("personas.bin","ab");
    if(archivos==NULL)
    {
        printf("error");
    }

    char usuario[LONGITUD +1];
    char clave[LONGITUD+1];

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

void login(char *usuario, char *clave, int *intento, int *ingresa)
{

    FILE*archi=fopen("personas.bin","rb");
    char archivoUsuario[LONGITUD+1];
    char archivoClave[LONGITUD+1];
    if (archi == NULL)
    {
        printf("Error al abrir el archivo\n");
        return;
    }




    int i=0;

        printf ("\n\t\t\tINICIO DE SESION\n");
        printf ("\t\t\t----------------\n");
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
        if (autenticado){
            *ingresa=1;
           printf("\n\t\tBIENVENIDO A INMOBILIARIA Carlitos\n");
           printf("\t\t----------------------------------\n");
        }else{
            printf("\n\t\tCONTRASENA Y/O USUARIO INCORRECTO");
            (*intento)++;
        }
        fclose(archi);
}

void agregarAutoArchivo()
{
    AutoArchivo autoArch;
    char c='s';
    FILE* archivo = fopen("autosArch","wb");
    if(archivo!=NULL)
    {
        while(c=='s')
        {
            printf("ingrese las letras de la patente\n");
            fflush(stdin);
            scanf("%s",&autoArch.patente.letras);
            printf("ingrese los numeros de la patente\n");
            fflush(stdin);
            scanf("%d",&autoArch.patente.numeros);


            printf("ingrese la marca del auto\n");
            fflush(stdin);
            scanf("%s",&autoArch.marca);

            printf("ingrese la modelo del auto\n");
            fflush(stdin);
            scanf("%s",&autoArch.modelo);

            printf("ingrese el aÃ±o del auto\n");
            scanf("%d",&autoArch.anio);

            printf("ingrese el kilometraje del auto\n");
            scanf("%d",&autoArch.kms);

            printf("ingrese el dni del titular del auto\n");
            scanf("%d",&autoArch.dniTitular);

            printf("ingrese el precio de adquisicion del auto\n");
            scanf("%f",&autoArch.precioDeAdquisicion);

            printf("desea continuar?(s/n)\n");
            fflush(stdin);
            scanf("%c",&c);

            fwrite(&autoArch,sizeof(AutoArchivo),1,archivo);
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
    FILE* archivo = fopen("personas","wb");
    if(archivo!=NULL)
    {
        while(c=='s')
        {
            printf("ingrese el dni\n");
            fflush(stdin);
            scanf("%d",&p.dni);
            printf("ingrese el nombre\n");
            fflush(stdin);
            scanf("%s",&p.nombre);

            printf("ingrese telefono\n");
            fflush(stdin);
            scanf("%d",&p.telefono);

            printf("ingrese la direccion de la persona\n");
            fflush(stdin);
            scanf("%s",&p.direccion);

            printf("ingrese el rol\n");
            scanf("%s",&p.rol);

            printf("desea continuar?(s/n)\n");
            fflush(stdin);
            scanf("%c",&c);

            fwrite(&p,sizeof(Persona),1,archivo);
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
    FILE* archivo = fopen("autosArch", "rb");

    if(archivo!=NULL)
    {
        while(fread(&autoArch, sizeof(AutoArchivo), 1, archivo) > 0)
        {
            printf("Patente:    %s-%d\n", autoArch.patente.letras, autoArch.patente.numeros);
            printf("Marca:      %s\n", autoArch.marca);
            printf("Modelo:     %s\n", autoArch.modelo);
            printf("Anio:       %d\n", autoArch.anio);
            printf("Kms:        %d\n", autoArch.kms);
            printf("DniTitular: %d\n", autoArch.dniTitular);
            printf("PrecioAdq:  %.2f\n", autoArch.precioDeAdquisicion);
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
    FILE* archivo = fopen("personas", "rb");

    if(archivo!=NULL)
    {
        while(fread(&p, sizeof(Persona), 1, archivo) > 0)
        {
            printf("Dni:    \t%d\n", p.dni);
            printf("Nombre:      \t%s\n", p.nombre);
            printf("Telefono:     \t%d\n", p.telefono);
            printf("Direccion:\t%s\n", p.direccion);
            printf("Rol:\t\t%s\n", p.rol);

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
    FILE* archivo = fopen("ventas","wb");
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
    FILE* archivo = fopen("ventas", "rb");

    if(archivo!=NULL)
    {
        while(fread(&v, sizeof(Venta), 1, archivo) > 0)
        {
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
void Autos10anos()
{
    AutoArchivo aut;
    FILE*archi=fopen("autosArch","rb");
    int conta=0;
    AutoArchivo autos[100];
    if(archi!=NULL)
    {
        while(fread(&aut,sizeof(AutoArchivo),1,archi))
              {
                  if(CURRENT_YEAR - aut.anio<10)
                {
                    conta++;
                }
              }
                fclose(archi);
                for(int i=0;i<conta;i++)
                {
                    for (int j=i+1;j<conta;j++)
                    {
                        if(autos[i].anio<autos[j].anio)
                        {
                            AutoArchivo temp= autos[i];
                            autos[i]=autos[j];
                            autos[j]=temp;
                        }
                    }
                }

            for(int k=0;k<conta;k++)
            {
                    printf("Patente:    %s-%d\n", aut.patente.letras, aut.patente.numeros);
                    printf("Marca:      %s\n", aut.marca);
                    printf("Modelo:     %s\n", aut.modelo);
                    printf("Anio:       %d\n", aut.anio);
                    printf("Kms:        %d\n", aut.kms);
                    printf("DniTitular: %d\n", aut.dniTitular);
                    printf("PrecioAdq:  %.2f\n", aut.precioDeAdquisicion);
            }



}
}
