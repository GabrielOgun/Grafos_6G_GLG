# Grafos_6G_GLG
* Gabriel Kury Fonseca - **32153848**
* Gabriel Marques Gonçalves Almeida - **32066724**
* Leonardo Borim Silva - **32154410**

| _Status do Projeto_| Parte 1 |
|--------------------|---------|

## Proposta do Projeto
Nossa proposta consiste em desenvolver um grafo de relações entre indivíduos que tem como inspiração a [teoria dos 6 graus de separação](https://www.agendor.com.br/blog/seis-graus-de-separacao/#:~:text=nos%20comentários%20🙂-,O%20que%20é%20a%20teoria%20dos%20seis%20graus%20de%20separação,e%20empresas%20confirmaram%20essa%20hipótese.), visando quantificar a probabilidade de transmissão de infecções entre eles. Dado que constantemente interagimos com outras pessoas, cada pessoa é representada  por um vértice e a relação por uma aresta não direcionada, cujo peso é determinado pela porcentagem de probabilidade de transmissão. Essa porcentagem é calculada com base na frequência de contato diário entre os indivíduos envolvidos. No entanto, na parte 1 nós apenas estipulamos esse valor conforme contato no dia a dia e não por dados concretos pelos cálculos. Segue abaixo a modelagem inicial da base de dados construída para o projeto.
![Modelagem do Grafo ND do Projeto](https://github.com/GabrielOgun/Grafos_6G_GLG/blob/main/Desenho_Grafo.png)

## ODS - Objetivo de Desenvolvimento Sustentável - [Saúde e Bem Estar](https://odsbrasil.gov.br/objetivo/objetivo?n=3)
O projeto tem o foco principal de atender e auxiliar no estudo e combate à epidemias de doenças como às listadas no indicador 3.3 que define
> **Até 2030, acabar com as epidemias de AIDS, tuberculose, malária e doenças tropicais negligenciadas, e combater a hepatite, doenças transmitidas pela água, e outras doenças transmissíveis.**

Já que com esse projeto é possível analisar como uma doença pode se propagar dentro de uma rede de pessoas que tem algum grau de relação e, à partir dos dados obtidos da capacidade de transmissão da doença, observar e traçar um padrão de propagação da doença, sendo que este dado poderia ser usado para estudos científicos a respeito da doença e também no desenvolvimento de medidas de prevenção para evitar futuras epidemias ou medidas de segurança durante epidemias.
