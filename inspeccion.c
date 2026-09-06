#include <stdio.h>
#include <stdbool.h>
// pregunta 1: ¿Cuantos pasajeros realizaran el viaje inaugural? int(1-250)
// si cant. pasajeros <= 180 --> se realiza el viaje
// si cant. pasajeros > 180 --> no se realiza el viaje. -NO APTO-

// pregunta 2: ¿Que distancia recorrio el monorriel durante la prueba de los frenos? float(0.0-150.0)
// distancia <= 50 --> aprobado
// 50 < distancia <= 100 --> falla pero no hay heridos (-1)
// 100 < distancia <= 150 --> desaprobado (-2)

// pregunta 3: ¿A que hora esta programado el viaje inaugural? (hh(0-23):mm(0-59))
// si viaje entre 06:00 y 19:59 --> aprobado
// si viaje entre 20:00 y 05:59 --> desaprobado (-3)

// pregunta 4: ¿Que encontro Marge en el compartimiento del matafuegos?
//  [M]Matafuegos(+1), [Z]Zarigueyas(-1), [V]Vacio(-3)

// puntaje final:
// puntaje (8-10) --> -APTO-
// puntaje (5-7) --> -REQUIERE REVISION-
// puntaje(0-4) --> -NO APTO-

const int PUNTAJE_MAXIMO = 10;

const int MAXIMO_RANGO_PASAJEROS = 250;
const int MAXIMO_CAPACIDAD = 180;

const float MAXIMA_DISTANCIA_SEGURA = 50.0;
const float DISTANCIA_MEDIA = 100.0;
const float MAXIMA_DISTANCIA = 150.0;

const int HORA_MINIMA = 00;
const int HORA_MAXIMA = 23;
const int MINUTO_MINIMO = 00;
const int MINUTO_MAXIMO = 59;
const int HORA_MINIMA_APTA = 6;
const int HORA_MAXIMA_APTA = 19;

const char MATAFUEGOS = 'M';
const char ZARIGUEYAS = 'Z';
const char VACIO = 'V';

 typedef struct  {
        int hora;
        int minuto;
    } horario_t;


// Pre: -
// Post: Pregunta hasta que la respuesta ingresada sea válida.
int obtener_cantidad_pasajeros()
{
    int cantidad_pasajeros;
    printf("¿Cuántos pasajeros realizarán el viaje inaugural? ");
    scanf("%i", &cantidad_pasajeros);
    return cantidad_pasajeros;
}

// Pre: -
// Post: Pregunta hasta que la respuesta ingresada sea válida.
float obtener_distancia_frenado()
{
    float distancia_frenado;
    printf("¿Qué distancia recorrió el monorriel durante la prueba de los frenos marca Patito? ");
    scanf("%f", &distancia_frenado);
    return distancia_frenado;
}

// Pre: -
// Post: Pregunta hasta que la respuesta ingresada sea válida.


horario_t obtener_horario_programado()
{
    int hora;
    int minuto;
    
    printf("¿A qué hora está programado el viaje inaugural? (formato: hh:mm) ");
    scanf("%i:%i", &hora, &minuto);
    
    horario_t horario;
    horario.hora = hora;
    horario.minuto = minuto;
    return horario;
}

// Pre: -
// Post: Pregunta hasta que la respuesta ingresada sea válida.
char obtener_contenido_compartimiento()
{
    char contenido;
    printf("¿Qué encontró Marge en el compartimiento del matafuegos? \n");
    printf("[M] Matafuegos\n");
    printf("[Z] Familia de ZARIGUEYAS\n");
    printf("[V] Compartimiento vacío");
    scanf(" %c", &contenido);
    return contenido;
}

bool validar_ingreso_pasajeros(int cantidad_pasajeros)
{
    bool es_valido = true;
    if (0 < cantidad_pasajeros && cantidad_pasajeros <= MAXIMO_RANGO_PASAJEROS)
    {
        es_valido = false;
    }
    return es_valido;
}

bool validar_ingreso_distancia(float distancia_frenado)
{
    bool es_valido = false;
    if (0 < distancia_frenado && distancia_frenado <= MAXIMA_DISTANCIA)
    {
        es_valido = true;
    }
    return es_valido;
}

bool validar_ingreso_horario(horario_t horario)
{
    bool es_valido = false;
    if (horario.hora >= 0 && horario.minuto >= 0) {
        if ((HORA_MINIMA <= horario.hora || horario.hora <= HORA_MAXIMA) && (MINUTO_MINIMO <= horario.minuto || horario.minuto <= MINUTO_MAXIMO)) {
            es_valido = true;
        }
    }
    else {
        printf("Los valores ingresados no son válidos.");
    }
    return es_valido;
}

bool validar_ingreso_contenido(char contenido)
{
    bool es_valido = false;
    if (contenido == VACIO || contenido == ZARIGUEYAS || contenido == MATAFUEGOS)
    {
        es_valido = true;
    }
    return es_valido;
}

int asignar_puntos_distancia(float distancia_frenado)
{
    int puntos_distancia = 0;
    if (MAXIMA_DISTANCIA_SEGURA < distancia_frenado && distancia_frenado <= DISTANCIA_MEDIA)
    {
        puntos_distancia = -1;
    }
    else if (distancia_frenado > DISTANCIA_MEDIA)
    {
        puntos_distancia = -2;
    }
    return puntos_distancia;
}

int asignar_puntos_horario(horario_t horario)
{
    int puntos_horario = 0;
    if (horario.hora > HORA_MAXIMA_APTA || horario.hora < HORA_MINIMA_APTA)
    {
        puntos_horario = -3;
    }
    return puntos_horario;
}

int asignar_puntos_contenido(char contenido)
{
    int puntos_contenido = 1;
    if (contenido == ZARIGUEYAS)
    {
        puntos_contenido = -1;
    }
    else if (contenido == VACIO)
    {
        puntos_contenido = -3;
    }
    return puntos_contenido;
}

int calcular_puntaje(int puntaje_inicial, int puntos_pasajeros, int puntos_distancia, int puntos_horario, int puntos_contenido)
{
    int puntaje_final = puntaje_inicial + puntos_pasajeros + puntos_distancia + puntos_horario +puntos_contenido;
    if (puntaje_final >= PUNTAJE_MAXIMO)
    {
        puntaje_final = PUNTAJE_MAXIMO;
    }
    return puntaje_final;
}

int main()
{
    //int puntaje_inicial = 10; 

    int qtyPasajeros;
    bool continuarejecucion = false;
    bool condition ;
    do
    {
        // ingresar pasajeros
        qtyPasajeros = obtener_cantidad_pasajeros();

        // validar tipo y rango
        condition = validar_ingreso_pasajeros(qtyPasajeros);

    } while (condition); // condition es 1 a 250

    if (qtyPasajeros <= MAXIMO_CAPACIDAD)
    {
        continuarejecucion = true;
    }
    else{
        printf("-NO APTO-");
    }


    // sigo con el resto de las preguntas solo si "continuarejecucion=true"
    /*if (continuarejecucion)
    {
        printf("continuar ejecucion");
        do
        {
            preg 2
        } while (condition);

         do
        {
           

            preg 3
        } while (condition);

        do
        {
            // input valor
            // function validar
        } while (condition); 
    }*/

    return 0;
}
