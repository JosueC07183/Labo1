/**
 * @file bingo.c
 * @author Josué Salmerón Córdoba (josue.salmeron@ucr.ac.cr)
 * @brief En este código se está implementando un juego de bingo que abarca los números del 00-99. Por cuestiones de memoria del microcontrolador PIC12F675, xolamente se presionará un botón
 *  10 veces (claramente se mostrarán números distintos sino el juego no tendrá sentido), hecho esto al final se mostrará el número 99 3 veces en el display de 7 segmentos y se reiniciará el
 * juego.
 * @version 0.1
 * @date 2024-01-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <pic14/pic12f675.h>
#define boton GP3 // Este botón gira la tombola y muestra el número aleatorio.
typedef unsigned int word;
word __at 0x2007 __CONFIG = (_MCLRE_OFF & _WDT_OFF & _BODEN_OFF);

/**
 * @brief Aquí están los prototipos de las funciones.
 * 
 * @param tiempo: delay de una transición.
 * @param num: variable que abarca los números del 0-9.
 * @param digito: posición de los display de 7s para crear una combinación.
 */
void delay(unsigned int tiempo);
void mostrar_num(unsigned int num, unsigned int digito);
/**
 * @brief En la siguiente función main del programa se consideran los periféricos a trabajar
 * Por lo que el TRISIO muestra un numero en un display excepto el GP3. El GPIO es cero porque
 * se necesitan todos los pines en bajo. CMCON pone en bajo el comparador. El VRCON elimina la
 * referencia de tensión. Después se definen los números que van en los display de 7 segmentos,
 * así como las variables aleatorias para crear los números. Se tiene un registro para ir contando
 * los números que van saliendo, y otro para sumar la cantidad de veces que se presiona el botón.
 * Luego con un ciclo do while infinito, se van sumando las variables ran_1 y ran_2, de donde con un
 * condicional se revisa si el botón está presionado para cambiar de estado y con esto el sumador cuenta
 * ya una bola de la tombola, ahora, con ayuda de la función de mostrar número se tiene un número del 0-9
 * en uno de los display con un pequeño delay para la transición se carga el otro número aleatorio, y se 
 * incrementan los registros. Ahora con un operador ternario se comprueban si los números aleatorios son mayores
 * a 10 y hacerlos 0. La siguiente etapa es cuando se presiona el botón, el contador de bolas registra cuando el
 * usuario presiona el botón, y el contador se incrementa. Después se asignan los números aleatorios a algunos
 * de los espacios de los displays de 7s. Por último, cuando ya han salido las 10 bolas o números del bingo ganador
 * lo que se hace es hacer un llamado a la función mostrar_num y presentar el número 99 que parpadear 3 veces y 
 * reiniciar el juego.
 * @param num_1: valor defecto de un display
 * @param num_2: valor defecto de un display
 * @param ran_1: número random de un display
 * @param ran_2: número random de un display
 * @param cont_num: contador, registro de números que ya salieron
 * @param cont_bolas: sumador que verifica si ya se presionó 10 veces el botón.
 */
