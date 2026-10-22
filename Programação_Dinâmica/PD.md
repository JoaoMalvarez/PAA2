# Programação dinâmica

## Quando se aplica:
- Problemas de otimização
- Subproblemas são recorrentes
- Combina soluções de subproblemas

> Ideia: armazenar a solução de problemas para a resolução de subproblemas futuros.

---

## Características:
- Existência de subestrutura ótima: as soluções ótimas do problema contém soluções ótimas dos subproblemas
- Fórmula de recorrência: descreve a relação entre as soluções ótimas dos subproblemas.
- Sobreposição de subproblemas: a solução ótima de um subproblema é usada várias vezes mas calculada uma vez!

--- 

## Duas estratégias:
- Top down (memoization)
- Bottom-up (Tabulation)