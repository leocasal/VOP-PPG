//para ver el puerto COM donde se conectó el arduino, desde windows inicio ejecutar devmgmt.msc, y buscarlo en "puertos COM", conectando y desconectando arduino
bool serial_plotter = 0; //protocolo de envio de datos. 
//1 formato de envío para poder graficar con serial ploter de arduino. envia el 123 como el ascii de "1" "2" y "3", envia el 082 como "8" y "2" sin el cero. 
//0 envía los datos en formato byte. el 123 lo envia en un byte = 123
//en ambos, enviar el ascii de una coma despues de cada variable,  y ascii de '\n' al final
int Fs_Hz = 1400;    // Sampling frequency and execution time 
//con serial_plotter = 1, se alcanza 3200Hz con 1 sensor, 1700Hz con 2 sensores, 1100 con 3 sensores, DUEnative: 2500Hz 2 sens, MEGA 2000 2 sens
//con serial_plotter = 0, se alcanza 3500hz con 2 sensores llega , 3 sensores 2400 Hz, 4 sens 1800 Hz, DUEnative: 4000Hz 2 sens, MEGA 3400 2 sens
long Ts_us = 1000000/Fs_Hz;    // Sampling period in microsec 2400hz
//it takes about 100 us for analogRead(), so max fs is 10kHz
long executing_time_us = 0; //
//int state = 0; //
 //int value = 0;
 //int a = 0;
 int IN0 = 0; //señal de entrada analogica proveniente del Pulse sensor
 int IN1 = 0;
 int IN2 = 0;
 //int LAST_MAX=0;
 //int LAST_MIN=0;
 //float PWM =100;
 long TIMER_SEG_MAX=0;
 long TIMER_SEG_MIN=0;
 bool pin12 = LOW; //state for output at pin12 to measure execution time

// setup-----------------------------------
void setup() 
{
  //analogReadResolution(12);
  //pinMode(2, OUTPUT);
  //analogReference(INTERNAL);
  //analogReference(EXTERNAL); //connect aref to 3v3
  pinMode(12, OUTPUT); //output at pin12 to measure execution time
  pinMode(13, OUTPUT); // inboard LED, alarma cuando no logro execution time
  Serial.begin(250000);//115200);//250000);//9600);//multiples of 250k has minumum error for 16MHz arduino clock
}

// main loop-----------------------------------
void loop() 
{
  IN0 = analogRead(A0);
  IN1 = analogRead(A1);
  IN2 = analogRead(A2);//A2 NO ANDA CUANDO USAMOS LA LIBRERIA DE PULSESENSOR

if (serial_plotter) {
  //serial plotter protocol, convert digits to ascii, separating variable with comma
  Serial.print(IN0);
  Serial.print(",");
  Serial.print(IN1);
  Serial.print(",");
  Serial.print(IN2);
  //Serial.print(",");
  //Serial.print(PWM*4); //PWM max: 255 , x4 se obtiene mejor resolución
  //Serial.print(",");
  //Serial.print(900); //Enviamos un valor cte para que serial plotter no realice ajuste de escala
  Serial.print('\n'); //Fin envío datos
  }
else {
  //no serial plotter, transmit data as bytes
  Serial.write(highByte(IN0));
  Serial.write(lowByte(IN0));
  Serial.write(",");
  Serial.write(highByte(IN1));
  Serial.write(lowByte(IN1));

  Serial.write(",");
  Serial.write(highByte(IN2));
  Serial.write(lowByte(IN2));
  /*Serial.print(',');
  b = analogRead(A3);
  Serial.write(highByte(b));
  Serial.write(lowByte(b));*/
  Serial.print('\n');
 }


/*
analogWrite(5,PWM); //pwm solo en pines: 3,5,6,9,10,11
//Led saturación ON/OFF
digitalWrite(2, LOW);
if (IN0 > 900) {digitalWrite(3, HIGH);} //ON
else { digitalWrite(3, LOW);} //OFF
//if IN0 > LAST_MAX {
//  LAST_MAX=IN0;
//else
//}
if (IN0 > 900) { //Si saturó..?
  if (TIMER_SEG_MAX>2) { //Espero 2 seg. para realizar cambio
    TIMER_SEG_MAX=0; //Reseteo timer a 0
    PWM=PWM*0.9; //Reduzco 10% PWM
  }
}
// int LAST_MAX=0;  int LAST_MIN=0;
if (IN0 < 0) {  
  if (TIMER_SEG_MIN>4) {
    TIMER_SEG_MIN=0;
    PWM=PWM*1.1;
  }
}
//Limites PWM (max - min)
  if (PWM<0){PWM=0;}
  if (PWM>250){PWM=250;}
*/

//Timer sat
//use onboard led to flash at 1 sec
/*
TIMER_SEG_MAX = TIMER_SEG_MAX + (1/Fs_Hz);  
TIMER_SEG_MIN = TIMER_SEG_MIN + (1/Fs_Hz);  
if (TIMER_SEG_MIN<=1)  digitalWrite(13, LOW);   //turn off onboard led
if (TIMER_SEG_MIN>1)  digitalWrite(13, HIGH);   //turn on onboard led
if (TIMER_SEG_MIN>=2)  TIMER_SEG_MIN = 0;
*/

//set output at 1ms, to check execution time
if (pin12 == LOW) pin12 = HIGH;    
else              pin12 = LOW;
digitalWrite(12, pin12);   

//set fixed execution time----------------------------------------------------------------------------------------------------
//check if desired execution was exceeded. if so, turn on onboard led
  if (micros() - executing_time_us > Ts_us )     digitalWrite(13, HIGH);   //error!!! turn on onboard led
  else  digitalWrite(13, LOW);   //turn off on board led

  //Delay to ensure defined fixed execution time
  while (micros() - executing_time_us < Ts_us) {  }
  executing_time_us = micros()-2;//due 2khz-2   3.3 2k 16  15.7
 // digitalWrite(2, HIGH);
 }