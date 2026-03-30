# Guia de Resolução Estratégica (C++ com OpenCV)

Este guia propõe um fluxo de pensamento para resolver os problemas utilizando C++ e a biblioteca OpenCV (`cv::`), indicando os caminhos e funções exatas na documentação oficial em C++.

## 1. Convolução e Busca de Padrões (Template Matching)
* **A Matemática da Coisa:** A convolução de busca funciona deslizando o seu *template* (a janela menor) sobre a imagem original. Em cada posição, os pixels da janela são multiplicados pelos pixels da imagem subjacente, e a soma gera um mapa de similaridade (um novo `cv::Mat`). 
* **Estratégia de Código:**
    1. Carregue as imagens (`cv::imread`).
    2. A convolução fará a varredura e gerará o mapa de similaridade.
    3. Encontre as coordenadas de onde ocorreu o valor máximo ou mínimo (dependendo do método escolhido) nesse mapa.
    4. Extraia a região de interesse (ROI).
* **Tratamento de Borda:** Para extrair o quadrado de $50 \times 50$ sem disparar uma exceção de limite de memória, adicione bordas de preenchimento antes de fazer o recorte.
* **Onde pesquisar na Documentação C++:**
    * Operação de busca: `cv::matchTemplate()` (leia sobre `cv::TM_CCOEFF_NORMED`).
    * Encontrar a coordenada máxima: `cv::minMaxLoc()`. Retorna ponteiros para os valores e objetos `cv::Point` para as posições.
    * Preenchimento de bordas: `cv::copyMakeBorder()`.
    * Recorte (ROI): Em C++, você pode simplesmente instanciar um `cv::Rect` e aplicá-lo à matriz, ex: `cv::Mat recorte = imagem(cv::Rect(x, y, largura, altura));`.

## 2. Filtros de Suavização e Limiarização
* **Pipeline de Leitura:** Crie um laço que leia o diretório com as imagens em lote. 
* **Filtros e Suas Aplicações:**
    * *Média:* `cv::blur()`.
    * *Gaussiano:* `cv::GaussianBlur()`.
    * *Mediana:* `cv::medianBlur()`.
    * *Moda:* **Atenção aqui.** O OpenCV em C++ não possui um filtro de moda nativo. Você precisará implementar uma função manual que desliza um `cv::Rect` pela imagem e, para cada vizinhança, constrói um pequeno histograma/mapa de frequência (usando `std::map` ou um `int array[256]`) para descobrir qual pixel mais se repete.
* **Critério de Escolha:** Aplique o limiar de Otsu após a suavização. O melhor filtro será aquele que melhor separar as células do fundo mantendo a integridade morfológica.
* **Onde pesquisar na Documentação C++:**
    * Leitura de diretórios: Use o módulo nativo do C++17 `<filesystem>` (`std::filesystem::directory_iterator`) ou a função auxiliar do próprio OpenCV `cv::glob()`.
    * Redimensionamento: `cv::resize()`.
    * Limiarização Automática: `cv::threshold()` passando a flag `cv::THRESH_BINARY | cv::THRESH_OTSU`.

## 3. Realce e Derivadas
* **Operadores Práticos:**
    * *Primeira derivada:* Use as máscaras de Sobel (uma para X, outra para Y).
    * *Segunda derivada:* Use a matriz do Laplaciano.
* **Calculando o Gradiente (Magnitude e Direção):**
    * A magnitude (força da borda) é: $M = \sqrt{G_x^2 + G_y^2}$
    * A direção (ângulo) é: $\theta = \arctan(G_y / G_x)$
* **Análise de Predominância:** Isole os pixels onde a magnitude é forte e calcule os ângulos $\theta$ para ver qual direção vence.
* **Onde pesquisar na Documentação C++:**
    * Derivada de primeira ordem: `cv::Sobel()`. *Dica de ouro: O parâmetro `ddepth` (profundidade de destino) deve ser `CV_32F` ou `CV_64F` (float ou double). Se você deixar como 8-bit (`CV_8U`), o C++ vai truncar as derivadas negativas para zero e destruir o seu gradiente!*
    * Derivada de segunda ordem: `cv::Laplacian()`.
    * Cálculo rápido do Gradiente: O OpenCV tem as funções `cv::magnitude()` e `cv::phase()` (que pode retornar em graus se o parâmetro `angleInDegrees` for `true`). Elas recebem os `cv::Mat` de Sobel X e Y.
    * Mapeamento Visual: Para converter os ângulos (ex: $0^{\circ}$ a $360^{\circ}$) que estão em formato float (`CV_32F`) de volta para tons de cinza (`CV_8U`) a fim de exibi-los na tela com `cv::imshow()`, use `cv::normalize()` com os parâmetros `alpha=0`, `beta=255`, `norm_type=cv::NORM_MINMAX` e `dtype=CV_8U`.