#include <stdio.h>
#include <stdlib.h>

int convertirCaracterANumero(char caracter)
{
    int valorDecimal = caracter - '0';
    return valorDecimal;
}
int esNumero(char caracter)
{
    int valorDecimal = convertirCaracterANumero(caracter);
    if (valorDecimal >= 0 && valorDecimal <= 9)
    {
        return 1;
    }
    return 0;
}

int esMas(char caracter)
{
    if (caracter == '+')
    {
        return 1;
    }
    return 0;
}

int esMenos(char caracter)
{
    if (caracter == '-')
    {
        return 1;
    }
    return 0;
}

int esLetra(char caracter)
{
    if ((caracter >= 'a' && caracter <= 'z') || (caracter >= 'A' && caracter <= 'Z'))
    {
        return 1;
    }

    return 0;
}

int esDosPuntos(char caracter)
{
    if (caracter == ':')
    {
        return 1;
    }
    return 0;
}

int esIgual(char caracter)
{
    if (caracter == '=')
    {
        return 1;
    }
    return 0;
}

int esParentesisQueAbre(char caracter)
{
    if (caracter == '(')
    {
        return 1;
    }
    return 0;
}

int esParentesisQueCierra(char caracter)
{
    if (caracter == ')')
    {
        return 1;
    }
    return 0;
}

int esComa(char caracter)
{
    if (caracter == ',')
    {
        return 1;
    }
    return 0;
}

int esPuntoyComa(char caracter)
{
    if (caracter == ';')
    {
        return 1;
    }
    return 0;
}

int esEspacio(char caracter)
{
    if (caracter == ' ')
    {
        return 1;
    }
    return 0;
}

int esFinDeTexto(char caracter)
{
    if (caracter == EOF)
    {
        return 1;
    }

    return 0;
}

int columnaMatrizPorCaracter(char caracterLeido)
{
    if (esLetra(caracterLeido))
    {
        return 0;
    }

    if (esNumero(caracterLeido))
    {
        return 1;
    }

    if (esMas(caracterLeido))
    {
        return 2;
    }

    if (esMenos(caracterLeido))
    {
        return 3;
    }

    if (esParentesisQueAbre(caracterLeido))
    {
        return 4;
    }

    if (esParentesisQueCierra(caracterLeido))
    {
        return 5;
    }

    if (esComa(caracterLeido))
    {
        return 6;
    }

    if (esPuntoyComa(caracterLeido))
    {
        return 7;
    }

    if (esDosPuntos(caracterLeido))
    {
        return 8;
    }

    if (esIgual(caracterLeido))
    {
        return 9;
    }

    if (esFinDeTexto(caracterLeido))
    {
        return 10;
    }

    if (esEspacio(caracterLeido))
    {
        return 11;
    }

    //12 es el estado de rechazo
    return 12;
}

void erroresArchivo(int numeroError)
{
	switch(numeroError)
	{
		case 0:
            printf("Debe ingresar un argumento");
		break;

		case 1:
			printf("El archivo no pudo ser abierto");
        break;
	}
}


int cambiarEstado(int **matrizLexicografica, int estadoActual, int columnaLeida)
{
    return matrizLexicografica[estadoActual][columnaLeida];
}

int main(int argc, char *argv[])
{
    int matrizLexicografica[15][13] = {
              //L  D  +  -  (  )  ,   ; :  = fdt sp otro
       /* 0 */ {1, 3, 5, 6, 7, 8, 9, 10,11,14,13,0, 14},
       /* 1 */ {1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
       /* 2 */ {14,14,14,14,14,14,14,14,14,14,14,14,14},
       /* 3 */ {4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
       /* 4 */ {14,14,14,14,14,14,14,14,14,14,14,14,14},
       /* 5 */ {14,14,14,14,14,14,14,14,14,14,14,14,14},
       /* 6 */ {14,14,14,14,14,14,14,14,14,14,14,14,14},
       /* 7 */ {14,14,14,14,14,14,14,14,14,14,14,14,14},
       /* 8 */ {14,14,14,14,14,14,14,14,14,14,14,14,14},
       /* 9 */ {14,14,14,14,14,14,14,14,14,14,14,14,14},
       /* 10*/ {14,14,14,14,14,14,14,14,14,14,14,14,14},
       /* 11*/ {14,14,14,14,14,14,14,14,14,12,14,14,14},
       /* 12*/ {14,14,14,14,14,14,14,14,14,14,14,14,14},
       /* 13*/ {14,14,14,14,14,14,14,14,14,14,14,14,14},
       /* 14*/ {14,14,14,14,14,14,14,14,14,14,14,14,14}
    };

    int estado = 0;
    char *rutaDelFlujo = argv[1];
    FILE* flujoEntrada;

    if(argc=!2)
    {
		erroresArchivo(0);
		return 0;
	}

	if( flujoEntrada = fopen(rutaDelFlujo, "r") )
    {
        char caracterLeido;
        int columnaCaracterLeido = 0;

        //chequear qué pasa con el fin de archivo
        while( caracterLeido = getc(flujoEntrada) )
        {
            columnaCaracterLeido = columnaMatrizPorCaracter(caracterLeido);
            estado = cambiarEstado(matrizLexicografica, estado, columnaCaracterLeido);

            //comentario de prueba


        }
    }
    else
    {
        erroresArchivo(1);
        return 0;
    }


    return 0;
}
