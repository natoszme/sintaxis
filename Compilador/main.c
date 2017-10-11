#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#define tamanio_matriz_filas 16
#define tamanio_matriz_columnas 13
#define cantidad_maxima_tokens 1000000
#define longitud_maxima_token 20
#define TAMLEX 32+1

typedef enum{
    INICIO, FIN, LEER, ESCRIBIR, ID, CONSTANTE, PARENIZQUIERDO, PARENDERECHO, PUNTOYCOMA, COMA, ASIGNACION, SUMA, RESTA, FDT, ERRORLEXICO
} TOKEN;

typedef struct{
    char identificador[TAMLEX];
    TOKEN tok; /* Del 0 al 3 Es PR, si es 4 es ID */
} RegistroTablaSimbolos;

RegistroTablaSimbolos tablaSimbolos[1000] = {
    {
        "inicio", INICIO
    },
    {
        "fin", FIN
    },
    {
        "leer", LEER
    },
    {
        "escribir", ESCRIBIR
    },
    {
        "$", 99
    }
};

/*=====================================================
=            FUNCIONES VARIAS                         =
=====================================================*/
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

int esSaltoLinea(char caracter)
{
    if (caracter == '\r\n' || caracter == '\n')
    {
        return 1;
    }

    return 0;
}

int esTab(char caracter)
{
    if (caracter == '\t')
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

    if (esEspacio(caracterLeido) || caracterLeido=='\t' || esSaltoLinea(caracterLeido))
    {
        return 11;
    }

    //12 es el estado de rechazo
    return 12;
}

int cambiarEstado(int matrizLexicografica[tamanio_matriz_filas][tamanio_matriz_columnas], int estadoActual, int columnaLeida)
{
    return matrizLexicografica[estadoActual][columnaLeida];
}

int reconocioIdentificador(int estado, char caracterEspureo, FILE* flujoEntrada)
{
    if (estado == 2)
    {
        char caracterControlUngetC = ungetc(caracterEspureo, flujoEntrada);

        if (caracterControlUngetC == caracterEspureo)
        {
            //por como funciona el ungetc, si entra a este if, el caracter se pudo devolver bien al flujo
            return 1;
        }
        else
        {
            //no pudo devolver el caracter espúreo al flujo
            printf("Error: no se pudo devolver uno de los caracteres espúreos al flujo");
            exit(0);
        }
    }
    return 0;
}

int reconocioConstante(int estado, char caracterEspureo, FILE* flujoEntrada)
{
    if (estado == 4)
    {
        char caracterControlUngetC = ungetc(caracterEspureo, flujoEntrada);

        if (caracterControlUngetC == caracterEspureo)
        {
            //por como funciona el ungetc, si entra a este if, el caracter se pudo devolver bien al flujo
            return 1;
        }
        else
        {
            //no pudo devolver el caracter espúreo al flujo
            printf("Error: no se pudo devolver uno de los caracteres espúreos al flujo");
            exit(0);
        }
    }

    return 0;
}

int reconocioPuntoYComa(int estado)
{
    if (estado == 10)
    {
        return 1;
    }

    return 0;
}

int reconocioSignoMas(int estado)
{
    if (estado == 5)
    {
        return 1;
    }

    return 0;
}

int reconocioSignoMenos(int estado)
{
    if (estado == 6)
    {
        return 1;
    }

    return 0;
}

int reconocioParentesisAbre(int estado)
{
    if (estado == 7)
    {
        return 1;
    }

    return 0;
}

int reconocioParentesisCierra(int estado)
{
    if (estado == 8)
    {
        return 1;
    }

    return 0;
}

int reconocioComa(int estado)
{
    if (estado == 9)
    {
        return 1;
    }

    return 0;
}

int reconocioOperadorAsignacion(int estado)
{
    if (estado == 12)
    {
        return 1;
    }

    return 0;
}

int reconocioFDT(int estado)
{
    if (estado == 13)
    {
        return 1;
    }

    return 0;
}

int reconocioOtro(int estado)
{
    if (estado == 14)
    {
        return 1;
    }

    return 0;
}

/*=====================================================
=            FIN::FUNCIONES VARIAS                         =
=====================================================*/

void errorSintactico(){
    printf("Error Sintactico \n");
}

void erroresArchivo(int numeroError)
{
	switch(numeroError)
	{
		case 0:
            printf("Debe ingresar un unico argumento: la ruta del archivo a procesar");
		break;

		case 1:
			printf("El archivo no pudo ser abierto");
        break;
	}
}

