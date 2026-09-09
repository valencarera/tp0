#include <stdio.h>
#include <stdbool.h>

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

const char *ESTADO_A = "APTO";
const char *ESTADO_RR = "REQUIERE REVISION";
const char *ESTADO_NA = "NO APTO";

typedef struct horario {
    int hora;
    int minuto;
} horario_t;

const char *SU_RESPUESTA = "Su respuesta es: ";

// Pre: -
// Post: Pide al usuario la cantidad de pasajeros que realizarán el viaje inaugural y lo devuelve.
void obtener_cantidad_pasajeros(int *cantidad_pasajeros) {
    printf("¿Cuántos pasajeros realizarán el viaje inaugural? (1-250)\n");
    printf("%s", SU_RESPUESTA);
    scanf("%i", &cantidad_pasajeros);
}

// Pre: -
// Post: Pide al usuario la distancia de frenado y la devuelve.
void obtener_distancia_frenado(float *distancia_frenado) {
    printf("¿Qué distancia recorrió el monorriel durante la prueba de los frenos marca Patito? (1-150)\n");
    printf("%s", SU_RESPUESTA);
    scanf("%f", &distancia_frenado);
}

// Pre: -
// Post: Pide al usuario el horario programado y lo devuelve.
void obtener_horario_programado(horario_t *horario) { // VOID
    int hora;
    int minuto;
    
    printf("¿A qué hora está programado el viaje inaugural? (formato: hh:mm)\n");
    printf("%s", SU_RESPUESTA);
    scanf("%i:%i", &hora, &minuto);
    
    horario_t horario;
    *horario->hora = hora;
    *horario->minuto = minuto;
}

// Pre: -
// Post: Pide al usuario el contenido del compartimiento y lo devuelve.
char obtener_contenido_compartimiento(char *contenido) { 
    printf("¿Qué encontró Marge en el compartimiento del matafuegos?\n");
    printf("Ingresar respuesta en mayúsculas.\n");
    printf("[M] Matafuegos\n");
    printf("[Z] Familia de zarigüeyas\n");
    printf("[V] Compartimiento vacío\n");
    printf("%s", SU_RESPUESTA);
    scanf(" %c", &contenido);
}

// Pre: -
// Post: Valida que la cantidad de pasajeros ingresada esté entre 0 y MAXIMO_RANGO_PASAJEROS.
bool validar_ingreso_pasajeros(int cantidad_pasajeros) {
    bool es_valido = true;
    if (0 < cantidad_pasajeros && cantidad_pasajeros <= MAXIMO_RANGO_PASAJEROS) {
        es_valido = false;
    }
    else {
        printf("El valor ingresado no está dentro del rango válido.\n");
    }
    return es_valido;
}

// Pre: -
// Post: Valida que la distancia de frenado ingresada esté entre 0 y MAXIMA_DISTANCIA.
bool validar_ingreso_distancia(float distancia_frenado) {
    bool es_valido = true;
    if (0 < distancia_frenado && distancia_frenado <= MAXIMA_DISTANCIA){
        es_valido = false;
    }
    else {
        printf("El valor ingresado no está dentro del rango válido.\n");
    }
    return es_valido;
}

// Pre: -
// Post:
// Valida que la hora esté entre HORA_MINIMA y HORA_MAXIMA.
// Valida que el minuto esté entre MINUTO_MINIMO y MINUTO_MAXIMO.
bool validar_ingreso_horario(horario_t horario) {
    bool es_valido = true;
    if (horario.hora >= 0 && horario.minuto >= 0) {
        if ((HORA_MINIMA <= horario.hora && horario.hora <= HORA_MAXIMA) && (MINUTO_MINIMO <= horario.minuto && horario.minuto <= MINUTO_MAXIMO)) {
            es_valido = false;
        }
    }
    else {
        printf("El horario ingresado no tiene un formato válido.");
    }
    return es_valido;
}

// Pre: -
// Post: Valida que el contenido ingresado sea uno de los valores válidos(VACIO, ZARIGUEYAS, MATAFUEGOS).
bool validar_ingreso_contenido(char contenido) {
    bool es_valido = true;
    if (contenido == VACIO || contenido == ZARIGUEYAS || contenido == MATAFUEGOS) {
        es_valido = false;
    }
    else {
        printf("La respuesta ingresada no es válida. Ingresar M, Z o V.\n");
    }
    return es_valido;
}

