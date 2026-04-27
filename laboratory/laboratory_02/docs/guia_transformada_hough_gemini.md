# Guia de Implementação: Transformada de Hough para Círculos (CHT)

A Transformada de Hough é uma técnica de extração de características usada para detectar formas geométricas simples. Para círculos, o algoritmo busca por conjuntos de pontos que satisfaçam a equação da circunferência em um espaço de parâmetros (acumulador).

## 1. Fundamentos Matemáticos

Um círculo no plano $xy$ é definido pela equação:
$$(x - a)^2 + (y - b)^2 = r^2$$

Onde:
* $(a, b)$: Coordenadas do centro do círculo.
* $r$: Raio do círculo.

Diferente da detecção de retas (2 parâmetros), a detecção de círculos requer um espaço de busca **3D** (eixo $a$, eixo $b$ e eixo $r$).

## 2. Pré-processamento Obrigatório

Para que a transformada funcione, você não deve processar a imagem original diretamente, mas sim o seu mapa de bordas.

1.  **Suavização:** Use `cv::GaussianBlur` para reduzir ruídos que podem gerar bordas falsas.
2.  [cite_start]**Detecção de Bordas:** Utilize o operador de Sobel para obter os gradientes [cite: 488] ou o algoritmo de Canny para obter bordas binárias finas.
3.  [cite_start]**Cálculo de Gradiente (Opcional, mas recomendado):** Conhecer a direção do gradiente $\theta$ em cada ponto de borda permite votar apenas na direção normal à borda, reduzindo drasticamente o tempo de processamento[cite: 460, 472].

## 3. Algoritmo de Implementação Manual (Passo a Passo)

Se você for implementar "na mão" em C++, siga esta lógica:

### A. Definição do Acumulador
Crie uma estrutura de dados 3D (pode ser um `std::vector<cv::Mat>`) onde cada "fatia" representa um raio $r$. Inicialize todos os valores com zero.

### B. O Processo de Votação
Para cada pixel $(x, y)$ que seja considerado borda na sua imagem pré-processada:
1.  Para cada raio $r$ possível (dentro de um intervalo `minRadius` e `maxRadius`):
2.  Calcule os possíveis centros $(a, b)$ que poderiam ter gerado aquele pixel de borda:
    * $a = x - r \cdot \cos(\theta)$
    * $b = y - r \cdot \sin(\theta)$
3.  Incremente a posição `acumulador[r][a][b]++`.

### C. Detecção de Picos
Após percorrer todos os pixels de borda, procure os valores locais máximos no acumulador. Se o valor em `acumulador[r][a][b]` for maior que um determinado **limiar (threshold)**, um círculo de raio $r$ e centro $(a, b)$ foi detectado.

## 4. Estrutura Sugerida em C++

```cpp
// Exemplo de lógica para o acumulador
struct Circulo {
    int a, b, r, votos;
};

// 1. Detectar bordas (Ex: Canny)
cv::Mat bordas;
cv::Canny(imagemCinza, bordas, 50, 150);

// 2. Definir espaço de busca
int minR = 10, maxR = 100;
int dimRaio = maxR - minR;

// Espaço do acumulador (simplificado para um raio fixo para exemplo)
// Na prática, use uma matriz 3D ou itere sobre os raios
std::vector<cv::Mat> acumulador(maxR, cv::Mat::zeros(imagem.size(), CV_32S));

// 3. Votação
for (int y = 0; y < bordas.rows; y++) {
    for (int x = 0; x < bordas.cols; x++) {
        if (bordas.at<uchar>(y, x) > 0) { // Se for pixel de borda
            for (int r = minR; r < maxR; r++) {
                for (int theta = 0; theta < 360; theta++) {
                    int a = x - r * cos(theta * CV_PI / 180.0);
                    int b = y - r * sin(theta * CV_PI / 180.0);
                    
                    if (a >= 0 && a < bordas.cols && b >= 0 && b < bordas.rows) {
                        acumulador[r].at<int>(b, a)++;
                    }
                }
            }
        }
    }
}