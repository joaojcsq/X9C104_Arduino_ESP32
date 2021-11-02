/*
 * 
 * Programa para o CI x9c104. 
 * O x9c104 tem 100kOhms (10^4) e resolução de 1K por pulso (0 até 99).
 * O programa inicia zerando o CI (posição 0).
 * Comandos para usar na Serial:
 *                          a --> Aumenta a posição
 *                          d --> Diminui a posição
 *                          z --> Zera a posição
 *                          m --> Salva a posição na memória do CI
 * Programa criado por:
 *                         João Carlos
 *                         01/11/2021 13:56
 * 
*/

#define cs 3
#define ud 4
#define inc 5

char c = "";
byte i = 0, z = 0;

void zerar() {
  for (z = 0; z <= 100; z++) {
    diminuir();
  }
  Serial.println("##############");
  Serial.println("Reistor Zerado");
  Serial.println("##############");
}
void aumentar() {
  digitalWrite(cs, LOW);
  digitalWrite(ud, HIGH);
  digitalWrite(inc, HIGH);
  delay(10);
  digitalWrite(inc, LOW);
}
void diminuir() {
  digitalWrite(cs, LOW);
  digitalWrite(ud, LOW);
  digitalWrite(inc, HIGH);
  delay(10);
  digitalWrite(inc, LOW);
}
void memoria() {
  Serial.println("Gravando na memoria");
  digitalWrite(inc, HIGH);
  digitalWrite(cs, HIGH);
  delay(10);
  digitalWrite(cs, LOW);
}

void setup() {
  Serial.begin(9600);
  pinMode(cs, OUTPUT);
  pinMode(ud, OUTPUT);
  pinMode(inc, OUTPUT);
  /*
     Zerar resistor
  */
  zerar();
}

void loop() {

  if (Serial.available() > 0) {
    c = Serial.read();
    if ( c == 'm') {
      Serial.println("Salvando na memória");
      memoria();
    }
    if ( c == 'a') {
      if (i == 99) {
        i = 99;
      } else {
        i++;
      }
      Serial.print("Aumenta. Posição --> ");
      Serial.println(i);
      aumentar();
    }
    if ( c == 'd') {
      if (i == 0) {
        i = 0;
      } else {
        i--;
      }
      Serial.print("Diminui. Posição --> ");
      Serial.println(i);
      diminuir();
    }
    if ( c == 'z') {
      zerar();
      i = 0;
    }

  }

}
