
int counter = 0;
int tiemp=100;
int dist;
int estado = 1;
const int vel = 5;
bool sw = false;
bool motor_value, doblador_value, powercorte_value, poscorte_value;

#define stp_pin 2
#define sw_pin 3
#define motor 7
#define doblador 6
#define power_corte 5
#define pos_corte 4

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13,LOW);
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(stp_pin, INPUT);
  pinMode(sw_pin, INPUT);
  digitalWrite(sw_pin, HIGH);
  digitalWrite(stp_pin, HIGH);
 
  pinMode(motor, OUTPUT);
  pinMode(doblador, OUTPUT);
  pinMode(power_corte, OUTPUT);
  pinMode(pos_corte, OUTPUT);

  attachInterrupt(0,EmergencyStop,FALLING);
  //Serial.println("steps,botonEmergencia,energiaMotor,sensorFinCarrera,solenoideDoblador,energiaCorte,solenoideCorte");
  motor_value = LOW;  doblador_value = LOW; powercorte_value = LOW; poscorte_value = HIGH; 
}

void loop() {
  sw = toggleTrigger(sw,sw_pin);
  
  //sw = !digitalRead(encendido);
  
  if (sw == 1 && sw == true) {
    switch (estado) {
      case 1: //Estado Inicial
        motor_value = LOW;  doblador_value = LOW; powercorte_value = LOW; poscorte_value = HIGH; 
        tiemp = 10000;
        estado++;
        break;

      case 2:   //Mover varilla a estado inicial
        motor_value = HIGH;  doblador_value = LOW; powercorte_value = LOW; poscorte_value = HIGH; 
        dist = 5;
        tiemp = (dist/vel)*1000; 
        estado++;
        break;

      case 3: // Doblar
      case 6:
      case 9:
      case 16:
      case 19:
        motor_value = LOW;  doblador_value = HIGH; powercorte_value = LOW; poscorte_value = HIGH; 
        tiemp = 20000;
        estado++;
        break;

      case 4: // Retornar doblez
        motor_value = LOW;  doblador_value = LOW; powercorte_value = LOW; poscorte_value = HIGH;
        tiemp = 20000;
        estado++;
        break;

      case 5: // Iniciar Motor nuevamente 20cm
        motor_value = HIGH;  doblador_value = LOW; powercorte_value = LOW; poscorte_value = HIGH;
        dist = 25;
        tiemp = (dist/vel)*1000; 
        estado++;
        break;

      case 7:
      case 10:
      case 17:// Retornar doblez
        motor_value = LOW;  doblador_value = LOW; powercorte_value = LOW; poscorte_value = HIGH;
        tiemp = 20000;
        estado++;
        break;

      case 8: // Iniciar Motor 20cm
        motor_value = HIGH;  doblador_value = HIGH; powercorte_value = LOW; poscorte_value = HIGH;
        dist = 25;
        tiemp = (dist/vel)*1000;
        estado++;
        break;

      case 11: // Iniciar Motor 20cm
        motor_value = HIGH;  doblador_value = LOW; powercorte_value = LOW; poscorte_value = HIGH;
        dist = 25;
        tiemp = (dist/vel)*1000; 
        estado++;
        break;

      case 12: // Encender cortador
        motor_value = LOW;  doblador_value = LOW; powercorte_value = HIGH; poscorte_value = HIGH;
        tiemp = 20000;
        estado++;
        break;

      case 13: // Bajar Cortador
        motor_value = LOW;  doblador_value = LOW; powercorte_value = HIGH; poscorte_value = LOW;
        tiemp = 20000;
        estado++;
        break;

      case 14: // Apagar Cortador
        motor_value = LOW;  doblador_value = LOW; powercorte_value = LOW; poscorte_value = LOW;
        tiemp = 20000;
        estado++;
        break;

      case 15: // Subir Cortador
        motor_value = LOW;  doblador_value = LOW; powercorte_value = LOW; poscorte_value = HIGH;
        tiemp = 20000;
        estado++;
        break;

      case 18: // Iniciar motor 25 cm
        motor_value = HIGH;  doblador_value = LOW; powercorte_value = LOW; poscorte_value = HIGH;
        dist = 25;
        tiemp = (dist/vel)*1000; 
        estado++;
        break;

      default:
        estado = 1;
        sw = false;
        tiemp = 100;
        break;
        
    }

  }

  digitalWrite(motor, !motor_value);
  digitalWrite(doblador, !doblador_value);
  digitalWrite(power_corte, !powercorte_value);
  digitalWrite(pos_corte, !poscorte_value);
  
  Serial.print(motor_value);
  Serial.print(doblador_value);
  Serial.print(powercorte_value);
  Serial.print(poscorte_value);
  Serial.print(estado-1);
  Serial.println();
  delay(tiemp/10);
 
}

bool toggleTrigger(bool toggle_var, int trigger){

  if (digitalRead(trigger) == LOW){
    while (digitalRead(trigger) == LOW) 
      delay (10); 
    return !toggle_var;
  } 
  return toggle_var;
}
void EmergencyStop(){
  motor_value = HIGH;  doblador_value = LOW; powercorte_value = LOW; poscorte_value = HIGH;
  digitalWrite(motor, !motor_value);
  digitalWrite(doblador, !doblador_value);
  digitalWrite(power_corte, !powercorte_value);
  digitalWrite(pos_corte, !poscorte_value);
  
  digitalWrite(13,HIGH);
  while(1){;};
}

