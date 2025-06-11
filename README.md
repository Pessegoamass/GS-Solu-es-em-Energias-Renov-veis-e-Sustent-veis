# Sistema de Gerenciamento de Energia Residencial Inteligente

Solução IoT para priorização automática de fontes de energia (solar/rede) com controle por assistente virtual.

## Tecnologias Utilizadas
- **Hardware Simulado**:
  - Arduino Uno R3
  - Potenciômetros (sensores simulados)
  - LEDs indicadores
  - Motor DC (carga simulada)

- **Software**:
  - Tinkercad Circuits
  - Linguagem Arduino (C++)
 
## Como usar
- **Comandos**
  - ligar      # Ativa modo manual e liga motor
  - desligar   # Ativa modo manual e desliga motor
  - auto       # Retorna para modo automático
  - status     # Exibe dados do sistema

##  Arquitetura do Sistema
```mermaid
flowchart TB
    subgraph Inputs
        A[Potenciômetro Solar] -->|A0| C[Arduino]
        B[Potenciômetro Consumo] -->|A1| C
    end

    subgraph Outputs
        C -->|D2| D[LED Verde - Solar]
        C -->|D3| E[LED Vermelho - Rede]
        C -->|D5| F[Motor DC]
    end

    C --> G[Serial Monitor] <--> H[Assistente Virtual]
