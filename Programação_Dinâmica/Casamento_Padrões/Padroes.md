# Casamento de Padrões

O casamento de padrões é uma busca por uma cadeia de símbolos em uma sequência maior.

> Ex: Busca de palavras em texto.

##### Algoritmos

- string matching
- string searching
- pattern matching

##### Aplicações

- Busca de DNA
- Detecção de plágio
- Correção ortográfica
- Casamento de áudio

##### Casamento exato de padrões:

- Força bruta
- KMP
- Algoritmo Z
- Aho Corasick
- Boyer Moore

##### Casamento aproximado de padrões:
- Distância de Levenshtein

--- 

Seja $T[1 \dots n]$ um texto de tamanho $n$ e $P[1 \dots m]$ um padrão de tamanho $m$, com $m \le n$. Os elementos de $T$ e $P$ são símbolos do alfabeto finito $\Sigma$.

> Exemplos:
- $\Sigma = \{0, 1\}$
- $\Sigma = \{a, b, \dots , z\}$

Dizemos que o padrão $P$ ocorre em $T$, quando existir algum inteiro $s \le n - m$, tal que $T[s + j] = P[j]$, $1 \le j \le m$.

Se $P$ ocorre com deslocamento $s$ em $T$, então chamamos $s$ de deslocamento válido; caso contrário chamamos de deslocamento inválido.

> Exemplo:

Texto $T$

| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| a | b | c | a | b | a | a | b | c | a | b | a | 

Padrão $P$

| 1 | 2 | 3 | 4 |
|:---:|:---:|:---:|:---:|
| a | b | a | a | 

> Os deslocamentos $s = 0$, $s = 1$ e $s = 2$ são inválidos!
> O deslocamento $s = 3$ é válido!

O problema do casamento de padrões é o problema de encontrar todos os deslocamentos válidos com os quais um dado padrão $P$ ocorre em um dado texto $T$.

> Exemplo: 

Texto $T$

| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| a | b | r | a | c | a | d | a | b | r | a | 

Padrão $P$

| 1 | 2 | 3 |
|:---:|:---:|:---:|
| b | r | a | 

> No exemplo, $P$ ocorre duas vezes em $T$, com $s = 1$ e $s = 8$.

## Notação e Terminologia

- **Definição 1.** O conjunto de todas as palavras de tamanho finito utilizando os símbolos do alfabeto $\Sigma$ é denotado por $\Sigma^*$.

- **Definição 2.** O tamanho de uma palavra $x$ é o número de símbolos dessa palavra e é denotado por $|x|$.

- **Definição 3.** A concatenação de 2 palavras $x$ e $y$, denotada por $xy$, tem tamanho $|x| + |y|$ e consiste dos símbolos de $x$ seguidos dos símbolos de $y$.

> Exemplo:
- $x = abc$, $|x| = 3$
- $y = aad$, $|y| = 3$

> $xy = abcaad$, $|xy| = |x| + |y| = 6$

- **Definição 4 (Prefixo).** $X[1 \dots k]$ é prefixo de $Y[1 \dots j]$ se $k \le j$ e $X[1 \dots k] = Y[1 \dots k]$.

> Exemplo:
$$
\begin{cases}
X = abcdab \\
W = ab
\end{cases}
$$

> $W$ é prefixo de $X$.

- **Definição 5 (Prefixo próprio).** Se $k < j$, então $X[1 \dots k]$ é prefixo próprio de $Y$.

> Exemplo: $W$ é prefixo próprio de $X$.

- **Definição 6 (Sufixo).** $X[1 \dots k]$ é sufixo de $Y[1 \dots j]$ se $k \le j$ e $X[1 \dots k] = Y[j - k + 1 \dots j]$.

> Exemplo:
$$
\begin{cases}
X = abcdab \\
W = dab
\end{cases}
$$

> $W$ é sufixo de $X$.

- **Definição 7 (Sufixo próprio).** Se $k < j$, então $X[1 \dots k]$ é sufixo próprio de $Y$.

> Exemplo: $W$ é sufixo próprio de $X$.

## Força Bruta

O algoritmo de casamento de padrão utilizando o método da força bruta busca todos os deslocamentos válidos utilizando um laço que verifica a condição $P[1 \dots m] = T[s+1 \dots s+m]$ para cada um dos $n - m$ valores possíveis de $s$.

```text
Força Bruta(T, P)
    n ← |T|
    m ← |P| 
    c ← 0
    para s ← 0 até n − m
        j ← 1
        enquanto j ≤ m e P[j] = T[s + j]
            j ← j + 1
        se j > m
            c ← c + 1
    retorne c
```

> Consumo de tempo: $O(mn)$

> Notas do João: de acordo com o exemplo é o seguinte, ele vai verificar o primeiro caracter do Padrão com as 'letras', caso ela bata com alguma (seja igual) ela vê a proxima letra depois dela do padrão e do texto, caso em qualquer momento não bata, ele passa pro proximo letra do texto e reinicia a do padrão para a primeira

### Problema da Força Bruta

Com o algoritmo de força bruta, o segundo caracter depois que o primeiro bater será testado duas vezes.

Mas sabemos que caracter é esse e que ele não aparece no padrão.

Vamos ver a seguir um algoritmo mais eficiente.

## Knuth Morris e Pratt (KMP)

- Criado por Donald Knuth, James Morris e Vaughan Pratt.
- O algoritmo KMP é baseado em uma pré-computação de uma função de prefixo para o padrão $P$.

> Suponha que os símbolos do padrão $P[1 \dots q]$ casam com os símbolos $T[s + 1 \dots s + q]$ do texto, mas $P[q + 1] \ne T[s + q + 1]$.

