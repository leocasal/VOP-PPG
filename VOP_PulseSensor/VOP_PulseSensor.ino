float Fs_Hz = 2000;    // Sampling frequency and execution time //hasta 3200 con 1 sensor, 1700 con 2 sensores, 1100 con 3 sensores 
//con el prograna q envia los bytes, con 2 sensores llega hasta 3500hz, 3 sensores 2400, 4 sens 1800
float Ts_us = 1000000/Fs_Hz;    // Sampling period in microsec 2400hz
long executing_time_us = 0; //
//int state = 0; //
 //int value = 0;
 //int a = 0;
 int IN0 = 0; //señal de entrada analogica proveniente del Pulse sensor
 int IN1 = 0;
 int IN2 = 0;
 int LAST_MAX=0;
 int LAST_MIN=0;
 float PWM =100;
 float TIMER_SEG_MAX=0;
 float TIMER_SEG_MIN=0;

int serial_plotter = 1; //formato de envio. 1 formato de envío de arduino para graficar con serial ploter. 0 envía en formato byte
// setup-----------------------------------
void setup() 
{
  pinMode(2, OUTPUT);
  pinMode(13, OUTPUT); // in board LED
  Serial.begin(250000);//115200);//250000);//9600);//multiples of 250k has minumum error for 16MHz arduino clock
  //; //flag para monitorear vel de ejecucion
}



// main loop-----------------------------------
void loop() 
{

//  digitalWrite(3, LOW); //start output minimum spent time for program
 // digitalWrite(2, LOW);// output total execution time for program
  IN0 = analogRead(A0);
  IN1 = analogRead(A1);
  IN2 = analogRead(A2);//A2 NO ANDA CUANDO USAMOS LA LIBRERIA DE PULSESENSOR

if (serial_plotter) {
  //serial plotter protocol, convert digits to ascii, separating variable with comma
  Serial.print(IN0);
  Serial.print(",");
  //Serial.print(IN1);
  //Serial.print(",");
  //Serial.print(IN2);
  //Serial.print(",");
  Serial.print(PWM*4); //PWM max: 255 , x4 se obtiene mejor resolución
  Serial.print(",");
  Serial.print(900); //Enviamos un valor cte para que serial plotter no realice ajuste de escala
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
  Serial.write(A2);
  Serial.write(A2);
  /*Serial.print(',');
  b = analogRead(A3);
  Serial.write(highByte(b));
  Serial.write(lowByte(b));*/
  Serial.print('\n');
 }

analogWrite(5,PWM); //pwm solo en pines: 3,5,6,9,10,11

//Led saturación ON/OFF
digitalWrite(2, LOW);
if (IN0 > 900) {digitalWrite(3, HIGH);} //ON
else { digitalWrite(3, LOW);} //OFF

//Timer sat
TIMER_SEG_MAX=TIMER_SEG_MAX+(1/Fs_Hz);  
TIMER_SEG_MIN=TIMER_SEG_MIN+(1/Fs_Hz);  

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


//set fixed execution time----------------------------------------------------------------------------------------------------
//check if desired execution was exceeded. if so, turn on onboard led
  digitalWrite(13, LOW);   //turn off on board led
  if (micros() - executing_time_us > Ts_us ) { 
    digitalWrite(13, LOW);   //error!!! turn on onboard led

    } 
  //Delay to ensure defined fixed execution time
  while (micros() - executing_time_us < Ts_us) {  }
  executing_time_us = micros();
 // digitalWrite(2, HIGH);
 }