#include <LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


int dado; //variável que receberá os dados da porta serial
byte byteRead;

int sensorTemp = A2;
int lamp       = A0;
int led        = A1;
int pinMotor   = A5;
//
int pinR       = 6;
int pinG       = 9;
int pinB       = 10;
//

int valorR = 0;
int valorG = 0;
int valorB = 0;

float temperatura = 0;
int valorLido = 0;

String saida;
Servo servoMotor;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(lamp, OUTPUT); //define o pino o ledPin como saída
  pinMode(led, OUTPUT); //define o pino o ledPin como saída

  pinMode(pinR, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinB, OUTPUT);

  lcd.setCursor(0, 0);
  servoMotor.attach(pinMotor);
}

void loop() {

  valorLido = analogRead(sensorTemp);
  temperatura = (valorLido * 0.00488);
  temperatura = temperatura * 100;



  lcd.setCursor(0, 0);

  if (Serial.available() > 0)
  {
    saida = Serial.readStringUntil('\n');
    executaOperacao();
  }

  delay(1000);

  lcd.clear();

  Serial.println(temperatura);
  lcd.setCursor(0, 1);
  lcd.print("Temp.: ");
  lcd.print(temperatura);
  lcd.print(" C");

}


void executaOperacao() {



  if (saida.length() > 2) {

    if ((saida.charAt(0) == '#') && (saida.charAt(1) == '&')) {

      acendeLampada();

    } else if ((saida.charAt(0) == '#') && (saida.charAt(1) == '$')) {

      acionaMotor();

    } else if ((saida.charAt(0) == '#') && (saida.charAt(1) == '%')) {



      valorR = saida.substring(3, 6).toInt();
      valorG = saida.substring(7, 10).toInt();
      valorB = saida.substring(11, 14).toInt();

      acionaLeds();

    } else if ((saida.charAt(0) == '#') && (saida.charAt(1) == '>')) {

        lcd.setCursor(0, 0);
        lcd.print(saida.substring(2));
        delay(2000);
    }
  }
//  testaSaida();
  saida = "";

}

void  acionaLeds() {


  analogWrite(pinG, valorR);
  analogWrite(pinR, valorG);

  analogWrite(pinB, valorB);
  delay(500);
}

void acionaMotor() {

  String valorMtr = saida.substring(2);
  int valor =        valorMtr.toInt();


  int servoAngle = map(valor, 0, 180, 0, 180);

  servoMotor.write(servoAngle);

}

void acendeLampada() {

  if (saida.charAt(2) == 't') {

    digitalWrite(lamp, HIGH);

  } else if (saida.charAt(2) == 'f') {

    digitalWrite(lamp, LOW);

  }

}

void testaSaida() {

  Serial.println(saida.length());
  for (int i = 0; i < saida.length(); i++) {
    Serial.println( i ); Serial.println(saida.charAt(i));

  }

}


