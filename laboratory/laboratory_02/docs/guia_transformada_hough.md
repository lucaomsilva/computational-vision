# Transformada de Hough para Detecção de Círculos

A Transformada de Hough é uma técnica poderosa em processamento de imagens usada para detectar formas geométricas, como linhas, círculos e elipses. A detecção de círculos é particularmente útil em diversas aplicações, como análise de imagens médicas, controle de qualidade industrial e visão de robôs.

Este documento descreve os passos fundamentais para implementar a Transformada de Hough para detecção de círculos.

## Passo a Passo da Implementação

A ideia central é mapear os pontos da imagem (espaço da imagem) para um espaço de parâmetros (espaço de Hough) e procurar por picos de "votos" nesse novo espaço. Para um círculo, os parâmetros são as coordenadas do centro `(a, b)` e o raio `r`.

### 1. Pré-processamento da Imagem

Antes de aplicar a transformada, a imagem precisa ser preparada para destacar as bordas, que são os pontos de interesse para a votação.

*   **Conversão para Escala de Cinza:** A detecção de formas geralmente não depende de cor. Converter a imagem para escala de cinza simplifica os cálculos.
*   **Suavização (Blur):** Aplique um filtro de suavização, como o Gaussiano (`GaussianBlur`), para reduzir o ruído. Isso evita a detecção de muitos círculos falsos em bordas ruidosas.
*   **Detecção de Bordas:** Use um detector de bordas, como o Canny (`Canny`), para obter uma imagem binária onde os pixels brancos representam as bordas dos objetos.

### 2. Definição do Espaço de Parâmetros (Espaço de Hough)

A equação de um círculo é `(x - a)² + (y - b)² = r²`.

Os parâmetros que definem um círculo são `(a, b, r)`. Portanto, nosso espaço de Hough será tridimensional. Cada ponto nesse espaço corresponde a um único círculo na imagem.

### 3. Criação do Acumulador

O acumulador é uma matriz 3D que armazena os votos. As dimensões do acumulador são:
*   Largura: correspondente às possíveis coordenadas `a` do centro.
*   Altura: correspondente às possíveis coordenadas `b` do centro.
*   Profundidade: correspondente aos possíveis valores de raio `r`.

Antes de começar a votação, todos os elementos do acumulador são inicializados com zero.

### 4. Processo de Votação

Este é o núcleo do algoritmo. Para cada pixel de borda `(x_edge, y_edge)` detectado no Passo 1:

1.  Itere sobre uma faixa de raios `r` que você espera encontrar na imagem (por exemplo, de `r_min` a `r_max`).
2.  Para cada raio `r`, sabemos que o centro `(a, b)` do círculo deve estar a uma distância `r` do ponto `(x_edge, y_edge)`. Isso define um círculo de raio `r` centrado em `(x_edge, y_edge)` no espaço da imagem.
3.  Para cada ponto `(a, b)` nesse círculo de possíveis centros, incremente o contador no acumulador na posição `Acumulador[a][b][r]`.

Uma forma mais eficiente de fazer isso é usando a forma paramétrica:
`a = x_edge - r * cos(θ)`
`b = y_edge - r * sin(θ)`

Iterando `θ` de 0 a 360 graus, calculamos os possíveis centros `(a, b)` para um dado `(x_edge, y_edge)` e `r`, e votamos na célula `Acumulador[a][b][r]`.

### 5. Detecção dos Círculos

Após todos os pixels de borda terem "votado", o acumulador conterá picos de alta contagem. Esses picos representam os parâmetros dos círculos mais prováveis na imagem.

*   **Encontrar Máximos:** Procure por máximos locais no acumulador 3D.
*   **Aplicar um Limiar (Threshold):** Ignore os picos cuja contagem de votos seja menor que um determinado limiar. Isso filtra círculos fracos ou acidentais.

As coordenadas `(a, b, r)` de cada pico que ultrapassa o limiar correspondem a um círculo detectado na imagem.

### 6. Visualização dos Resultados

Para verificar o resultado, desenhe os círculos detectados (usando os parâmetros `a`, `b`, e `r` encontrados) sobre a imagem original.

## Implementação Prática com OpenCV

Implementar a Transformada de Hough do zero é um ótimo exercício de aprendizado. No entanto, para aplicações práticas, o OpenCV fornece uma função otimizada e eficiente: `cv::HoughCircles`.

Ela realiza todos os passos descritos acima internamente.

```cpp
#include <opencv2/opencv.hpp>
#include <vector>

void detectCircles(const cv::Mat& image) {
    cv::Mat gray, blurred;
    // Pré-processamento
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(gray, blurred, cv::Size(9, 9), 2, 2);

    std::vector<cv::Vec3f> circles;
    // Aplica a Transformada de Hough para Círculos
    cv::HoughCircles(blurred, circles, cv::HOUGH_GRADIENT, 1, blurred.rows / 8, 100, 30, 10, 100);

    // Desenha os círculos detectados
    cv::Mat result = image.clone();
    for(size_t i = 0; i < circles.size(); i++) {
        cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        cv::circle(result, center, 3, cv::Scalar(0, 255, 0), -1, 8, 0);
        cv::circle(result, center, radius, cv::Scalar(0, 0, 255), 3, 8, 0);
    }

    cv::imshow("Detected Circles", result);
    cv::waitKey(0);
}
```

Espero que este guia seja útil para os seus estudos em Visão Computacional! Se tiver mais alguma dúvida, pode perguntar.

<!--
[PROMPT_SUGGESTION]Poderia me ajudar a refatorar o código em `main.cpp` para usar a função `detectCircles` que está no novo arquivo de documentação?[/PROMPT_SUGGESTION]
[PROMPT_SUGGESTION]Como eu poderia ajustar os parâmetros da função `cv::HoughCircles` para detectar círculos de tamanhos diferentes na minha imagem?[/PROMPT_SUGGESTION]