void main(void) {
    TRISIO = 0b00001000;
    GPIO = 0x00;
    CMCON = 0X07;
    VRCON = 0X00;
    ANSEL = 0X00;
    unsigned int num_1 = 0;
    unsigned int num_2 = 0; 
    unsigned int ran_1 = 0;
    unsigned int ran_2 = 0;
    unsigned int cont_num = 0; 
    unsigned int cont_bolas = 0;
    unsigned int tiempo = 1;

    do {
        ran_1 ++;
        ran_2 ++;
        if(boton==1){
            cont_bolas = 1;
            mostrar_num(num_1,0);
            ran_2 ++;
            delay(tiempo);
            mostrar_num(num_2,0);
            ran_2 ++;
            delay(tiempo);
        }
        ran_1 = (ran_1 >= 10) ? 0 : ran_1;
        ran_2 = (ran_2 >= 10) ? 0 : ran_2;
        if(boton!=1){
            cont_num +=(cont_bolas==1) ? 1:0;
            cont_bolas = 0;
            num_1 = (unsigned int)(ran_1);
            num_2 = (unsigned int)(ran_2);
        }
        if(cont_num==10){
            unsigned int time = 30;
			unsigned int time_2 = 5;
// Primer parpadeo
			for (int i = 0; i < time; i++)
			{
				mostrar_num(9,0);
				delay(tiempo);
				mostrar_num(9,1);
				delay(tiempo);
				
			}
//Complemento del parpadeo
			for (int i = 0; i < time_2; i++)
			{
				mostrar_num(0,0);
				delay(tiempo);
				mostrar_num(0,1);
				delay(tiempo);
				
			}
// Segundo parpadeo
			for (int i = 0; i < time; i++)
			{
				mostrar_num(9,0);
				delay(tiempo);
				mostrar_num(9,1);
				delay(tiempo);	
			}
//Complemento del parpadeo
			for (int i = 0; i < time_2; i++)
			{
				mostrar_num(0,0);
				delay(tiempo);
				mostrar_num(0,1);
				delay(tiempo);	
			}
// Tercer parpadeo
			for (int i = 0; i < time; i++)
			{
				mostrar_num(9,0);
				delay(tiempo);
				mostrar_num(9,1);
				delay(tiempo);	
			}
//Complemento del parpadeo
			for (int i = 0; i < time_2; i++)
			{
				mostrar_num(0,0);
				delay(tiempo);
				mostrar_num(0,1);
				delay(tiempo);	
			}
			for (int i = 0; i < time; i++)
			{
				mostrar_num(9,0);
				delay(tiempo);
				mostrar_num(9,1);
				delay(tiempo);	
			}
// Reinicio del juego, los valores de los display y el contador son 0.
            num_1 = 0;
            num_2 = 0;
            cont_num = 0; // Acá se reinicia el juego.

        }

    }while (1);
}
/**
 * @brief Esta función muestra el número aleatorio en los display de 7 segmentos. Se toma el
 * caso de los números del 00-99, entonces GP5 será el encargado de colocar cada nñumero en cada
 * display. Por medio de casos se va analizando todaas las posibles combinaciones que permiten los
 * display de 7 segmentos.
 * @param num: esta variable indica el número que se está analizando, desde el 0-9
 * @param digito: coloca las combinaciones de los números en cada display.
 */
void mostrar_num(unsigned int num, unsigned int digito){
    GP5 = digito;
     switch (num) {
        case 0:
            GP0 = 0;
            GP1 = 0;
            GP2 = 0;
            GP4 = 0;
            break;

        case 1:
            GP0 = 1;
            GP1 = 0;
            GP2 = 0;
            GP4 = 0;
            break;

        case 2:
            GP0 = 0;
            GP1 = 1;
            GP2 = 0;
            GP4 = 0;
            break;

        case 3:
            GP0 = 1;
            GP1 = 1;
            GP2 = 0;
            GP4 = 0;
            break;

        case 4:
            GP0 = 0;
            GP1 = 0;
            GP2 = 1;
            GP4 = 0;
            break;

        case 5:
            GP0 = 1;
            GP1 = 0;
            GP2 = 1;
            GP4 = 0;
            break;

        case 6:
            GP0 = 0;
            GP1 = 1;
            GP2 = 1;
            GP4 = 0;
            break;

        case 7:
            GP0 = 1;
            GP1 = 1;
            GP2 = 1;
            GP4 = 0;
            break;

        case 8:
            GP0 = 0;
            GP1 = 0;
            GP2 = 0;
            GP4 = 1;
            break;

        case 9:
            GP0 = 1;
            GP1 = 0;
            GP2 = 0;
            GP4 = 1;
            break;

        default:
            case 10:
            GP0 = 0;
            GP1 = 1;
            GP2 = 0;
            GP4 = 1;
            break;
    }
}

/**
 * @brief Esta es la función de delay que se utilizó en el programa Hola PIC. Consiste en encender y apagar un LED en pequeños intervalos de tiempo.
 * 
 * @param tiempo: esto es el intervalo de tiempo que estará encendido el LED.
 */
void delay(unsigned int tiempo) {
    unsigned int i;
    unsigned int j;

    for (i = 0; i < tiempo; i++)
        for (j = 0; j < 1275; j++);
}

