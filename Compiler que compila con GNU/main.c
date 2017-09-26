#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tamanio_matriz_filas 15
#define tamanio_matriz_columnas 13
#define cantidad_maxima_tokens 1000000
#define longitud_maxima_token 20
#define TAMLEX 32+1


/* ESTRUCTURAS PARA UTILIZAR TABLA DE SIMBOLOS */
typedef enum{
    INICIO, FIN, LEER, ESCRIBIR, ID, CONSTANTE, PARENIZQUIERDO, PARENDERECHO, PUNTOYCOMA, COMA, ASIGNACION, SUMA, RESTA, FDT, ERRORLEXICO
} TOKEN;

// typedef struct{
//     char identificador[TAMLEX];
//     TOKEN tok; /* Del 0 al 3 Es PR, si es 4 es ID */
// } RegistroTablaSimbolos;

// RegistroTablaSimbolos tablaSimbolos[1000] = {
//     {
//         "inicio", INICIO
//     },
//     {
//         "fin", FIN
//     },
//     {
//         "leer", LEER
//     },
//     {
//         "escribir", ESCRIBIR
//     },
//     {
//         "$", 99
//     }
// };

// typedef struct{
//     TOKEN clase;
//     char nombre[TAMLEX];
//     int valor;
// } EXPRESION_REGULAR;

// /* FUNCIONES DE LA TABLA DE SIMBOLOS */

// /*
// *   @function buscarEnLaTS
// *   Función que busca un id en la TS y devuelve el TOKEN
// */
// int buscarEnLaTS(char *id, RegistroTablaSimbolos *tablaSimbolos, TOKEN *token){
//     int i = 0;
//     while(strcmp("$", tablaSimbolos[i].identificador)){ //RECORRO HASTA EL ULTIMO
//         if(!strcmp(id, tablaSimbolos[i].identificador)){ //ENCONTRE EL ID
//             *token = tablaSimbolos[i].tok;
//             return 1;
//         }
//         i++;
//     }
//     return 0;
// }

// /*
// *   @function colocarEnLaTS
// *   Función que agrega un id a la TS
// */

// void colocarEnLaTS(char *id, RegistroTablaSimbolos *tablaSimbolos){
//     int i = 4;
//     while(strcmp("$", tablaSimbolos[i].identificador)){
//         i++;
//     }
//     if(i < 999){
//         strcpy(tablaSimbolos[i].identificador, id);
//         tablaSimbolos[i].tok = ID;
//         strcpy(tablaSimbolos[++i].identificador, "$");
//     }
// }

// /*
// *   @function chequearTS
// *   Función que agrega un id a la TS si este no esta
// */

// void chequearTS(char *s){
//     TOKEN tok;
//     if(!buscarEnLaTS(s, tablaSimbolos, &tok)){
//         colocarEnLaTS(s, tablaSimbolos);
//         //ACA DEBERIA GENERAR LA INSTRUCCION
//     }
// }

// /*=====================================================
// =            FUNCIONES ANALISIS SINTACTICO            =
// =====================================================*/
// void expresion(EXPRESION_REGULAR *presul);
// void identificador(EXPRESION_REGULAR *presul);

// void primaria(EXPRESION_REGULAR *presul){
//     TOKEN tok = proximoToken();
//     switch(tok){
//         case ID:
//             identificador(presul);
//             break;
//         case CONSTANTE:
//             match(CONSTANTE);
//             // *presul = procesarConstante(); RS
//             break;
//         case PARENIZQUIERDO:
//             match(PARENIZQUIERDO);
//             expresion(presul);
//             match(PARENDERECHO);
//             break;
//         default:
//             return;
//     }
// }

// void operadorAditivo(char *presul){
//     TOKEN tok = proximoToken();
//     if(tok == SUMA || tok == RESTA){
//         match(tok);
//         //strcpy(presul, procesarOperador()); RS
//     }else{
//         // errorSintactico(tok); RS
//     }
// }

// void expresion(EXPRESION_REGULAR *presul){
//     EXPRESION_REGULAR operandoIzquierdo, operandoDerecho;
//     char operador[TAMLEX];
//     TOKEN tok;
//     primaria(&operandoIzquierdo);
//     for (tok = proximoToken(); tok == SUMA || tok == RESTA; tok = proximoToken())
//     {
//         operadorAditivo(operador);
//         primaria(&operandoDerecho);
//         //operandoIzquierdo = genInfijo(operandoIzquierdo, operador, operandoDerecho); RS
//     }
// }

// void identificador(EXPRESION_REGULAR *presul){
//     match(ID);
//     //*presul = procesarID(); ACA SE LLAMA A LA RUTINA SEMANTICA
// }

