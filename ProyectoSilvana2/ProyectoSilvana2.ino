#define emergencia_pin 2
#define btnInicio_pin 3

//Entrada
#define motor_pin 4
#define doblador_pin 5
#define pwrCorte_pin 6
#define posCorte_pin 7

//Salida
#define sFinCarrera_pin 8

//Casos
#define c_PuntoInicial 0
#define c_AltoTotal 0
#define c_RetornaDoblez 0
#define c_SubeCortadoraOFF 0

#define c_IniciaMotor 1
#define c_IniciaDoblez 2
#define c_InicaCortadora 3
#define c_BajaCortadora 4
#define c_ApagaCortadoraDOWN 5

#define OFF HIGH
#define ON LOW

#define UP LOW
#define DOWN HIGH



bool motor, doblador, pwrCorte, posCorte, sFinCarrera, emergencia, btnInicio;
bool LED = false;

void setup() {
  //inicialización
   pinMode(13, OUTPUT);
  digitalWrite(13,LOW);
  pinMode(emergencia_pin, INPUT_PULLUP);
  digitalWrite(emergencia_pin, HIGH);
  //attachInterrupt(digitalPinToInterrupt(emergencia_pin), subEmergencia, FALLING);

  pinMode(motor_pin, OUTPUT);
  pinMode(doblador_pin, OUTPUT);
  pinMode(pwrCorte_pin, OUTPUT);
  pinMode(posCorte_pin, OUTPUT);

  pinMode(sFinCarrera_pin, INPUT_PULLUP);
  digitalWrite(sFinCarrera_pin, OFF);

  motor = OFF;
  doblador = OFF;
  pwrCorte = OFF;
  posCorte = UP;

  sFinCarrera = digitalRead(sFinCarrera_pin);

}
#define time_constant 10000
#define time_motor 3500
void loop() {
  
  // put your main code here, to run repeatedly:
  caso(c_AltoTotal);
  delay(time_constant);
  caso(c_IniciaDoblez);
  delay(time_constant);
  caso(c_RetornaDoblez);
  delay(time_constant);
  caso(c_IniciaMotor);
  delay(time_motor);
  /*  while (sFinCarrera == OFF) {  sFinCarrera = digitalRead(sFinCarrera_pin);}  */
  sFinCarrera = OFF;
  caso(c_AltoTotal);
  delay(3000);
  caso(c_IniciaDoblez);
  delay(time_constant);
  caso(c_RetornaDoblez);
  delay(time_constant);
  caso(c_InicaCortadora);
  delay(time_constant);
  caso(c_BajaCortadora);
  delay(time_constant);
  caso(c_ApagaCortadoraDOWN);
  delay(time_constant);
  caso(c_SubeCortadoraOFF);
  delay(time_constant);
  caso(c_IniciaMotor);
  delay(time_motor);
  /*  while (sFinCarrera == OFF) {  sFinCarrera = digitalRead(sFinCarrera_pin);}  */
  sFinCarrera = OFF;
  caso(c_IniciaDoblez);
  delay(time_constant);
  caso(c_RetornaDoblez);
  delay(time_constant);
  caso(c_IniciaMotor);
  delay(time_motor);
  /*  while (sFinCarrera == OFF) {  sFinCarrera = digitalRead(sFinCarrera_pin);}  */
  sFinCarrera = OFF;
  caso(c_IniciaDoblez);
  delay(time_constant);
  caso(c_RetornaDoblez);
  delay(time_constant);
  caso(c_AltoTotal);
  delay(time_constant);



  while (1) {
        digitalWrite(13, !LED);};

}

void subEmergencia() {
  caso(c_AltoTotal);

  pinMode(13, OUTPUT);

  while (1) {
    digitalWrite(13, !LED);
    LED = !LED;
    delay(30000);
  }
}

void caso(int valor) {
  switch (valor) {
    case 0: // c_AltoTotal c_RetornaDoblez c_SubeCortadoraOFF
      motor = OFF;
      doblador = OFF;
      pwrCorte = OFF;
      posCorte = UP;
      break;
    case 1: // c_IniciaMotor
      motor = ON;
      doblador = OFF;
      pwrCorte = OFF;
      posCorte = UP;
      break;
    case 2: // c_IniciaDoblez
      motor = OFF;
      doblador = ON;
      pwrCorte = OFF;
      posCorte = UP;
      break;
    case 3: // c_InicaCortadora
      motor = OFF;
      doblador = OFF;
      pwrCorte = ON;
      posCorte = UP;
      break;
    case 4: // c_BajaCortadora
      motor = OFF;
      doblador = OFF;
      pwrCorte = ON;
      posCorte = DOWN;
      break;
    case 5: // c_ApagaCortadoraDOWN
      motor = OFF;
      doblador = OFF;
      pwrCorte = OFF;
      posCorte = DOWN;
      break;
  }
  digitalWrite(motor_pin, motor);
  digitalWrite(doblador_pin, doblador);
  digitalWrite(pwrCorte_pin, pwrCorte);
  digitalWrite(posCorte_pin, posCorte);
  
}
