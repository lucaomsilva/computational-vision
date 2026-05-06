# System Requirements Specification (SRS)

| Metadado            | Detalhe                                                |
| :------------------ | :----------------------------------------------------- |
| **Projeto**         | Sistema de Controle de Estoque com Visão Computacional |
| **ID do Documento** | SCEVC-DOC-003                                          |
| **Versão**          | 0.1                                                    |
| **Status**          | Rascunho                                               |
| **Data**            | 05/05/2026                                             |

## Histórico de Revisão

| Versão | Data | Autor | Descrição da Mudança |
| :--- | :--- | :--- | :--- |
| 0.1 | 05/05/2026 | Equipe | Versão inicial baseada no JSON de planejamento. |

---

## 1. Requisitos de Arquitetura de Hardware (ARCH)

*Definições físicas necessárias para suportar a carga de software e processamento.*

- [ ] **[SYS-ARCH-001] Nó de Captura e Processamento (Edge)**
  > O sistema deve utilizar módulos **ESP32-CAM**. Além de atuar como servidor de captura, o módulo deve ser capaz de executar algoritmos de manipulação de matrizes de imagem.

- [ ] **[SYS-ARCH-002] Câmera e Resolução**
  > A câmera acoplada (ex: OV2640) deve ser configurada em resoluções suportáveis pela RAM do ESP32 (ex: QVGA 320x240 ou menor) para permitir alocação de três buffers inteiros na PSRAM (Imagem Atual, Baseline e Diferença).

## 2. Requisitos de Recursos e Performance (PERF)

*Gestão de tempo de resposta e consumo.*

- [ ] **[SYS-PERF-001] Frequência de Processamento na Borda**
  > O microcontrolador ESP32-CAM deve conseguir rodar um ciclo completo de captura, escala de cinza e diferença em um tempo **inferior a 2 segundos**.

- [ ] **[SYS-PERF-002] Gerenciamento Estrito de Memória (ESP32)**
  > O código do ESP32 deve otimizar o uso da PSRAM para armazenar os quadros de referência sem causar fragmentação ou vazamentos de memória (Memory Leaks), garantindo execução ininterrupta.

- [ ] **[SYS-PERF-003] Interface Leve no Host**
  > Uma vez que o processamento pesado ocorre no dispositivo, o software no PC deve ter baixíssimo consumo de recursos de CPU, focado apenas na renderização da UI.

## 3. Requisitos Funcionais (FUNC)

*Operações centrais que o sistema deve executar.*

- [ ] **[SYS-FUNC-001] Processamento Subtrativo Local**
  > O firmware do ESP32-CAM deve processar as imagens internamente comparando a captura atual com uma imagem base (baseline) gravada em memória, utilizando diferença absoluta.

- [ ] **[SYS-FUNC-002] Lógica de Decisão (Threshold)**
  > O ESP32-CAM deve aplicar um limiar (threshold) nos resultados da diferença e contar os pixels alterados. Se exceder o parâmetro, o estado lógico passa para "Ausente".

- [ ] **[SYS-FUNC-003] Servidor de Resultados**
  > O ESP32-CAM deve expor endpoints HTTP acessíveis pelo PC que devolvam simultaneamente: A Imagem Original (JPEG), A Imagem Processada/Threshold (JPEG) e o Estado Atual da Prateleira.

- [ ] **[SYS-FUNC-004] Dashboard de Visualização**
  > O PC deve exibir as imagens recebidas e apresentar alertas visuais se o status do item recebido for reportado como ausente pelo sensor.

## 4. Requisitos de Restrição e Conectividade (REST)

*Limitações e dependências do ambiente.*

- [ ] **[SYS-REST-001] Constância de Iluminação**
  > Como o algoritmo subtrativo embarcado tem menos poder de correção inteligente, ele depende criticamente de operar em iluminação controlada, sem grandes sombras móveis.

- [ ] **[SYS-REST-002] Independência Parcial de Rede**
  > O processamento ocorrerá mesmo que o PC esteja desconectado. No entanto, para visualização de logs ou alarmes imediatos, a conexão local via Wi-Fi deve estar ativa.

## 5. Requisitos de Expansão (FUTURO)

*Funcionalidades não obrigatórias para a v1.0, mas previstas.*

- [ ] **[SYS-FUT-001] Notificações MQTT Ativas**
  > O ESP32-CAM poderá enviar ativamente um pacote JSON via MQTT para a nuvem sempre que detectar uma mudança de estado, em vez de depender do PC realizar *polling*.

---
**Legenda de Status:**

- [ ] Aberto / Não Iniciado
- [x] Implementado e Testado
