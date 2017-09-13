#include <stdio.h>
#include <stdlib.h>

int cambiarEstado(int **matrizLexicografica, int *estadoActual, int columnaLeida)
{
    *estadoActual = matrizLexicografica[estadoActual][columnaLeida];
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

    if (esOperador(caracterLeido))
    {
        return 2;
    }

    if (esDosPuntos(caracterLeido))
    {
        return 3;
    }

    if (esIgual(caracterLeido))
    {
        return 4;
    }

    if (esSignoPuntuacion(caracterLeido))
    {
        return 5;
    }

    if (esFinDeTexto(caracterLeido))
    {
        return 6;
    }

    //7 es el estado de rechazo
    return 7;
}

int main()
{
    int matrizLexicografica[11][8] = {
        {1,3,5,6,10,8,9,10},
        {1,1,2,2,2,2,2,10},
        {10,10,10,10,10,10,10,10},
        {10,3,4,4,4,4,4,10},
        {10,10,10,10,10,10,10,10},
        {10,10,10,10,10,10,10,10},
        {10,10,10,10,7,10,10,10},
        {10,10,10,10,10,10,10,10},
        {10,10,10,10,10,10,10,10},
        {10,10,10,10,10,10,10,10},
        {10,10,10,10,10,10,10,10}
    };

    int estado;



    return 0;
}
