# Subsequência Crescente Mais Longa

- Do inglês, Longest Increasing Sequence - LIS
- Dada uma sequência de números inteiros.
- Determinar o tamanho da maior subsequência, não necessariamente contígua, cujos elementos estão em ordem crescente.

- Seja n o tamanho da sequência, num[i] é o i-ésimo número.
- Seja LIS(i) o tamanho da subsequência crescente mais longa de tamanho i.
- Para encontrar a subsequência crescente mais longa para um certo num[i], é necessário computar LIS(i) para cada elemento num[i], 0 ≤ i ≤ n.

---

## Recorrência:
- seja LIS(i) o tamanho da subsequência crescente mais longa
de tamanho i.

$$
LIS(i) = 
\begin{cases} 
1, & \text{se } i = 0 \\ 
max{LIS(j) + 1}, & \text{onde } num[j] < num[i], para 0 <= j < i 
\end{cases}
$$

---

### Solução Recursiva:

```
LIS(i)
    se i = 0
        retorne 1
    senão
        maior = 1
        para j = 0 até i
            se num[j] < num[i]
                maior = max(maior, LIS(j) + 1)
        retorne maior

subsequencia crescente mais longa(num, n)
    maior = 1
    para i = 1 até n
        maior = max(maior, LIS(i))
    retorne maior
```

### Memoization (top-down):

```
LIS(i)
    se L[i] ̸= −1
        retorne L[i]
    senão se i = 0
        retorne L[i] = 1
    senão
        maior = 1
        para j = 0 até i
            se num[j] < num[i]
                maior = max(maior, LIS(j) + 1)
        retorne L[i] = maior

subsequencia crescente mais longa(num, n)
    maior = 1
    para i = 1 até n
        maior = max(maior, LIS(i))
    retorne maior
```

### Tabulation (bottom-up):

```
subsequencia crescente mais longa(num, n)
    para i = 1 até n
        L[i] = 1
    maior = 0
    para i = 1 até n
        para j = 0 até i
            se num[j] < num[i]
                L[i] = max(L[i], L[j] + 1)
        maior = max(maior, L[i])
    retorne maior
```