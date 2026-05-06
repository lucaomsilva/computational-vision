# System Architecture

| Metadado            | Detalhe                                                |
| :------------------ | :----------------------------------------------------- |
| **Projeto**         | Sistema de Controle de Estoque com Visão Computacional |
| **ID do Documento** | SCEVC-DOC-002                                          |
| **Versão**          | 0.1                                                    |
| **Status**          | Rascunho                                                 |
| **Data**            | 05/05/2026                                             |
| **Hardware**        | ESP32-CAM + PC                                         |
| **Stack:**          | C/C++ (ESP32 para Processamento) + UI Viewer no PC     |

---

## 1. Visão Geral (C4 Context Diagram)

O diagrama abaixo ilustra o contexto de alto nível do sistema e suas interações com a inteligência na borda (Edge Computing).

```mermaid
graph TD
    User((Operador))
    
    subgraph "Prateleira / Estoque"
        Camera[ESP32-CAM<br/>Sensor OV2640<br/>Processamento Interno]
    end

    subgraph "Central de Controle"
        PC[PC Viewer<br/>Dashboard UI]
    end

    %% Relações
    Camera <-->|Wi-Fi / HTTP - Imagens + Status| PC
    PC -->|Exibe Monitor e Alertas| User
```

## 2. Arquitetura de Hardware

- **Dispositivo de Captura e Borda**: Módulo ESP32-CAM equipado com câmera OV2640. Toda a lógica de visão computacional ocorre aqui, aproveitando os 4MB de PSRAM para alocação do frame original e dos *buffers* de diferença.
- **Processamento Central (Dashboard)**: PC Genérico atuando puramente como cliente HTTP para buscar o estado ("Item Ausente"/"Presente") e as imagens resultantes para visualização humana.
- **Rede**: Ponto de Acesso Wi-Fi local para comunicação TCP/IP na porta 80.

```mermaid
graph LR
    subgraph "Módulo ESP32-CAM (Smart Sensor)"
        Sensor[OV2640] -->|DVP Bus| ESP32[ESP32 SoC]
        ESP32 -->|Cálculo de Diferença| PSRAM[4MB PSRAM]
        ESP32 -->|Wi-Fi| Antena[Antena 2.4GHz]
    end

    subgraph "PC Viewer"
        NetworkCard[Interface de Rede] --> App[Dashboard UI]
        App --> Monitor[Display de Saída]
    end

    Antena <==>|HTTP GET - Dados Processados| NetworkCard
```

## 3. Arquitetura de Software

Toda a carga de processamento das imagens e tomada de decisão é atribuída ao firmware do ESP32-CAM. O PC atua apenas como cliente de apresentação.

### 3.1 Pipeline de Visão Computacional (ESP32-CAM Firmware)

A lógica interna executada no ESP32-CAM a cada ciclo (Frame):

```mermaid
classDiagram
    direction BT
    class Acquisition {
        Ler Frame do Sensor (OV2640)
    }

    class PreProcessing {
        Converter para Escala de Cinza
    }

    class DifferenceEngine {
        Ler Baseline da RAM
        AbsDiff(Baseline, Atual)
    }

    class Thresholding {
        Aplicar Limiar Binário (Threshold)
        Contar Pixels Brancos (Alterados)
    }

    class StateLogic {
        If (Pixels > Threshold Máximo) -> Item Ausente
        Preparar Buffers JPEG (Original e Diferença)
    }

    %% Relacionamentos
    PreProcessing <.. Acquisition
    DifferenceEngine <.. PreProcessing
    Thresholding <.. DifferenceEngine
    StateLogic <.. Thresholding
```

## 4. Fluxo de Dados (Sequence Diagram)

### 4.1 Ciclo de Processamento e Visualização

Este fluxo detalha como o ESP32 realiza o trabalho de visão e como o PC consulta os resultados.

```mermaid
sequenceDiagram
    participant PC as PC (Dashboard Viewer)
    participant ESP_HTTP as HTTP Server (ESP32)
    participant ESP_Core as Image Pipeline (ESP32)
    participant Cam as Sensor OV2640
    
    loop Ciclo Interno (ESP32-CAM)
        ESP_Core->>Cam: Requisita Frame
        Cam-->>ESP_Core: Retorna Buffer Raw/JPEG
        ESP_Core->>ESP_Core: Converte para Grayscale
        ESP_Core->>ESP_Core: Calcula Diferença Absoluta vs Baseline
        ESP_Core->>ESP_Core: Atualiza Variável Global de Estado (Ausente/Presente)
        ESP_Core->>ESP_Core: Compacta buffers resultantes para JPEG
    end

    loop Polling (PC)
        PC->>ESP_HTTP: HTTP GET /status_and_images
        ESP_HTTP->>ESP_Core: Lê as últimas imagens e estado
        ESP_HTTP-->>PC: Retorna JSON (Status) e multipart JPEGs
        PC->>PC: Atualiza a interface gráfica
    end
```

## 5. Próximos Passos (Expansão Futura)

Para evoluir a arquitetura, o sistema pode incorporar:

- Redes Neurais Leves (TinyML) rodando diretamente no ESP32-S3 para substituir a subtração de fundo tradicional.
- Definição de Múltiplas ROIs (Regions of Interest) na mesma imagem processadas no ESP32.
- O ESP32 pode parar de depender de *polling* do PC e passar a publicar ativamente mudanças via MQTT.
