# Exercícios de Visão Computacional - Aula 03: Limiarização e Filtragem

## Exercício 1: Convolução e Busca por Padrões
* Implemente a operação de convolução que procure e imprima a posição mais semelhante que uma determinada janela ocorre dentro de uma imagem grande.
* Crie e mostre uma imagem de região de $50 \times 50$ centralizada na posição encontrada.
* **Nota:** Se a região centralizada ficar na borda da imagem, preencher os espaços vazios com pixels pretos (padding).

## Exercício 2: Filtros de Suavização e Limiarização
* Pesquise e implemente o filtro de suavização gaussiano.
* Baixe 100 imagens de células do banco de dados recomendado e depois tente fazer limiarizações para separar as células do fundo.
    * http://www.cellimagelibrary.org/pages/project_20269
* Tente usar filtros de suavização para melhorar os resultados e deixar as células com o mínimo de componentes possíveis. 
* Faça o teste e compare os resultados utilizando:
    * Os filtros de média, mediana e moda.
    * Três tamanhos de janela diferentes para cada filtro.
* **Nota:** Caso seja necessário um filtro muito grande para ver alterações, reduza a resolução original da imagem para $256 \times 256$ pixels.
* **Desafio analítico:** Qual filtro você escolheria para a base? Justifique sua resposta com base nos testes.

## Exercício 3: Filtros de Realce e Derivadas
Dada a mesma base de imagens de células do exercício anterior, tente realçar o núcleo e o contorno de cada célula:
* Use a derivada primeira e a derivada segunda. (Reduza a resolução da imagem para $256 \times 256$ pixels se precisar de filtros muito grandes).
* Implemente um filtro de realce das direções da primeira derivada.
* Use a informação dos gradientes nas bordas mais fortes para tentar estimar qual é a direção predominante de gradientes em cada imagem (vertical ou horizontal?).
* Indique a orientação do gradiente (escuro $\rightarrow$ claro) ou (claro $\rightarrow$ escuro) em cada ponto de borda atribuindo um valor baixo ou alto de cinza, respectivamente.
