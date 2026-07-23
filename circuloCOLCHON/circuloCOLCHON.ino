/**
 * Círculo: "EL COLCHÓN DE AIRE"
 * -----------------------------
 * Código para activar las bombas de aire que inflan las bolsas
 * tubulares y también las bombas que succionan el aire de las
 * bolsas para vaciarlas.
 */

#define PIN_INFLADOR_01 8
#define PIN_INFLADOR_02 10
#define PIN_INFLADOR_03 12
#define PIN_INFLADOR_04 13

#define PIN_ASPIRADOR_01 7
#define PIN_ASPIRADOR_02 6
#define PIN_ASPIRADOR_03 5
#define PIN_ASPIRADOR_04 4


#define MIN_PAUSA 1000
#define MAX_PAUSA 4000
#define MIN_INFLACION  3000
#define MAX_INFLACION  20000
#define MIN_ASPIRACION 3000
#define MAX_ASPIRACION 20000

#define MODO_PAUSA 0
#define MODO_INFLACION 1
#define MODO_ASPIRACION 2

#define RETARDO 100

int modo;
unsigned long tiempo_ini;
unsigned long tiempo_fin;


void setup() {
  // Definición de los pines
  pinMode(PIN_INFLADOR_01, OUTPUT);
  pinMode(PIN_INFLADOR_02, OUTPUT);
  pinMode(PIN_INFLADOR_03, OUTPUT);
  pinMode(PIN_INFLADOR_04, OUTPUT);

  pinMode(PIN_ASPIRADOR_01, OUTPUT);
  pinMode(PIN_ASPIRADOR_02, OUTPUT);
  pinMode(PIN_ASPIRADOR_03, OUTPUT);
  pinMode(PIN_ASPIRADOR_04, OUTPUT);

  pinMode(A5, OUTPUT);

  // Se inicia con la pausa mínima
  modo = MODO_PAUSA;
  tiempo_ini = millis(); + RETARDO;
  tiempo_fin = tiempo_ini + random(MIN_PAUSA, MAX_PAUSA);

  // Inicialización del puerto serial
  Serial.begin(9600);
  delay(1000);
  Serial.print("Iniciando el modo PAUSA - Duración=");
  Serial.println(tiempo_fin - tiempo_ini);
}


/**
 * Ciclo principal de ejecución
 */
void loop() {

  // MODO PAUSA
  // Simplemente se apagan todos los motores (bombas y succionadoras)
  // vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
  if (modo == MODO_PAUSA) {
    digitalWrite(PIN_INFLADOR_01, LOW);
    digitalWrite(PIN_INFLADOR_02, LOW);
    digitalWrite(PIN_INFLADOR_03, LOW);
    digitalWrite(PIN_INFLADOR_04, LOW);

    digitalWrite(PIN_ASPIRADOR_01, LOW);
    digitalWrite(PIN_ASPIRADOR_02, LOW);
    digitalWrite(PIN_ASPIRADOR_03, LOW);
    digitalWrite(PIN_ASPIRADOR_04, LOW);
    digitalWrite(A5, LOW);

    delay(RETARDO);

    if (millis() > tiempo_fin) {
      modo = MODO_INFLACION;
      tiempo_ini = millis() + RETARDO;
      tiempo_fin = tiempo_ini + random(MIN_INFLACION, MAX_INFLACION);
      Serial.print("Iniciando el modo INFLACIÓN - Duración=");
      Serial.println(tiempo_fin - tiempo_ini);
    }
  }

  // MODO INFLACIÓN
  // Se envía la señal al controlador Darlington para activar las
  // cuatro bombas. Al mismo tiempo, se apagan las succionadoras.
  // vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
  if (modo == MODO_INFLACION) {
    digitalWrite(PIN_INFLADOR_01, HIGH);
    digitalWrite(PIN_INFLADOR_02, HIGH);
    digitalWrite(PIN_INFLADOR_03, HIGH);
    digitalWrite(PIN_INFLADOR_04, HIGH);

    digitalWrite(PIN_ASPIRADOR_01, LOW);
    digitalWrite(PIN_ASPIRADOR_02, LOW);
    digitalWrite(PIN_ASPIRADOR_03, LOW);
    digitalWrite(PIN_ASPIRADOR_04, LOW);
    digitalWrite(A5, LOW);

    delay(RETARDO);

    if (millis() > tiempo_fin) {
      modo = MODO_ASPIRACION;
      tiempo_ini = millis() + RETARDO;
      tiempo_fin = tiempo_ini + random(MIN_ASPIRACION, MAX_ASPIRACION);
      Serial.print("Iniciando el modo ASPIRACIÓN - Duración=");
      Serial.println(tiempo_fin - tiempo_ini);
    }
  }

  // MODO ASPIRACIÓN
  // Se envía la señal al controlador Darlington para activar las
  // cuatro succionadoras. Al mismo tiempo, se apagan las bombas.
  // vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
  if (modo == MODO_ASPIRACION) {
    digitalWrite(PIN_INFLADOR_01, LOW);
    digitalWrite(PIN_INFLADOR_02, LOW);
    digitalWrite(PIN_INFLADOR_03, LOW);
    digitalWrite(PIN_INFLADOR_04, LOW);

    digitalWrite(PIN_ASPIRADOR_01, HIGH);
    digitalWrite(PIN_ASPIRADOR_02, HIGH);
    digitalWrite(PIN_ASPIRADOR_03, HIGH);
    digitalWrite(PIN_ASPIRADOR_04, HIGH);
    digitalWrite(A5, HIGH);

    delay(RETARDO);

    if (millis() > tiempo_fin) {
      modo = MODO_PAUSA;
      tiempo_ini = millis() + RETARDO;
      tiempo_fin = tiempo_ini + random(MIN_PAUSA, MAX_PAUSA);
      Serial.print("Iniciando el modo PAUSA - Duración=");
      Serial.println(tiempo_fin - tiempo_ini);
    }
  }
}