// void listaIdentificadores(){
//     TOKEN tok;
//     EXPRESION_REGULAR regular;
//     identificador(&regular);
//     leer(regular);

//     for (tok = proximoToken(); tok == COMA; tok = proximoToken())
//     {
//         match(COMA);
//         identificador(&regular);
//         leer(regular);
//     }
// }

// void listaExpresiones(){
//     TOKEN tok;
//     EXPRESION_REGULAR regex;
//     expresion(&regex);
//     //escribir(regex); RS
//     for (tok = proximoToken(); tok == COMA; tok = proximoToken())
//     {
//         match(COMA);
//         expresion(&regex);
//         //escribir(regex); RS
//     }
// }

// void sentencia(){
//     TOKEN tok = proximoToken();
//     EXPRESION_REGULAR izquierda, derecha;
//     switch(tok){
//         case ID: //ASIGNACION
//             identificador(&izquierda);
//             match(ASIGNACION);
//             expresion(&derecha);
//             asignar(izquierda, derecha);
//             match(PUNTOYCOMA);
//             break;
//         case LEER: //LECTURA DE LISTA IDS
//             match(LEER);
//             match(PARENIZQUIERDO);
//             listaIdentificadores();
//             match(PARENDERECHO);
//             match(PUNTOYCOMA);
//             break;
//         case ESCRIBIR: //ESCRITURA SENTENCIAS
//             match(ESCRIBIR);
//             match(PARENIZQUIERDO);
//             listaExpresiones();
//             match(PARENDERECHO);
//             match(PUNTOYCOMA);
//             break;
//         default: // NO RECONOCE SENTENCIA, ENTONCES FINALIZA
//             return;
//     }
// }
// void listaSentencias(){
//     sentencia();
//     while(1){ // NO ES TAN LOCO; HASTA QUE HACE EL RETURN...
//         switch(proximoToken()){
//             case ID: 
//             case LEER: 
//             case ESCRIBIR:
//                 sentencia();
//                 break;
//             default:
//                 return; // SI NO ES SENTENCIA; TERMINA LA FUNCION
//         }
//     }
// }

// void programa(){
//     comenzar();
//     match(INICIO);
//     listaSentencias();
//     match(FIN);
// }

// void objetivo(){
//     programa();
//     match(FDT);
//     terminar();
// }


/*=====  FIN :: FUNCIONES ANALISIS SINTACTICO  ======*/

/**

    PARA HACER:
    - PROXIMOTOKEN
    - MATCH
    - LEER
    - ASIGNAR
    - COMENZAR
    - TERMINAR
    
    SIN ESTO NO COMPILARÁ!
 */



/* FUNCIONES */

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
    if (caracter == '\n')
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
    //contemplado el caso del ':' sin el '='
    if (estado == 14 || estado == 11)
    {
        return 1;
    }

    return 0;
}


/*void recorrerTokens(char array_tokens[cantidad_maxima_tokens][longitud_maxima_token])
{
    int i = 0;
    for ( i ; i < cantidad_maxima_tokens ; i++ )
    {
        char *token_actual = array_tokens[i];

        //REVISAR
        if (token_actual != "")
        {
            printf("%s", token_actual);
        }
    }
}*/

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