// Pre: distancia_frenado debe estar entre 0 y MAXIMA_DISTANCIA.
// Post:
// Devuelve puntos_distancia = 0 si la distancia de frenado es menor o igual a MAXIMA_DISTANCIA_SEGURA.
// Devuelve puntos_distancia = -1 si la distancia de frenado está entre MAXIMA_DISTANCIA_SEGURA y DISTANCIA_MEDIA.
// Devuelve puntos_distancia = -2 si la distancia de frenado es mayor a DISTANCIA_MEDIA.
int asignar_puntos_distancia(float *distancia_frenado) {
    int puntos_distancia = 0;
    if (MAXIMA_DISTANCIA_SEGURA < *distancia_frenado && *distancia_frenado <= DISTANCIA_MEDIA) {
        puntos_distancia = -1;
    }
    else if (*distancia_frenado > DISTANCIA_MEDIA) {
        puntos_distancia = -2;
    }
    return puntos_distancia;
}

// Pre: horario.hora debe estar entre HORA_MINIMA y HORA_MAXIMA.
// Post:
int asignar_puntos_horario(horario_t *horario) {
    int puntos_horario = 0;
    if (horario->hora > HORA_MAXIMA_APTA || horario->hora < HORA_MINIMA_APTA) {
        puntos_horario = -3;
    }
    return puntos_horario;
}

int asignar_puntos_contenido(char *contenido) {
    int puntos_contenido = 1;
    if (*contenido == ZARIGUEYAS) {
        puntos_contenido = -1;
    }
    else if (*contenido == VACIO) {
        puntos_contenido = -3;
    }
    return puntos_contenido;
}

int calcular_puntaje(int puntaje_inicial, int puntos_distancia, int puntos_horario, int puntos_contenido) {
    int puntaje_final = puntaje_inicial + puntos_distancia + puntos_horario + puntos_contenido;
    if (puntaje_final >= PUNTAJE_MAXIMO) {
        puntaje_final = PUNTAJE_MAXIMO;
    }
    return puntaje_final;
}

const char *asignar_estado(int puntaje_final) {
    const char *estado;
    if (puntaje_final >= 0 && puntaje_final <= 4) {
        estado = ESTADO_NA;
    }
    else if (puntaje_final >= 5 && puntaje_final <= 7) {
        estado = ESTADO_RR;
    }
    else {
        estado = ESTADO_A;
    }
    return estado;
}

int main() {
    int cantidad_pasajeros;
    horario_t horario;
    float distancia_frenado;
    char contenido ;

    bool continuar = false;
    bool condicion;

    int puntaje_final = 0;
    int puntaje_inicial = 10; 
    int puntos_distancia = 0;
    int puntos_horario = 0;
    int puntos_contenido = 0;

    const char *estado;

    do {
        cantidad_pasajeros = obtener_cantidad_pasajeros();
        condicion = validar_ingreso_pasajeros(cantidad_pasajeros);
    } while (condicion); // condition es 1 a 250

    if (cantidad_pasajeros <= MAXIMO_CAPACIDAD) {
        continuar = true;
    }
    else {
        printf("-%s-\n", ESTADO_NA);
    }

    if (continuar) {
        do {
            distancia_frenado = obtener_distancia_frenado();
            condicion = validar_ingreso_distancia(distancia_frenado);
            puntos_distancia = asignar_puntos_distancia(distancia_frenado);
            printf("puntos distancia: %i\n", puntos_distancia);
        } while (condicion);

        do {
            horario = obtener_horario_programado();
            condicion = validar_ingreso_horario(horario);
            puntos_horario = asignar_puntos_horario(horario);
            printf("puntos horario: %i\n", puntos_horario);
        } while (condicion);

        do {
            contenido = obtener_contenido_compartimiento();
            condicion = validar_ingreso_contenido(contenido);
            puntos_contenido = asignar_puntos_contenido(contenido);
            printf("puntos contenido: %i\n", puntos_contenido);
        } while (condicion);

        puntaje_final = calcular_puntaje(puntaje_inicial, puntos_distancia, puntos_horario, puntos_contenido);
        estado = asignar_estado(puntaje_final);

        printf("Con las respuestas brindadas, su puntaje final es %i.\nEl estado de la inspección de seguridad del monorriel es: -%s-\n", puntaje_final, estado);
    }
    return 0;
}
