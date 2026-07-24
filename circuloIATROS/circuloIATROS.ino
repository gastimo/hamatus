/**
 * Círculo: "LAS FALLAS DE IATROS"
 * -------------------------------
 * Código para controlar 2 motores "paso a paso" (PAP) unipolares
 * 28BYJ, responsables de hacer girar los ejes del círculo.
 */
 
// MOTOR 1 - Definición de pines
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
int M1_IN1 = 13;
int M1_IN2 = 12;
int M1_IN3 = 11;
int M1_IN4 = 10;

// MOTOR 2 - Definición de pines
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
int M2_IN1 = 9;
int M2_IN2 = 8;
int M2_IN3 = 7;
int M2_IN4 = 6;

// MOTOR 3 - Definición de pines
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
int M3_IN1 = 5;
int M3_IN2 = 4;
int M3_IN3 = 3;
int M3_IN4 = 2;

// MOTOR 3 - Definición de pines
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
int M4_IN1 = A5;
int M4_IN2 = A4;
int M4_IN3 = A3;
int M4_IN4 = A2;


// Demora entre pasos, no debe ser menor a 10ms (tiempo mínimo para energizar al motor)
int demora = 10;


// Matriz para realizar el "Paso Completo con Dos Bobinas"
// Estos pasos tienen mayor torque que el "pasoSimple" porque
// energiza dos bobinas a la vez.
int paso[4][4] = {
  {1, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 1},
  {1, 0, 0, 1}
};


/**
 * setup
 * Definición de los pines para energizar las bobinas del motor
 */
void setup() {
  pinMode(M1_IN1, OUTPUT);
  pinMode(M1_IN2, OUTPUT);
  pinMode(M1_IN3, OUTPUT);
  pinMode(M1_IN4, OUTPUT);

  pinMode(M2_IN1, OUTPUT);
  pinMode(M2_IN2, OUTPUT);
  pinMode(M2_IN3, OUTPUT);
  pinMode(M2_IN4, OUTPUT);

  pinMode(M3_IN1, OUTPUT);
  pinMode(M3_IN2, OUTPUT);
  pinMode(M3_IN3, OUTPUT);
  pinMode(M3_IN4, OUTPUT);

  pinMode(M4_IN1, OUTPUT);
  pinMode(M4_IN2, OUTPUT);
  pinMode(M4_IN3, OUTPUT);
  pinMode(M4_IN4, OUTPUT);
}

/**
 * loop
 * Ciclo principal de ejecución
 */
void loop() {
  rotacionEnPasos();
}

/**
 * rotacionEnPasos
 * Un ciclo requiere de 4 pasos. Hace rotar al motor siguiendo la definición de 
 * los pasos cargada en la matriz de 4x4.
 * PUNTOS A TENER EN CUENTA
 * - Un ciclo son los 4 pasos (matriz) que van energizando en secuencia las bobinas
 * - Un giro completo del rotor requiere 8 ciclos
 * - Un giro completo del eje exterior requiere de 64 vueltas del rotor, ya que el
 *   motor tiene varios engranajes que funcionan como reductores (por eso el eje
 *   del motor no está en el centro).
 * Entonces para una vuelta completa se requieren:
 *   4 ciclos x 8 x 64 = 2048
 */
void rotacionEnPasos() {
  for (int i = 0; i < 512; i++) {  // 512 * 4 (pasos del ciclo) = 2048 pasos
    for (int j = 0; j < 4; j++) {
      digitalWrite(M1_IN1, paso[j][0]);
      digitalWrite(M2_IN1, paso[j][0]);
      digitalWrite(M3_IN1, paso[j][0]);
      digitalWrite(M4_IN1, paso[j][0]);

      digitalWrite(M1_IN2, paso[j][1]);
      digitalWrite(M2_IN2, paso[j][1]);
      digitalWrite(M3_IN2, paso[j][1]);
      digitalWrite(M4_IN2, paso[j][1]);

      digitalWrite(M1_IN3, paso[j][2]);
      digitalWrite(M2_IN3, paso[j][2]);
      digitalWrite(M3_IN3, paso[j][2]);
      digitalWrite(M4_IN3, paso[j][2]);

      digitalWrite(M1_IN4, paso[j][3]);
      digitalWrite(M2_IN4, paso[j][3]);
      digitalWrite(M3_IN4, paso[j][3]);
      digitalWrite(M4_IN4, paso[j][3]);

      delay(demora);
    }
  }

}


