<!-----

Yay, no errors, warnings, or alerts!

Conversion time: 1.028 seconds.


Using this Markdown file:

1. Paste this output into your source file.
2. See the notes and action items below regarding this conversion run.
3. Check the rendered output (headings, lists, code blocks, tables) for proper
   formatting and use a linkchecker before you publish this page.

Conversion notes:

* Docs to Markdown version 1.0β34
* Tue Oct 10 2023 09:58:19 GMT-0700 (PDT)
* Source doc: arduino VOP - pulse sensor - guia de instalacion, adquisición, uso (instructivo)
----->


**FIRMWARE**

install arduino ide

elegir placa arduino uno y puerto com adecuado

compilar/verify y luego grabar programa arduiino

conectar serial plotter y ver que efectivamente adquiere (los datos deben enviarse en protocolo serial plotter)

para graficar mas tiempo y ver las señales de ppg, se debe aumentar las muestras de arduino plotter, editando este archivo `main.35ae02cb.chunk.js` ubicado en


```
C:\Program Files\Arduino IDE\resources\app\node_modules\arduino-serial-plotter-webapp\build\static\js\
```


reemplazar `U=Object(o.useState)(50)` with `U=Object(o.useState)(2500)` para una frec de muestreo de 2000hz

**PYTHON (adquirir y guardar)**

descargar compilador de python anaconda, que inclouye jupyter notebook (a diferencia de google collab, se debe usar un compilador local para conectarse a l puerto serie)

**ejecutar “Jupyter notebook” **y copiar direccion en algun explorador.

buscar y abrir archivo python Adquisicion_arduino.ipynb

pip install pyserial #en una nueva planilla o reiniciando el kernel (para el error no module named serial)if 

cerrar arduino id plotter y monitor, para tener acceso al puerto serie

crear la carpeta /datos para que lo pueda guardar aui

en firmware.ino elegir opcion serial_plotter = 0, para que envie los datos sin formato plotter

**procesamiento**

buscar y abrir archivo python procesamiento_arduino.ipynb

------------------------------------------------------

prueba_puerto_serie-PulseSensor-Copy5.ipynb

arduino.close()

des

**abrir **

**#agregar led q indica qie esta saturando sensor y corregir luz led**

**#agregar potenciometro a led para ajustar luz R1 470 ohm, **

**1) agregar pote entre led y 5v**

**2) agregar cable para alimentar led con una salida del pwm, o pote**

**guia de instalacion**

procesar señales

arduino uno permite hasta 115000 bauds

pulsesensor implementa su serial communcation aparentemente para transmitir mas rapido

solo se pueden usar baudrate fijo, 250000 en alternativo

si usamos 3 sensores y fsample = 2000 khz, aduquiere un tiempo incorrecto, y mayor

probar usar el programa no alternativo porque usa interrupciones para manejar el tiempo

si usamos 2 sensores y 500hz, da 12.5 bytes por sampleo y transmitios 9 bytes. al aghregar 1 sensor, aparece el problema de comunicacion???

para verificar si la frec de sampleo es correcta, prender y apagar una salida digital en cada tiempo de sampleo y medir con el osciloscopio

**FIRMWARE**

install arduino ide

install library pulse sensor (desde arduino ide)

connect arduino board, download firmware

set vel baud serial 115000 250000 segun corresponda

`const byte SAMPLES_PER_SERIAL_SAMPLE = 1; `%tiene q estar en 1 para la comunicacion

elegir frec de muestreo, para 2kHz = 2/4 * 1000L, para 500 Hz 2* 1000L, editando el archivo fuente de la libreria: 

C:\Users\Leonardo Casal\Documents\Arduino\libraries\PulseSensor_Playground\src


```
static const unsigned long MICROS_PER_READ = (2/4 * 1000L); // usecs per sample.
```


arduino nano: elegir puerto, placa nano y “herramienta”-> “procesador”->”old bootloader” 


---

**HARDWARE**

no connectar a2 de arduino poruque no adquiere (cuando esta la libreria pulsensor)

connect a0 (`const int PULSE_INPUT0 = A0;`), 5v y gnd a la placa arduino UNO + pulse sensor

connect a1

connect a3

mcp6001 1.8V - 6V

Si alimento con un potenciometro, sigue saturando pero en valores de cuentas mas bajo. a 5V, satura en 950 aprox, en 3V 550, y en 2.5V deja de saturar con 450 cuentas. esto se debe a q al bajar la luz del led, también baja la tension de alimentacion del amplificador, que debe tener una salida ratiometrica

el circuito analogico esta en una configuración tipo pasabanda de segundo orden. es no convencional, es decir no es butter, etc etc


---

**ADQUIRIR / Visualizar**

protocolo de comunicación? orden de los bytes 

44 (COMA) 

ASCII_BYTE1_SIGNAL1

ASCII_BYTE2_SIGNAL1

ASCII_BYTE3_SIGNAL1

13 (CARRIAGE RETURN) 

10 (LINEFEED) 

ASCII_BYTE1_SIGNAL2 

ASCII_BYTE2_SIGNAL2 

ASCII_BYTE3_SIGNAL213

**medir con 4 a la vez sensores**

**CON PYTHON**

ejecutar Jupyter notebook Anaconda, y copiar direccion en algun explorador.

buscar prueba_puerto_serie-PulseSensor-Copy5.ipynb

arduino.close()

CERRAR/DESCONECTAR ARDUINO SERIAL MONITO PLOTTER

ver si diego corre ipynb y ve puertos desde colab NO

ver en mi pc como adquirir datos con anaconda PENDIENTE

**con arduino plotter y visualizar**

arduino plotter tiene q recibir los datos en ascii, separados por coma para diferentes variables y al final un carriage return

la desventaja es que generalmente transmite una cantidad variable de  bytes (entre 1 y 4 bytes por señal ademas de la coma) ya que convierte la variable medida (por ej int +-1024) en cada caracter a ascii (por ej 24-> “2” y “4”, -306-> “-”, “3”,”0” y “6”, 1008 -> “1”,”0”, “0” y “4”)

si se transmite la variable sin convertir a ascii, la cant de bytes transmitios sera optima (menor en este caso) ya que se transmite la misma cant de bytes que el tamaño de la variable. por ej para int +-1024 serán 3 bytes (10 bits + 1 de signo)

connect serial monitor o plotter

para graficar mas tiempo: aumentar las muestras de arduino plotter:

The package can be found in the installation folder of Arduino IDE


```
C:\Program Files\Arduino IDE\resources\app\node_modules\arduino-serial-plotter-webapp\build\static\js\
```


`main.35ae02cb.chunk.js` 

can be modified to change values threshold value, need to replace `U=Object(o.useState)(50)` with `U=Object(o.useState)(5000)` it will increase maximum data points to 5000.

y cambiar en el firmware de 1 a 10 o 100


```
const byte SAMPLES_PER_SERIAL_SAMPLE = 1;

para visualizar mas cantidad de datos (mayor longitud temporal), usar const byte SAMPLES_PER_SERIAL_SAMPLE = 10;
```


**con matlab**


---

**PROCESAMIENTO CON PYTHON**

subir adquisiciones

