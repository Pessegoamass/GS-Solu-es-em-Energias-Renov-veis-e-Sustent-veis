
# Diagrama de Arquitetura

## Componentes Principais
1. **Camada de Sensoriamento**:
   - Potenciômetro Solar (Entrada Analógica A0)
   - Potenciômetro Consumo (Entrada Analógica A1)

2. **Camada de Controle**:
   - Microcontrolador Arduino
   - Lógica de Priorização Energética
   - Sistema Modo Manual/Automático

3. **Camada de Atuação**:
   - LEDs Indicadores
   - Motor DC (Carga Simulada)

4. **Interface**:
   - Serial Monitor (Assistente Virtual Simulado)

## Fluxo de Dados
```mermaid
sequenceDiagram
    participant SensorSolar
    participant SensorConsumo
    participant Arduino
    participant Atuadores

    loop A cada 200ms
        SensorSolar->>Arduino: Valor energia solar
        SensorConsumo->>Arduino: Valor consumo
        Arduino->>Arduino: Processa priorização
        alt Modo Automático
            Arduino->>Atuadores: Aciona LEDs/Motor
        else Modo Manual
            Arduino->>Atuadores: Mantém estado definido
        end
    end
