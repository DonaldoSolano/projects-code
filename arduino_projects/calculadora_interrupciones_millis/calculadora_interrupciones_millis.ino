enum calculadoraEstadosType { INIT_CAL, ESPERAR_OPERACION, ESPERAR_OPERANDO1, ESPERAR_OPERANDO2};
calculadoraEstadosType calculadoraST = INIT_CAL;


int32_t valor1 = 0;
int32_t valorResp = 0;
int32_t valor2 = 0;
int32_t operador = 0;
int32_t data;
void CalcularOp(void);




void CalcularOp()
{


  if (operador == '/')
  {
    valorResp = valor1 / valor2;

    Serial.println(valorResp);
  }
  else if (operador == '*')
  {
    valorResp = valor1 * valor2;
    Serial.println(valorResp);
  }
  else if (operador == '-')
  {
    valorResp = valor1 - valor2;
    Serial.println(valorResp);
  }
  else if (operador == '+')
  {
    valorResp = valor1 + valor2;
    Serial.println(valorResp);
  }

  valorResp = 0;
  operador = 0;
  data = 0;
  valor1 = 0;
  valor2 = 0;
  Serial.println("Ingrese operador:  ");
  calculadoraST = ESPERAR_OPERACION;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}



void loop() {
  // put your main code here, to run repeatedly:


  switch (calculadoraST) {
    case INIT_CAL:
      Serial.println("Ingrese operador:  ");
      calculadoraST = ESPERAR_OPERACION;
      break;

    case ESPERAR_OPERACION:

      if (Serial.available()) {
        data = Serial.read();
        if (data != '\n' && data == '/' || data == '*' || data == '+' || data == '-' ) {
          operador = data;
        }
        else {
          //TODO: inicializar todo para el nuevo estado
          valor1 = 0;
          //TODO: chequear que si tenga el operador en op
          calculadoraST = ESPERAR_OPERANDO1;
          Serial.println("Ingrese primer valor:  ");
        }

      }

      break;

    case ESPERAR_OPERANDO1:


      if (Serial.available()) {
        data = Serial.read();

        if (data != '\n' && data == '0' || data == '1' || data == '2' || data == '3' || data == '4' || data == '5' || data == '6' || data == '7' || data == '8' || data == '9')
        {
          valor1 *= 10;
          valor1 += data - '0';
        }
        else {
          valor2 = 0;
          Serial.println("Ingrese segundo valor:  ");
          calculadoraST = ESPERAR_OPERANDO2;

        }
      }

      break;

    case ESPERAR_OPERANDO2:


      if (Serial.available()) {
        data = Serial.read();

        if (data != '\n' && data == '0' || data == '1' || data == '2' || data == '3' || data == '4' || data == '5' || data == '6' || data == '7' || data == '8' || data == '9')
        {
          valor2 *= 10;
          valor2 += data - '0';
        }
        else {
          CalcularOp();

        }
      }

      break;


  }
}



