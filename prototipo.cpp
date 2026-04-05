/*
 * PLANTAYA LED - Prototipo
 
 */

// Pines
const int sensorPin = A0;
const int pinRojo = 9;
const int pinVerde = 10;
const int pinAzul = 11;

// Umbrales (ajustar según calibración)
const int SATURACION = 150;
const int OPTIMO = 350;
const int LIGERO = 500;
const int MODERADO = 650;
const int MUY_SECO = 800;

int humedad = 0;
unsigned long tiempoParpadeo = 0;
bool parpadeo = false;

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(pinRojo, OUTPUT);
  pinMode(pinVerde, OUTPUT);
  pinMode(pinAzul, OUTPUT);
  apagar();
  Serial.begin(9600);
  Serial.println("PLANTAYA LED iniciado");
}

void loop() {
  humedad = analogRead(sensorPin);
  Serial.print("Humedad: ");
  Serial.println(humedad);
  
  if (humedad <= SATURACION) {
    morado();
  } else if (humedad <= OPTIMO) {
    verde();
  } else if (humedad <= LIGERO) {
    azul();
  } else if (humedad <= MODERADO) {
    amarillo();
  } else if (humedad <= MUY_SECO) {
    naranja();
  } else {
    rojoParpadeante();
  }
  
  delay(1000);
}

void apagar() {
  digitalWrite(pinRojo, LOW);
  digitalWrite(pinVerde, LOW);
  digitalWrite(pinAzul, LOW);
}

void morado() {
  digitalWrite(pinRojo, HIGH);
  digitalWrite(pinVerde, LOW);
  digitalWrite(pinAzul, HIGH);
}

void verde() {
  digitalWrite(pinRojo, LOW);
  digitalWrite(pinVerde, HIGH);
  digitalWrite(pinAzul, LOW);
}

void azul() {
  digitalWrite(pinRojo, LOW);
  digitalWrite(pinVerde, LOW);
  digitalWrite(pinAzul, HIGH);
}

void amarillo() {
  digitalWrite(pinRojo, HIGH);
  digitalWrite(pinVerde, HIGH);
  digitalWrite(pinAzul, LOW);
}

void naranja() {
  analogWrite(pinRojo, 200);
  digitalWrite(pinVerde, LOW);
  digitalWrite(pinAzul, LOW);
}

void rojoParpadeante() {
  unsigned long ahora = millis();
  if (ahora - tiempoParpadeo >= 300) {
    tiempoParpadeo = ahora;
    parpadeo = !parpadeo;
    if (parpadeo) {
      analogWrite(pinRojo, 255);
    } else {
      digitalWrite(pinRojo, LOW);
    }
    digitalWrite(pinVerde, LOW);
    digitalWrite(pinAzul, LOW);
  }
}