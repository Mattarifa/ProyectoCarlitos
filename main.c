#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define LONGITUD 20

int main()
{

    char usuario[LONGITUD + 1];
    char clave[LONGITUD + 1];
    int intento =0;
    int ingresa = 0;
    registrarse();
    login(usuario, clave, &intento, &ingresa);
    registrarse();


    return 0;
}
void registrarse()
{
    FILE *archivos= fopen("personas.bin","wb");
    if(archivos==NULL)
    {
        printf("error");
    }

    char usuario[LONGITUD +1];
    char clave[LONGITUD+1];

    printf("\n\tIngrese un nombre de usuario: ");
    fgets(usuario,LONGITUD+1,stdin);
    usuario[strcspn(usuario, '/n')]='/0';///strcspn(usuario, "\n") devuelve la posición del primer carácter en usuario que es \n, /0 para eliminar el salto de linea

    printf("\n\tIngrese una contrasena: ");
    fgets(usuario,LONGITUD+1,stdin);
    usuario[strcspn(usuario,'/n')]='/0';

    fwrite(usuario,sizeof(char),LONGITUD+1,archivos);
    fwrite(clave,sizeof(char),LONGITUD+1,archivos);

    fclose(archivos);
    printf("\n\t---------------------------------");
    printf("\n\tUsuario registrado correctamente");
    printf("\n\t---------------------------------");



}

void login(char *usuario, char *clave, int *intento, int *ingresa)
{

    FILE*archi=fopen("personas.bin","wb");
    char archivoUsuario[LONGITUD+1];
    char archivoClave[LONGITUD+1];
    if (archi == NULL)
    {
        printf("Error al abrir el archivo\n");
        return;
    }

    fread(archivoUsuario,sizeof(char),LONGITUD+1,archi);
    fread(archivoUsuario,sizeof(char),LONGITUD+1,archi);
    fclose(archi);

    char caracter;
    int i=0;
    do{
        printf ("\n\t\t\tINICIO DE SESION\n");
        printf ("\t\t\t----------------\n");
        printf("\n\tUSUARIO: ");
        gets(usuario);
        printf("\n\tCLAVE: ");
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

    if(strcmp(usuario,archivoUsuario)== 0 && strcmp(clave,archivoClave)== 0){
        *ingresa =1;
        printf ("\n\t\tBIENVENIDO A INMOBILIARIA Carlitos\n");
        printf ("\t\t----------------------------------\n");

    }else{
        printf ("\n\t\tUSUARIO Y/O CONTRASENIA INCORRECTOS\n");
        (*intento)++;

    }
    }while (*intento <3 && *ingresa == 0);
}