![imagem1](i1.png)

> Pergunta: Qual é o menor deslocamento $s' > s$ tal que $P[1 \dots k] = T[s' + 1 \dots s' + k]$, onde $s' + k = s + q$?

![imagem2](i2.png)

- Na prática, o deslocamento $s'$ pode ser pré-computado comparando $P$ com ele mesmo.
- Observe $T[s'+1 \dots s'+k]$ é um texto conhecido, e é um sufixo de $P[1 \dots q]$.
- Encontrar o menor deslocamento $s' > s$, é o mesmo que encontrar o maior $k < q$, tal que, $P[1 \dots k]$ é sufixo de $P[1 \dots q]$.

Dado um padrão $P[1 \dots m]$, a função de prefixo para o padrão $P$ é a função $\pi : \{1, 2, 3 \dots , m\} \rightarrow \{0, 1, 2, \dots , m - 1\}$ tal que

$$\pi[q] = \{k : k < q \text{ e } P[1 \dots k] \text{ é sufixo próprio de } P[1 \dots q]\}$$

Ou seja, $\pi[q]$ é o tamanho do maior prefixo de $P$ que é um sufixo de $P[1 \dots q]$.

> Exemplo: $P = ababbababba$

| $q$ | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| $P$ | a | b | a | b | b | a | b | a | b | b | a | 
| $\pi$ | 0 | 0 | 1 | 2 | 0 | 1 | 2 | 3 | 4 | 5 | 6 |

```
Computar-Função-Prefixo(P)
    m ← |P|
    π[1] ← 0
    k ← 0
    para q ← 2 até m
        enquanto k > 0 e P[k + 1] ≠ P[q]
            k ← π[k]
        se P[k + 1] = P[q]
            k ← k + 1
        π[q] ← k
    retorne π
```

> Computar-Função-Prefixo(): $O(m)$

```
Casamento-Padrões-KMP(T, P)
    n ← |T|
    m ← |P|
    π ← Computar-Função-Prefixo(P)
    q ← 0
    para i ← 1 até n
        enquanto q > 0 e P[q + 1] ≠ T[i]
            q ← π[q]
        se P[q + 1] = T[i]
            q ← q + 1
        se q = m
            imprima "P ocorre em T com deslocamento: ", i − m
            q ← π[q]
```

> Casamento-Padrões-KMP(): $O(n)$

> Portanto, o tempo total do algoritmo é $O(m + n)$

--- 

## Casamento de Padrões com Z

```
Casamento-Padrões-Z(T, P)
    S = P$T
    Computar todos os Zi para S
    retorne todos i − |P| − 1 tal que Zi = |P|
```

> Exemplo:
- P = ’ana’
- T = ’bananana’

Construimos S = ’ana$bananana’
Calculamos o vetor Z, valores iguais a 3 indicam a ocorrência de ’ana’

### Por que isto funciona?
- i − |P| − 1 mapeia índices de que para os índices de T
- Zi = |P| se, e somente se, a string iniciando em i casa com P
- Consumo de tempo: O(|P| + |T| + ZS), onde ZS é o tempo de computar o Zi para T. Este passo pode ser ineficiente.

---

Para computar todos os Zi para S.

Algoritmo ingênuo:
    Para cada posição:
        1 comparar caracter por caracter
        2 contar os casamentos

```
Função-z(S)
    n = |S|
    para i ← 1 até n
        enquanto i + Z[i] < n e S[Z[i]] == S[i + Z[i]]
            Z[i] ← Z[i] +1
```

> Exemplo:
- S = "aabxaayaab"
- Z = [0,1,0,0,2,1,0,3,1,0]

> Consumo de tempo: O(^2)
Vamos utilizar outra estratégia mais eficiente para computar Zi para S.

---

O algoritmo de pré-processamento iterativamente computa Zi.
A cada passo o algoritmo considera:
- Z2 . . . Zi−1, e
- os limites l (left) e r (right) do Z-box que se encontra mais a direita e que inicia-se em alguma posição entre 2 . . . i − 1.

Como resultado, o algoritmo devolve:
• Zi e os valores atualizados de l e r

1. Se i > r, explicitamente compute Zi comparando com o prefixo de S. Se o Zi > 0, então l = i e r = i + Zi − 1, que são os novos limites do Z-box mais a direita.
2. Se i ≤ r, ocorre a seguinte situação:

![tabela](i3.png)

A string S[i . . r] é rotulado com β e também ocorre em i′

Dois subcasos possíveis:
2a. Zi′ < |β| então Zi = Zi′,e as posições l e r não se alteram.

![tabela2](i4.png)

2b. Zi′ ≥ |β|, então S[i . . r] deve ser um prefixo de S e Zi ≥ |β| = r − i + 1.

![tabela3](i5.png)

então, compare os caracteres a partir da posição r + 1 de S com a posição iniciando em |β|+1 de S até que um mismatch ocorra. 
Digamos que o mismatch ocorra na posição q ≥ r+1. Então Zi recebe o valor q − i e atribua l = i e r = q − 1.

```
Função-z(S)
    n = |S|
    para i ← 2 até n
        se i > r então ▷ Caso 1
            l ← i, r ← i
            enquanto r ≤ n e S[r − l] == S[r ] faça r ← r +1
            Z[i] ← r − l, r ← r −1
        senão ▷ Caso 2
            i′ ← i − l + 1
            se Z[i′] < r − i +1 então Z[i] ← Z[i′] ▷ Caso 2a
            senão ▷ Caso 2b
                l ← i
                enquanto r ≤ n e S[r − l] == S[r ] faça r ← r +1
                Z[i] ← r − l +1, r ← r −1
    retorne Z
```