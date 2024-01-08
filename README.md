### Universidad de Costa Rica
#### IE0624 - Laboratorio de Microcontroladores
##### Laboratorio 1: Introducción a microcontroladores y manejo de GPIOS

III Ciclo 2023

---
## Descripción
Este el primer laboratorio del curso IE0624, donde se desarrolla un bingo circuito de 10 bolas en total para obtener un ganador del premio en cuestión. Todo esto se desarrolló con ayuda de un microcontrolador PIC12F675, dos displays de 7 segmentos y demás componentes electrónicos para su buen funcionamiento.
## Puntos importantes
1. Ingresar en el directorio `src` y realizar lo siguiente.
   1. Abrir una terminal y escribir en la terminal la palabra `make`. Hecho esto sucederán dos eventos, primero se genera un archivo .hex, y el segundo es que se abrirá el .html con la documentación respectiva de Doxygen.
   2. Con el .hex listo, abrir el archivo *bingo.sim1* con SimulIDE y hacer click derecho sobre el PIC12F675, luego cargar firmware y seleccionar el .hex generado con el makefile.
   3. Hecho esto, ya es posible jugar bingo.
   4. Por último, para limpiar el directorio `src` basta con escribir `make clean` en la terminal.
