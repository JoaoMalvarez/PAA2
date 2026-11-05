# Exercícios
## 1. (MELHOR MOMENTO PARA COMPRA E VENDER AÇÕES) 

Você recebe um vetor precos, onde precos[i] é o preço de uma determinada ação no i-ésimo dia. Você deseja maximizar seu lucro escolhendo um único dia para comprar uma ação e escolhendo um dia diferente no futuro para vender essa ação. Retorne o lucro máximo que você pode obter com essa transação. Se você não puder obter nenhum lucro, retorne 0.

> Exemplo 1:
```
Entrada: precos = [7,1,5,3,6,4]
Saída: 5
Explicação:
    Compre no dia 2 (preço = 1) e venda no dia 5 (preço = 6), o lucro é igual a 6 - 1 = 5.Note que comprar no dia 2 e vender no dia 1 não é permitido pois você deve comprar antes de vender.
```

> Exemplo 2:
```
Entrada: precos = [7,6,4,3,1]
Saída: 5
    Explicação: Nesse caso, nenhuma transação é realizada e o lucro máximo é igual a 0.
```

### Restrição:
- 1 ≤ precos.length ≤ 105
- 0 ≤ precos[i] ≤ 104

---

## 2. (CUSTO MÍNIMO PARA SUBIR ESCADAS) 

Você recebe um vetor de inteiros chamado "custo", onde custo[i] representa o custo do i-ésimo degrau em uma escada. Após pagar o custo, você pode subir um ou dois degraus. Você pode começar tanto no degrau de índice 0 quanto no degrau de índice 1. Retorne o custo mínimo para chegar ao topo do piso.

> Exemplo 1:
```
Entrada: custo = [10,15,20]
Saída: 15
Explicação: Você começará no índice 1.
    - Pague 15 e suba dois degraus para chegar ao topo.
    - O custo total é 15.
```

> Exemplo 2:
```
Entrada: custo = [1,100,1,1,1,100,1,1,100,1]
Saída: 6
Explicação: Você começará no índice 0.
    - Pague 1 e suba dois degraus para chegar ao índice 2.
    - Pague 1 e suba dois degraus para chegar ao índice 4.
    - Pague 1 e suba dois degraus para chegar ao índice 6.
    - Pague 1 e suba um degrau para chegar ao índice 7.
    - Pague 1 e suba dois degraus para chegar ao índice 9.
    - Pague 1 e suba um degrau para chegar ao topo.
    - O custo total é 6.
```

### Restrição
- 2 ≤ custo.length ≤ 1000
- 0 ≤ custo[i] ≤ 999

---

## 3. (JOGO DO DIVISOR) 
Alice e Bob jogam em turnos um jogo, com Alice começando primeiro. Inicialmente, há um número n no quadro-negro. Em cada turno do jogador, esse jogador faz uma jogada consistindo em:
    - Escolher qualquer x com 0 < x < n e n % x == 0.
    - Substituir o número n no quadro-negro por n − x.
    - Além disso, se um jogador não puder fazer uma jogada, ele perde o jogo.
Retorne verdadeiro somente se Alice vencer o jogo, assumindo que ambos os jogadores jogam de forma otimizada.

> Exemplo 1:
```
Entrada: n = 2
Saída: verdadeiro
Explicação: Alice escolhe 1 e Bob não tem mais jogadas disponíveis.
```

> Exemplo 2:
```
Entrada: n = 3
Saída: falso
Explicação: Alice escolhe 1, Bob escolhe 1 e Alice não tem mais jogadas disponíveis.
```

---

## 4. (LADRÃO DE CASAS) Você é um ladrão profissional planejando roubar casas ao longo de uma rua. Cada casa tem uma certa quantia de dinheiro guardada, e a única restrição que impede você de roubar todas elas é que casas adjacentes possuem sistemas de segurança conectados, que automaticamente acionam a polícia se duas casas adjacentes forem roubadas na mesma noite. Dado um vetor de inteiros chamado nums, que representa a quantia de dinheiro em cada casa, retorne o valor máximo que você pode roubar esta noite sem alertar a polícia.

> Exemplo 1:
```
Entrada: nums = [1,2,3,1]
Saída: 4
Explicação: Roube a casa 1 (dinheiro = 1) e depois roube a casa 3 (dinheiro = 3). 
    Quantidade total que você pode roubar = 1 + 3 = 4.
```

> Exemplo 2:
```
Entrada: nums = [2,7,9,3,1]
Saída: 12
Explicação: 
        Roube a casa 1 (dinheiro = 2),
        roube a casa 3 (dinheiro = 9) e
        roube a casa 5 (dinheiro = 1).
    Quantidade total que você pode roubar = 2 + 9 + 1 = 12.
```
### Restrição
• 1 ≤ nums.length ≤ 100
• 0 ≤ nums[i] ≤ 400