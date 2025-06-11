// Definindo os pinos
const int pinoSolar = A0;    // Potenciômetro Solar
const int pinoConsumo = A1;  // Potenciômetro Consumo
const int ledSolar = 2;      // LED Verde (Solar)
const int ledRede = 3;       // LED Vermelho (Rede)
const int ledBateria = 4;    // LED Azul (Bateria/Modo)
const int pinoMotor = 5;     // Controle do Motor

// Variável de controle do modo
bool modoManual = false;

void setup() {
  // Configura os pinos
  pinMode(ledSolar, OUTPUT);
  pinMode(ledRede, OUTPUT);
  pinMode(ledBateria, OUTPUT);
  pinMode(pinoMotor, OUTPUT);
  
  // Inicia comunicação serial
  Serial.begin(9600);
  Serial.println("Sistema de Energia Inteligente");
  Serial.println("Comandos: ligar, desligar, auto, status");
}

void loop() {
  // Leitura dos sensores
  int solar = map(analogRead(pinoSolar), 0, 1023, 0, 100);
  int consumo = map(analogRead(pinoConsumo), 0, 1023, 0, 100);

  // Controle do modo automático
  if (!modoManual) {
    if (solar >= consumo * 0.7) {  // Se solar cobre 70% do consumo
      ativarModoSolar();
    } else {
      ativarModoRede();
    }
  }

  // Controle por serial
  if (Serial.available()) {
    processarComandoSerial();
  }
  
  // Atualiza o LED de modo
  digitalWrite(ledBateria, modoManual ? HIGH : LOW);
  
  delay(200);  // Pequeno delay para estabilidade
}

void ativarModoSolar() {
  digitalWrite(ledSolar, HIGH);
  digitalWrite(ledRede, LOW);
  digitalWrite(pinoMotor, HIGH);
  Serial.println("Modo AUTO: Energia Solar - Motor LIGADO");
}

void ativarModoRede() {
  digitalWrite(ledSolar, LOW);
  digitalWrite(ledRede, HIGH);
  digitalWrite(pinoMotor, LOW);
  Serial.println("Modo AUTO: Rede Elétrica - Motor DESLIGADO");
}

void processarComandoSerial() {
  String comando = Serial.readStringUntil('\n');
  comando.trim();
  comando.toLowerCase();

  if (comando == "ligar") {
    modoManual = true;
    digitalWrite(pinoMotor, HIGH);
    Serial.println("Motor LIGADO manualmente (Modo MANUAL)");
  } 
  else if (comando == "desligar") {
    modoManual = true;
    digitalWrite(pinoMotor, LOW);
    Serial.println("Motor DESLIGADO manualmente (Modo MANUAL)");
  }
  else if (comando == "auto") {
    modoManual = false;
    Serial.println("Modo AUTOMÁTICO ativado");
  }
  else if (comando == "status") {
    Serial.print("Solar: ");
    Serial.print(map(analogRead(pinoSolar), 0, 1023, 0, 100));
    Serial.print("% | Consumo: ");
    Serial.print(map(analogRead(pinoConsumo), 0, 1023, 0, 100));
    Serial.print("% | Modo: ");
    Serial.println(modoManual ? "MANUAL" : "AUTO");
  }
}