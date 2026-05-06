# Concept of Operations (ConOps)

| Metadado            | Detalhe                                                |
| :------------------ | :----------------------------------------------------- |
| **Projeto**         | Sistema de Controle de Estoque com Visão Computacional |
| **ID do Documento** | SCEVC-DOC-001                                          |
| **Versão**          | 0.1                                                    |
| **Status**          | Rascunho                                                 |
| **Data**            | 05/05/2026                                             |

---

## 1. Escopo

Este documento descreve as características operacionais do Sistema de Controle de Estoque com Visão Computacional. O sistema destina-se a realizar a detecção automática de presença ou ausência de itens em uma prateleira, utilizando um dispositivo embarcado ESP32-CAM tanto para a captura quanto para o processamento das imagens (Edge Computing), comunicando os resultados e as imagens processadas para um PC de visualização.

## 2. Situação Atual e Oportunidades

Atualmente, o monitoramento do estoque de prateleiras é realizado de forma manual ou exige equipamentos caros e complexos de visão industrial.

### 2.1. Deficiências do Processo Atual

* **Dependência Humana:** A necessidade de verificação visual manual constante é propensa a erros e exige tempo.
* **Falta de Tempo Real:** Atualizações no inventário sofrem atrasos.
* **Custo Elevado:** Sistemas tradicionais de visão computacional industrial têm um custo de hardware proibitivo para pequenas implementações.

## 3. Conceito do Sistema Proposto

O sistema propõe uma arquitetura de baixo custo e processamento na borda (Edge Computing), onde a captura e o processamento de imagem são realizados diretamente no nó (ESP32-CAM). O PC atua estritamente como um painel de visualização (Dashboard).

### 3.1. Arquitetura Operacional

O sistema é composto por três elementos principais:

1. **Nó de Captura e Processamento (ESP32-CAM):** Dispositivo fixado em frente à prateleira que captura imagens, mantém o *baseline*, calcula a diferença absoluta, aplica thresholds e determina o estado do estoque. Ele hospeda um servidor web HTTP para prover os dados.
2. **Unidade de Visualização (PC):** Computador executando um software ou script de painel que requisita o estado e as imagens (original e processada) do ESP32-CAM e as exibe para o operador.
3. **Infraestrutura de Rede (Wi-Fi):** Meio de transmissão sem fio (Local) entre a câmera e o PC.

### 3.2. Cenários de Uso (User Stories)

#### Cenário A: Inicialização e Setup (Baseline)
>
> O **Operador** posiciona o ESP32-CAM de forma fixa voltado para a prateleira. O operador aciona (via botão ou requisição web) o comando de inicialização. O ESP32-CAM captura a primeira imagem em escala de cinza e a salva em sua própria memória RAM/PSRAM como *baseline* (referência) para futuras comparações.

#### Cenário B: Monitoramento Contínuo
>
> O **PC** solicita os dados do ESP32-CAM periodicamente. O ESP32-CAM retorna o estado atual (ex: Item Presente) junto com um stream contendo a imagem original recém capturada e a máscara da imagem processada (diferença/threshold). O PC apenas exibe essas janelas lado a lado no monitor.

#### Cenário C: Detecção de Ausência de Item
>
> Um item é retirado da prateleira. No próximo ciclo interno do **ESP32-CAM**, ele detecta uma grande quantidade de pixels diferentes (acima do limiar configurado) em relação ao seu *baseline* local. Ele atualiza internamente o estado para "Item Ausente". Na próxima requisição do PC, o painel é atualizado instantaneamente para sinalizar visualmente a falta.

## 4. Ambiente Operacional

* **Físico:** Ambiente interno (estoque ou prateleira) com a câmera fixada firmemente (evitar vibrações que causam falsos positivos).
* **Iluminação:** Requer iluminação relativamente constante. Grandes variações de luz podem gerar artefatos na subtração de fundo realizada pelo microcontrolador.
* **Rede:** Necessita de cobertura Wi-Fi estável na banda de 2.4GHz para suportar a transferência das imagens resultantes.

## 5. Matriz de Stakeholders

| Papel               | Responsabilidade        | Interesse no Sistema                      |
| :------------------ | :---------------------- | :---------------------------------------- |
| **Operador de Estoque**| Monitorar faltas     | Interface simples informando o que falta. |
| **Gerência**        | Acompanhar inventário   | Dados confiáveis de disponibilidade em tempo real. |
| **Desenvolvedor**   | Manter e expandir       | Código modular que permita ajustar o threshold direto no firmware do ESP32. |

## 6. Impactos Operacionais

* **Automatização:** Reduz a necessidade de verificação física frequente.
* **Custo-Benefício:** Demonstra viabilidade de usar hardwares de ~US$ 10 (ESP32-CAM) operando como *Smart Sensors* autossuficientes.
* **Banda de Rede:** Ocupa menos a rede Wi-Fi, pois o PC não precisa baixar quadros em altíssima resolução para processar; o ESP32 pode enviar apenas alertas de status e imagens JPEG compactadas sob demanda.

---
