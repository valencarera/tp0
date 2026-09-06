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
// Post: Pregunta hasta que la respuesta ingresada sea válida.
int obtener_cantidad_pasajeros() {
    int cantidad_pasajeros;
    printf("¿Cuántos pasajeros realizarán el viaje inaugural? (1-250)\n");
    printf("%s", SU_RESPUESTA);
    scanf("%i", &cantidad_pasajeros);
    return cantidad_pasajeros;
}

// Pre: -
// Post: Pregunta hasta que la respuesta ingresada sea válida.
float obtener_distancia_frenado() {
    float distancia_frenado;
    printf("¿Qué distancia recorrió el monorriel durante la prueba de los frenos marca Patito? (1-150)\n");
    printf("%s", SU_RESPUESTA);
    scanf("%f", &distancia_frenado);
    return distancia_frenado;
}

// Pre: -
// Post: Pregunta hasta que la respuesta ingresada sea válida.
horario_t obtener_horario_programado() {
    int hora;
    int minuto;
    
    printf("¿A qué hora está programado el viaje inaugural? (formato: hh:mm)\n");
    printf("%s", SU_RESPUESTA);
    scanf("%i:%i", &hora, &minuto);
    
    horario_t horario;
    horario.hora = hora;
    horario.minuto = minuto;

    return horario;
}

// Pre: -
// Post: Pregunta hasta que la respuesta ingresada sea válida.
char obtener_contenido_compartimiento() {
    char contenido;
    printf("¿Qué encontró Marge en el compartimiento del matafuegos?\n");
    printf("Ingresar respuesta en mayúsculas.\n");
    printf("[M] Matafuegos\n");
    printf("[Z] Familia de zarigüeyas\n");
    printf("[V] Compartimiento vacío\n");
    printf("%s", SU_RESPUESTA);
    scanf(" %c", &contenido);
    return contenido;
}

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

int asignar_puntos_distancia(float distancia_frenado) {
    int puntos_distancia = 0;
    if (MAXIMA_DISTANCIA_SEGURA < distancia_frenado && distancia_frenado <= DISTANCIA_MEDIA) {
        puntos_distancia = -1;
    }
    else if (distancia_frenado > DISTANCIA_MEDIA) {
        puntos_distancia = -2;
    }
    return puntos_distancia;
}

int asignar_puntos_horario(horario_t horario) {
    int puntos_horario = 0;
    if (horario.hora > HORA_MAXIMA_APTA || horario.hora < HORA_MINIMA_APTA) {
        puntos_horario = -3;
    }
    return puntos_horario;
}

int asignar_puntos_contenido(char contenido) {
    int puntos_contenido = 1;
    if (contenido == ZARIGUEYAS) {
        puntos_contenido = -1;
    }
    else if (contenido == VACIO) {
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
