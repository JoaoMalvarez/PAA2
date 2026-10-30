# Longest Common Subsequence (LCS)

O problema do **Longest Common Subsequence (LCS)** é um problema clássico de Ciência da Computação e Análise de Algoritmos, amplamente utilizado em bioinformática (para alinhamento de sequências de DNA/RNA) e em ferramentas de comparação de arquivos (como o comando `diff`).

## 1. Definição do Problema

Dadas duas sequências:

* $X = \langle x_1, x_2, \dots, x_m \rangle$
* $Y = \langle y_1, y_2, \dots, y_n \rangle$

Deseja-se encontrar uma subsequência de comprimento máximo que seja comum a ambas as sequências $X$ e $Y$.

> **Diferença entre Subcadeia e Subsequência:**
>
> * **Subcadeia (*Substring*):** Os elementos precisam ser contíguos.
> * **Subsequência (*Subsequence*):** Os elementos mantêm a ordem relativa, mas **não precisam ser contíguos**.

### Exemplo

Dadas as cadeias de DNA:

* $X = \text{ATCTGAT}$
* $Y = \text{TGCATTA}$

Uma das maiores subsequências comuns é **`TCTA`** (comprimento 4).

#### Alinhamento Visual

```
AT_C_TGAT
 | | | |
_TGCAT_A_
```

## 2. Estrutura Genética / Subestrutura Ótima

A Programação Dinâmica é aplicável porque o problema possui a propriedade de **subestrutura ótima**.

Seja $Z = \langle z_1, z_2, \dots, z_k \rangle$ a LCS das sequências $X = \langle x_1, x_2, \dots, x_m \rangle$ e $Y = \langle y_1, y_2, \dots, y_n \rangle$:

1. **Se** $x_m = y_n$**:** Então $z_k = x_m = y_n$, e $Z_{k-1}$ é a LCS de $X_{m-1}$ e $Y_{n-1}$.
2. **Se** $x_m \neq y_n$ **e** $z_k \neq x_m$**:** Então $Z$ é a LCS de $X_{m-1}$ e $Y$.
3. **Se** $x_m \neq y_n$ **e** $z_k \neq y_n$**:** Então $Z$ é a LCS de $X$ e $Y_{n-1}$.

### Formulação Recorrente

Seja $c[i, j]$ o comprimento da LCS dos prefixos $X_i$ e $Y_j$:

$$
c[i, j] = \begin{cases} 0 & \text{se } i = 0 \text{ ou } j = 0 \\ c[i-1, j-1] + 1 & \text{se } i, j > 0 \text{ e } x_i = y_j \\ \max(c[i-1, j], c[i, j-1]) & \text{se } i, j > 0 \text{ e } x_i \neq y_j \end{cases}
$$

## 3. Algoritmo em Programação Dinâmica

Construímos uma tabela $c[0..m, 0..n]$ de baixo para cima (*bottom-up*). Também podemos utilizar uma matriz de ponteiros/direções $b[1..m, 1..n]$ para guardar de onde veio cada valor e reconstruir a resposta.

### Pseudo-código: Construção da Tabela

```
LCS(X, Y, m, n)
 1. para i = 0 até m faça:
 2.     c[i, 0] = 0
 3. para j = 0 até n faça:
 4.     c[0, j] = 0
 5. para i = 1 até m faça:
 6.     para j = 1 até n faça:
 7.         se x[i] == y[j] então
 8.             c[i, j] = c[i-1, j-1] + 1
 9.             b[i, j] = "↖"
10.         senão se c[i-1, j] >= c[i, j-1] então
11.             c[i, j] = c[i-1, j]
12.             b[i, j] = "↑"
13.         senão
14.             c[i, j] = c[i, j-1]
15.             b[i, j] = "←"
16. retorne c e b
```

## 4. Recuperação da Subsequência

Após preencher a matriz $b$, a subsequência em si é reconstruída de trás para a frente (partindo de $b[m, n]$ até $i=0$ ou $j=0$).

### Pseudo-código: Recuperação Recursiva

```
RECUPERA-LCS(b, X, i, j)
 1. se i == 0 ou j == 0 então
 2.     retorne
 3. se b[i, j] == "↖" então
 4.     RECUPERA-LCS(b, X, i-1, j-1)
 5.     imprime(X[i])
 6. senão se b[i, j] == "↑" então
 7.     RECUPERA-LCS(b, X, i-1, j)
 8. senão
 9.     RECUPERA-LCS(b, X, i, j-1)
```

## 5. Análise de Complexidade e Otimização

* **Tempo de Execução:** $\mathcal{O}(m \times n)$ para preencher as matrizes $c$ e $b$.
* **Tempo de Reconstrução:** $\mathcal{O}(m + n)$ para rastrear o caminho de volta.
* **Espaço de Memória:** $\mathcal{O}(m \times n)$ no algoritmo padrão.

### Otimizações de Espaço:

1. **Remoção da Matriz** $b$**:** É possível recuperar a solução sem a matriz $b$, consultando apenas os valores adjacentes da matriz $c$ ($c[i-1, j-1]$, $c[i-1, j]$ e $c[i, j-1]$) em tempo $\mathcal{O}(m + n)$.
2. **Apenas Comprimento:** Se a intenção for apenas obter o **tamanho** da LCS, é necessário guardar apenas duas linhas da matriz $c$ por vez (a atual e a anterior), reduzindo a memória para $\mathcal{O}(\min(m, n))$.

---

## Desafio: 
Implementar o algoritmo de programação dinâmica do problema *Longest Common Subsequence* utilizando uma matriz 2 linhas por $n+1$ colunas, em que $n = |Y|$. O algoritmo deve montar a matriz de programação dinâmica, e também recuperar o alinhamento das sequências.