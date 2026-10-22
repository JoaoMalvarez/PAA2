# Problema do Troco

## Problema
> Dar o troco de valor 'T', usando o menor número de moedas possível.

Dado um valor para o troco 'T', e um conjunto 'M' de 'n' moedas, cada um com um valor 'mi', determinar a quantidade mínima de moedas que somadas resultam no valor 'T'.

--- 

## Observação: 
> Uma moeda 'mi' pode ser utilizada diversas vezes na solução.

---

## Recorrência:
```
conta_moedas(T) = 
\begin{cases} 
0, & \text{se } T = 0 \\ 
∞, & \text{se } T < 0 \\ 
min{conta_moedas(T - mi) + 1}, & \text{se } T > 0 
\end{cases}
```

---

### Solução Recursiva:

```
conta moedas(T)
    se T == 0
        retorne 0
    se T < 0
        retorne ∞
    menor = ∞
    para i = 1 até n
        menor = min(menor, conta moedas(T - M[i]) + 1)
    retorne menor
```

### Top-Down:

```
conta moedas(T)
    se T == 0
        retorne 0
    se T < 0
        retorne ∞
    se memo[T] ̸= −1
        retorne memo[T]
    menor = ∞
    para i = 1 até n
        menor = min(menor, conta moedas(T - M[i]) + 1)
    retorne memo[T] = menor
```

### Bottom-Up:

```
conta moedas(T)
    para i = 1 até T
        troco[i] = ∞
    troco[0] = 0
    para i = 1 até T
        para j = 1 até n
            se i >= M[j]
                troco[i] = min(troco[i], troco[i − M[j]] + 1)
    retorne troco[T]
```