FILE* flujoEntrada;



/*=====================================================
=            DEVUELVE EL TOKEN                         =
=====================================================*/
TOKEN token()
{
    int matrizLexicografica[tamanio_matriz_filas][tamanio_matriz_columnas] = {
              //L  D  +  -  (  )  ,  ;  :  = fdt sp otro
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
       /* 11*/ {15,15,15,15,15,15,15,15,15,12,15,15,15},
       /* 12*/ {14,14,14,14,14,14,14,14,14,14,14,14,14},
       /* 13*/ {14,14,14,14,14,14,14,14,14,14,14,14,14},
       /* 14*/ {14,14,14,14,14,14,14,14,14,14,14,14,14},
       /* 15*/ {15,15,15,15,15,15,15,15,15,15,15,15,15}
    };

    int estado = 0;

    char caracterLeido;
    int columnaCaracterLeido;
    //const char array_tokens[cantidad_maxima_tokens][longitud_maxima_token];
    int posicion_token = 0;
    char caracterControlUngetC;
    char string_token[TAMLEX];

    //char *stringTokens;

    //chequear qué pasa con el espacio y los saltos de linea
    while( (caracterLeido = getc(flujoEntrada)))
    {


        if(!((esEspacio(caracterLeido)) || (esSaltoLinea(caracterLeido)) || (esTab(caracterLeido))))
        {
            string_token[posicion_token] = caracterLeido;
            posicion_token++;
        }
        printf("Caracter actual: %c\n", caracterLeido);

        columnaCaracterLeido = columnaMatrizPorCaracter(caracterLeido);

        //printf("Columna caracter actual: %d\n", columnaCaracterLeido);

        estado = cambiarEstado(matrizLexicografica, estado, columnaCaracterLeido);

        //printf("Nuevo estado: %d\n", estado);

        if (reconocioIdentificador(estado, caracterLeido, flujoEntrada))
        {
            TOKEN* identificador;
            if(buscarEnLaTS(string_token,tablaSimbolos,identificador))
            {
                 printf("PALABRA RESERVADA\n");
                 return identificador;
            }
            printf("IDENTIFICADOR\n");
            return ID;
        }

        if (reconocioConstante(estado, caracterLeido, flujoEntrada))
        {
            printf("CONSTANTE\n");
            return CONSTANTE;
        }

        if (reconocioPuntoYComa(estado))
        {
            printf("PUNTOYCOMA\n");
            return PUNTOYCOMA;
        }

        if (reconocioSignoMas(estado))
        {
            printf("OPERADORMAS\n");
            return SUMA;
        }

        if (reconocioSignoMenos(estado))
        {
            printf("OPERADORMENOS\n");
            return RESTA;
        }

        if (reconocioParentesisAbre(estado))
        {
            printf("PARENTESISABRE\n");
            return PARENIZQUIERDO;
        }

        if (reconocioParentesisCierra(estado))
        {
            printf("PARENTESISCIERRA\n");
            return PARENDERECHO;
        }

        if (reconocioComa(estado))
        {
            printf("COMA\n");
            return COMA;
        }

        if (reconocioOperadorAsignacion(estado))
        {
            printf("OPERADORASIGNACION\n");
            return ASIGNACION;
        }

        if (estado == 15)
        {
            printf("ERRORLEXICOGRAFICO\n");

            caracterControlUngetC = ungetc(caracterLeido, flujoEntrada);

            if (caracterControlUngetC == caracterLeido)
            {
                //por como funciona el ungetc, si entra a este if, el caracter se pudo devolver bien al flujo
                return ERRORLEXICO;
            }
            else
            {
                //no pudo devolver el caracter espúreo al flujo
                printf("Error: no se pudo devolver uno de los caracteres espúreos al flujo");
                exit(0);
            }
        }

        if (reconocioOtro(estado))
        {
            printf("ERRORLEXICOGRAFICO\n");
            return ERRORLEXICO;
        }

        //chequear que pasa con este return cuando se quiera usar el scanner para la funcion match!
        if (reconocioFDT(estado))
        {
            printf("FDT\n");
            return FDT;
        }

    }
}
/*=====================================================
=           FIN::DEVUELVE EL TOKEN                    =
=====================================================*/

/*=====================================================
=            FUNCIONES ANALISIS SINTACTICO            =
=====================================================*/
void match(TOKEN t){
    if(!(t == token())){
        errorSintactico();
    }
}
typedef struct{
    TOKEN clase;
    char nombre[TAMLEX];
    int valor;
} EXPRESION_REGULAR;

