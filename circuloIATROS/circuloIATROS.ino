// Pines de Arduino que controlan las bobinas del motor
int IN1 = 8;
int IN2 = 9;
int IN3 = 10;
int IN4 = 11;

// Demora entre pasos, no debe ser menor a 10ms (tiempo mínimo para energizar al motor)
int demora = 12;


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
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
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
      digitalWrite(IN1, paso[j][0]);
      digitalWrite(IN2, paso[j][1]);
      digitalWrite(IN3, paso[j][2]);
      digitalWrite(IN4, paso[j][3]);
      delay(demora);
    }
  }

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(5000);
}


