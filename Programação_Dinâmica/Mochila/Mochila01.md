# Mochila 0/1
> Basicamente, ou o item vai entrar totalmente na mochila ou ela não vai entrar (0 = não entra, 1 = entra totalmente). Não existe dividir o item para entrar. Então o que vai fazer é decidir quais itens vão entrar.

## Recursão:

Caso base:
- Se a capacidade da mochila ou a quantidade de itens for zero, então o valor máximo é zero.
- Senão há duas opções: incluir ou não incluir o item na mochila.

### Caso 1: A solução ótima inclui o item sn.
> O resto da solução inclui soluções ótimas para os subproblemas da mochila em que os itens 's1', · · · , 'sn' − 1 são dados (mesmos pesos e valores que antes), e para o qual a capacidade da mochila agora é 'W' − 'wn'.

### Caso 2: A solução ótima não inclui o item sn.
> A solução apenas inclui soluções ótimas para os subproblemas da mochila em que os itens 's1', · · · , 'sn' − 1 são dados (mesmos pesos e valores que antes), e para o qual a capacidade da mochila é 'W'.

---

## Subestrutura ótima
Podemos generalizar esta observação por considerar o sub-problema onde os itens 's1', 's2', · · · , 'si' são colocados na mochila de capacidade 'W'. Denote F(i, W) o valor máximo para este problema, então temos a seguinte recorrência:

$$
F(i, W) = 
\begin{cases} 
0, & \text{se } i = 0 ou W ≤ 0 \\ 
F(i - 1, W), & \text{se } wi > W \\ 
max{F(i − 1, W), F(i − 1, W − wi) + vi}, & \text{se } wi ≤ W 
\end{cases}
$$

> O valor de F(n, W) pode ser encontrado computando cada entrada F(i, c), para 0 ≤ 'i' ≤ 'n', e 0 ≤ 'c' ≤ 'W'

---     

## Solução Recursiva:

```
maior_valor(n, W) 
    se n < 0 ou W ≤ 0
        retorne 0
    se w[n] > W
        retorne maior_valor(n - 1, W)
    senão
        retorne max{maior_valor(n - 1, W), maior_valor(n - 1, W - w[n]) + v[n]}x
```

## Memoization (Top-Down):

```
maior_valor(n, W)
    se n < 0 ou W ≤ 0
        retorne 0
    se M[n][W] ̸= −1
        retorne M[n][W]
    se w[n] > W
        M[n][W] = maior valor(n − 1, W)
    senão
        M[n][W] = max{maior valor(n − 1, W), maior valor(n − 1, W − w[n]) + v[n]}
    retorne M[n][W]
```

## Tabulation (Bottom-Up):

```
maior valor(n, W)
    ▷ Declare matriz M[n][W] e inicialize com 0.
    para i = 1 até n
        para j = 1 até W
            ▷ Se o peso do item atual é maior que a capacidade W.
            se w[i] > j
                M[i][j] = M[i − 1][j]
            ▷ Verifica se inclui ou não o item na mochila.
            senão
                M[i][j] = max{M[i − 1][j], M[i − 1][j − w[i]] + v[i]}  
    retorne M[n][W]
```