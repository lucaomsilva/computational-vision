# Master Test Plan (MTP)

| Metadado              | Detalhe                                                |
| :-------------------- | :----------------------------------------------------- |
| **Projeto**           | Sistema de Controle de Estoque com Visão Computacional |
| **ID do Documento**   | SCEVC-DOC-004                                          |
| **Versão**            | 0.1                                                    |
| **Status**            | Rascunho                                               |
| **Data**              | 05/05/2026                                             |
| **Hardware de Teste** | 1x ESP32-CAM, 1x PC Viewer, Roteador Wi-Fi             |
| **Ferramentas**       | Postman/Browser (Testar endpoints HTTP)                |

---

## 1. Estratégia de Teste

A validação do sistema será realizada focando na arquitetura *Edge Computing*:

1. **Testes Unitários de Firmware:** Validação das rotinas matemáticas no ESP32 (Filtro Grayscale, Subtração, Threshold).
2. **Testes de Integração e Servidor Web:** Garantir que o ESP32 entregue corretamente o JSON de *status* e as imagens em formato adequado.
3. **Testes de Sistema/Robustez:** Comportamento térmico do ESP32 operando intensamente na borda, e resiliência à iluminação.

---

## 2. Casos de Teste (Test Cases)

### 2.1. Testes de Unidade no Firmware (ESP32)

| ID do Teste | Rastreabilidade | Descrição | Procedimento | Critério de Aceite (Pass/Fail) |
| :--- | :--- | :--- | :--- | :--- |
| **TC-UNT-01** | `SYS-FUNC-001`<br>`SYS-PERF-002` | **Rotina de Conversão e Diferença** | 1. Carregar na PSRAM duas imagens estáticas forçadas.<br>2. Chamar a função `process_diff()`.<br>3. Inspecionar o buffer de saída (Log/Serial). | A função deve calcular os pixels diferentes corretamente sem falhas de alocação de memória (Heap OK). |
| **TC-UNT-02** | `SYS-FUNC-002` | **Estado Lógico (Threshold)** | 1. Modificar artificialmente o contador de pixels diferentes.<br>2. Verificar se a variável de estado muda para `Ausente`. | O comportamento lógico deve respeitar exatamente o valor definido como parâmetro limite (*Threshold*). |

### 2.2. Testes de Integração e Rede (INT)

| ID do Teste | Rastreabilidade | Descrição | Procedimento | Critério de Aceite (Pass/Fail) |
| :--- | :--- | :--- | :--- | :--- |
| **TC-INT-01** | `SYS-FUNC-003` | **Servidor HTTP Local** | 1. Acessar o endpoint do ESP32 via Browser ou Postman.<br>2. Verificar Payload de Resposta. | O ESP32 deve retornar um payload contendo o Status do estoque e pelo menos um Stream/Buffer com a imagem processada. |
| **TC-INT-02** | `SYS-FUNC-004` | **Dashboard Viewer** | 1. Abrir o cliente no PC.<br>2. Retirar o objeto da frente da câmera. | O PC deve exibir a imagem processada com a mancha branca (diferença) e emitir/indicar visualmente o "Alerta de Ausência" em menos de 2s. |

### 2.3. Testes de Sistema e Confiabilidade (SYS)

| ID do Teste | Rastreabilidade | Descrição | Procedimento | Critério de Aceite (Pass/Fail) |
| :--- | :--- | :--- | :--- | :--- |
| **TC-SYS-01** | `SYS-PERF-001` | **Estabilidade Térmica (1h)** | 1. Deixar o ESP32 rodando ciclos ininterruptos de processamento de imagem por 1 hora. | O ESP32 não deve reiniciar por travamento (Watchdog) e nem degradar o tempo de resposta do endpoint web devido ao aquecimento. |
| **TC-SYS-02** | `SYS-REST-001` | **Variação de Iluminação Leve** | 1. Modificar a incidência de luz ou causar sombras.<br>2. Observar o log local no PC. | O processamento interno do ESP32 não deve ser tão sensível a ponto de disparar o alerta repetidamente por conta de sombras simples. |
