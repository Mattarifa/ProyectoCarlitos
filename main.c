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

    login(usuario, clave, &intento, &ingresa);
    registrarse();


    return 0;
}
void registrarse()
{
    File *archivos= fopen("personas.bin","wb");
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