int buscarEnLaTS(char *id, RegistroTablaSimbolos *tablaSimbolos, TOKEN *token){
    int i = 0;
    while(strcmp("$", tablaSimbolos[i].identificador)){ //RECORRO HASTA EL ULTIMO
        if(!strcmp(id, tablaSimbolos[i].identificador)){ //ENCONTRE EL ID
            *token = tablaSimbolos[i].tok;
            return 1;
        }
        i++;
    }
    return 0;
}

void expresion(EXPRESION_REGULAR *presul);
void identificador(EXPRESION_REGULAR *presul);

void primaria(EXPRESION_REGULAR *presul){
    TOKEN tok = token();
    switch(tok){
        case ID:
            match(ID);
            break;
        case CONSTANTE:
            match(CONSTANTE);
            break;
        case PARENIZQUIERDO:
            match(PARENIZQUIERDO);
            expresion(presul);
            match(PARENDERECHO);
            break;
        default:
            return;
    }
}

void operadorAditivo(char *presul){
    TOKEN tok = token();
    if(tok == SUMA || tok == RESTA){
        match(tok);
        //strcpy(presul, procesarOperador()); RS
    }else{
        errorSintactico();
    }
}

void expresion(EXPRESION_REGULAR *presul){
    EXPRESION_REGULAR operandoIzquierdo, operandoDerecho;
    char operador[TAMLEX];
    TOKEN tok;
    primaria(&operandoIzquierdo);
    for (tok = token(); tok == SUMA || tok == RESTA; tok = token())
    {
        operadorAditivo(operador);
        primaria(&operandoDerecho);
        //operandoIzquierdo = genInfijo(operandoIzquierdo, operador, operandoDerecho); RS
    }
}

void identificador(EXPRESION_REGULAR *presul){
    match(ID);
    //*presul = procesarID(); ACA SE LLAMA A LA RUTINA SEMANTICA
}

void listaIdentificadores(){
    TOKEN tok;
    EXPRESION_REGULAR regular;
    identificador(&regular);
    //leer(regular);

    for (tok = token(); tok == COMA; tok = token())
    {
        match(COMA);
        identificador(&regular);
        //leer(regular);
    }
}

void listaExpresiones(){
    TOKEN tok;
    EXPRESION_REGULAR regex;
    expresion(&regex);
    //escribir(regex); RS
    for (tok = token(); tok == COMA; tok = token())
    {
        match(COMA);
        expresion(&regex);
        //escribir(regex); RS
    }
}

void sentencia(){
    TOKEN tok = token();
    EXPRESION_REGULAR izquierda, derecha;
    switch(tok){
        case ID: //ASIGNACION
            match(ASIGNACION);
            expresion(&derecha);
            match(PUNTOYCOMA);
            break;
        case LEER: //LECTURA DE LISTA IDS
            match(PARENIZQUIERDO);
            listaIdentificadores();
            match(PARENDERECHO);
            match(PUNTOYCOMA);
            break;
        case ESCRIBIR: //ESCRITURA SENTENCIAS
            match(PARENIZQUIERDO);
            listaExpresiones();
            match(PARENDERECHO);
            match(PUNTOYCOMA);
            break;
        default: // NO RECONOCE SENTENCIA, ENTONCES FINALIZA
            return;
    }
}
void listaSentencias(){
    sentencia();
    while(1){ // NO ES TAN LOCO; HASTA QUE HACE EL RETURN...
        switch(token()){
            case ID:
            case LEER:
            case ESCRIBIR:
                sentencia();
                break;
            default:
                return; // SI NO ES SENTENCIA; TERMINA LA FUNCION
        }
    }
}

void programa(){
    match(INICIO);
    listaSentencias();
    match(FIN);
}

void objetivo(){
    programa();
    match(FDT);
}

/*=====================================================
=      FIN :: FUNCIONES ANALISIS SINTACTICO           =
=====================================================*/
int main(int argc, char *argv[])
{
    char *rutaDelFlujo = argv[1];

    if(argc != 2)
    {
		erroresArchivo(0);
		return 0;
	}

	if( flujoEntrada = fopen(rutaDelFlujo, "r") )
    {
        objetivo();
        fclose(flujoEntrada);
    }
    else
    {
        erroresArchivo(1);
        return 0;
    }

    return 0;
}