int main(int argc, char *argv[])
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
       /* 11*/ {14,14,14,14,14,14,14,14,14,12,14,14,14},
       /* 12*/ {14,14,14,14,14,14,14,14,14,14,14,14,14},
       /* 13*/ {14,14,14,14,14,14,14,14,14,14,14,14,14},
       /* 14*/ {14,14,14,14,14,14,14,14,14,14,14,14,14}
    };

    int estado = 0;
    char *rutaDelFlujo = argv[1];
    FILE* flujoEntrada;

    if(argc != 2)
    {
		erroresArchivo(0);
		return 0;
	}

	if( flujoEntrada = fopen(rutaDelFlujo, "r") )
    {
        char caracterLeido;
        int columnaCaracterLeido;
        //const char array_tokens[cantidad_maxima_tokens][longitud_maxima_token];
        int posicion_token = 0;

        //char *stringTokens;

        //chequear qué pasa con el espacio y los saltos de linea
        while( (caracterLeido = getc(flujoEntrada)) && (!esEspacio(caracterLeido)) && (!esSaltoLinea(caracterLeido)) )
        {
            printf("Caracter actual: %c\n", caracterLeido);

            columnaCaracterLeido = columnaMatrizPorCaracter(caracterLeido);

            printf("Columna caracter actual: %d\n", columnaCaracterLeido);

            estado = cambiarEstado(matrizLexicografica, estado, columnaCaracterLeido);

            printf("Nuevo estado: %d\n", estado);

            if (reconocioIdentificador(estado, caracterLeido, flujoEntrada))
            {
                //se reconocio un identificador
                //array_tokens[posicion_token] = "IDENTIFICADOR";

                printf("IDENTIFICADOR\n");

                estado = 0;
            }

            if (reconocioConstante(estado, caracterLeido, flujoEntrada))
            {
                //se reconocio una constante
                //array_tokens[posicion_token] = "CONSTANTE";

                printf("CONSTANTE\n");

                estado = 0;
            }

            if (reconocioPuntoYComa(estado))
            {
                //se reconocio el punto y coma
                //array_tokens[posicion_token] = "PUNTOYCOMA";

                printf("PUNTOYCOMA\n");

                estado = 0;
            }

            if (reconocioSignoMas(estado))
            {
                printf("OPERADORMAS\n");
                estado = 0;
            }

            if (reconocioSignoMenos(estado))
            {
                printf("OPERADORMENOS\n");
                estado = 0;
            }

            if (reconocioParentesisAbre(estado))
            {
                printf("PARENTESISABRE\n");
                estado = 0;
            }

            if (reconocioParentesisCierra(estado))
            {
                printf("PARENTESISCIERRA\n");
                estado = 0;
            }

            if (reconocioComa(estado))
            {
                printf("COMA\n");
                estado = 0;
            }

            if (reconocioOperadorAsignacion(estado))
            {
                printf("OPERADORASIGNACION\n");
                estado = 0;
            }

            if (reconocioOtro(estado))
            {
                printf("ERRORLEXICOGRAFICO\n");
                estado = 0;
            }

            //chequear que pasa con este return cuando se quiera usar el scanner para la funcion match!
            if (reconocioFDT(estado))
            {
                printf("FDT\n");

                return 0;
            }

            posicion_token++;
        }

        //recorrerTokens(array_tokens);

        fclose(flujoEntrada);
    }
    else
    {
        erroresArchivo(1);
        return 0;
    }

    return 0;
}

/*========================================
=            SCANNER DE OSCAR            =
========================================*/

FILE* flujoEntrada;
char *buffer;

int estadoFinal(int estado){
    if(estado == 0 || estado == 1 || estado == 3 || estado == 11 || estado == 14)
        return 0;
    else
        return 1;
}

int columna(int caracter){
    if(isalpha(caracter)) return 0;
    if(isdigit(caracter)) return 1;
    if(caracter == '+') return 2;
    if(caracter == '-') return 3;
    if(caracter == '(') return 4;
    if(caracter == ')') return 5;
    if(caracter == ',') return 6;
    if(caracter == ';') return 7;
    if(caracter == ':') return 8;
    if(caracter == '=') return 9;
    if(caracter == EOF) return 10;
    if(isspace(caracter)) return 11;
    return 12;
}

TOKEN scanner(){
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
       /* 11*/ {14,14,14,14,14,14,14,14,14,12,14,14,14},
       /* 12*/ {14,14,14,14,14,14,14,14,14,14,14,14,14},
       /* 13*/ {14,14,14,14,14,14,14,14,14,14,14,14,14},
       /* 14*/ {14,14,14,14,14,14,14,14,14,14,14,14,14}
    };

    int caracter;
    int columnaActual;
    int estado = 0;
    int i = 0;
    do{
        caracter = fgetc(flujoEntrada);
        columnaActual = columna(caracter);
        estado = matrizLexicografica[estado][columnaActual];
        if(columnaActual != 11){ // SI NO ES ESPACIO
            buffer[i] = caracter;
            i++;
        }
    }while(!estadoFinal(estado) && !(estado == 14));
    buffer[i] = '\0'; //FIN CADNA

    switch(estado){
        case 2:
            if(columnaActual != 11){
                ungetc(caracter, flujoEntrada); // SI EL CARACTER ESPUREO NO ES BLANCO, VA AL FLUJO
                buffer[i-1] = '\0';
            }
            return ID;
        case 4:
            if(columnaActual != 11){
                ungetc(caracter, flujoEntrada);
                buffer[i-1] = '\0';
            }
            return CONSTANTE;
        case 5: return SUMA;
        case 6: return RESTA;
        case 7: return PARENIZQUIERDO;
        case 8: return PARENDERECHO;
        case 9: return COMA;
        case 10: return PUNTOYCOMA;
        case 12: return ASIGNACION;
        case 13: return FDT;
        case 14: return ERRORLEXICO;
    }
    return 0;

}


/*=====  End of SCANNER DE OSCAR  ======*/
