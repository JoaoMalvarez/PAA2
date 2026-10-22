# Números de Fibonacci
$$
fib(n) = 
\begin{cases} 
0, & \text{se } n = 0 \\ 
1, & \text{se } n = 1 \\ 
fib(n - 1) + fib(n - 2), & \text{se } n > 1 
\end{cases}
$$

---

### Solução Recursiva:
```
fib(n)
    se n = 0 ou n = 1
        retorne n
    senão
        retorne fib(n - 1) + fib(n - 2)
```

---

#### Tabela

fib(n) | 0 | 1 | 1 | 2 | 3 | 5 |
| --- | --- | --- | --- | --- | --- | --- |
n | 0 | 1 | 2 | 3 | 4 | 5 |

---

### Versão Top-Down:
```
fib(n)
    se memo[n] != -1 -> caso já calculado
        retorne memo[n]
    senão se n = 0 ou n = 1
        memo[n] = n
    senão 
        memo[n] = fib(n - 1) + fib(n - 2)
    retorne memo[n]
```

> Complexidade: O(n)

---

#### Tabela

n | memo[n]
| --- | --- |
0 | 0
1 | 1
2 | 1
3 | 2
4 | 3
5 | 5

--- 

### Versão Bottom-Up:

> Utilizando uma memória auxiliar, inicie os casos base.
> - Casos base fib(0) = 0 e fib(1) = 1.
> - Obtenha o valor de fib(i) = fib(i-1) + fib(i-2), para i entre 2 .. n.
> - Devolva o fib(n)
```
fib(n)
    f[0] = 0
    f[1] = 1
    para i = 2 até n
        f[i] = f[i - 1] + f[i - 2]
    retorne f[n]
```

> Complexidade: O(n)

---

#### Tabela

n | memo[n]
| --- | --- |
0 | 0
1 | 1
2 | 1
3 | 2
4 | 3
5 | 5

--- 