# INFOS

## Dados:
> Uma mochila que possui uma certa capacidade W (admite um peso).
> Um conjunto de n objetos distintos, enumerados de 1 a n, cada um com um certo valor v1, v2, · · · , vn e peso w1, w2, · · · , wn.

## Objetivo:
> Maximizar o valor do conjunto de objetos dentro da mochila respeitando a capacidade.

## Há duas variações para o problema da mochila:
> Mochila fracionária
> Mochila binária ou 0 − 1

## Problema da Mochila
> Ambos tem sub-estrutura ótima
> O problema da mochila fracionária tem solução gulosa, o problema da mochila binária não

### Mochila Fracionária
> Ordene os itens por 'valor'/'peso' em ordem decrescente
> Começando em i = 1 coloque na mochila o máximo do item i que estiver disponível e for possível
> Se a capacidade da mochila permitir passe para o próximo item