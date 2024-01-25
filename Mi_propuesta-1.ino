// Delcaración de Los Pines de los LED
byte led1 = 2;
byte led2 = 3;
byte led3 = 4;
byte led4 = 5;
byte led5 = 6;
byte led6 = 7;
byte led7 = 8;
byte led8 = 9;
byte Pizq = 10; // Pulzador Izquierda
byte Pder = 11; // Pulzador Derecha

int i;          // Variable del Contador del FOR
long vel = 40;  // Velocidad de las Luces
byte valor = 1; // Almacena el dato de los pulsadores

byte Ppwer = 12;                  // Pulsador Encendido/Apagado
int estado = 0, variable_val = 0; // Variables de cambio de esta on/off

void setup()
{
    // put your setup code here, to run once:
    // Configura los 8 Pines digitales como SALIDAS
    for (i = led1; i <= led8; i++)
    {
        pinMode(i, OUTPUT);
    }
    // Configura los PINES 10 y 11 Como Entradas
    pinMode(Pizq, INPUT);
    pinMode(Pder, INPUT);
    pinMode(Ppwer, INPUT);

    Serial.begin(9600);
}

void loop()
{
    /*
    lee si se ejucto el btn power y en base a ello se plantea lo siguiente:
    se guardar el estaod del btn y se pregunta si esta encendido "high" => 1
    si esta en 1 este cambiara el estado de variable_val en 1 y entra a realizar
    el comando de luces en secuencia.
        Si no pasa nada mandara un mensaje por comando de error
        (al notener dispositivo de camputara de error conectado)

     */
    estado = digitalRead(Ppwer);
    if (estado == HIGH)
    {
        variable_val = !variable_val; // de 0 pasa a 1
        delay(300);                   // tiempo de espera para no cambiar de estado varias veces
    }
    if (variable_val == HIGH)
    {
        Encendido_controller();
    }
    else
    {
        Errorprint();
    }
}

void Encendido_controller()
{
    // Si "valor" es Cero gire a la DERECHA
    if (valor == 0)
    {
        // Enciende los LED de Izquierda a Derecha
        for (i = led1; i <= led8 + 3; i++)
        {
            if (i <= led8)
            {
                digitalWrite(i, HIGH); // Enciende el LED
            }

            if (i > led3)
            {
                digitalWrite(i - 3, LOW); // Apaga el LED
            }
            delay(vel); // Retardo (Espera el valor de vel)

            // Lee los dos pulsadores
            if (digitalRead(Pizq))
            {
                valor = 1;
                i = led8 + 3; // Cambia el valor y sale del FOR
            }
            if (digitalRead(Pder))
            {
                valor = 0;
                i = led8 + 3; // Cambia el valor y sale del FOR
            }
        }
    }

    // Si "valor" es uno gire a la IZQUIERDA
    if (valor == 1)
    {
        // Enciende los LED de Izquierda a Derecha
        for (i = led8; i >= led1 - 3; i--)
        {
            if (i >= led1)
            {
                digitalWrite(i, HIGH); // Enciende el LED
            }

            if (i < led6)
            {
                digitalWrite(i + 3, LOW); // Apaga el LED
            }
            delay(vel); // Retardo (Espera el valor de vel)

            // Lee los dos pulsadores
            if (digitalRead(Pizq))
            {
                valor = 1;
                i = led1 - 3; // Cambia el valor y sale del FOR
            }
            if (digitalRead(Pder))
            {
                valor = 0;
                i = led1 - 3; // Cambia el valor y sale del FOR
            }
        }
    }
}
void Errorprint()
{
    // Serial.begin(9600); => se pone en el setup para mostrar print
    Serial.print("ERROR EN LA EJECUCION");
    exit;
}
