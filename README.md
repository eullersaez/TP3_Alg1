Trabalho prático 3 da disciplina de Algoritmos I

O trabalho proposto consistia em desenvolver um sistema computacional capaz de resolver o
problema de ajudar um jovem universitário em Nova Iorque a gastar a menor quantia possível
dentro do sistema de metrô da cidade. Basicamente o jovem tem direito a uma quantia de
descontos que vão se acumulando até uma quantidade D de escalas feitas nas estações, dentro
de um tempo T. Após esse tempo, é obrigatório reiniciar os descontos. Como o jovem sabe
que em alguns momentos pode esperar o tempo acabar em uma estação para reiniciar os
descontos, isso pode ajudá-lo a pagar um custo menor, pois quando ainda dentro do limite T
de tempo, porém já tendo se passado de D estações consecutivas aplicando os descontos
cumulativos, não vale a pena continuar seguindo dentro do limite de tempo, já que o preço
pago nessas estações será seu preço integral, o que aumentará o custo acumulado total.
Desse modo, é possível resolver o problema dado com o artifício da programação dinâmica,
sem a necessidade de fazer a mesma chamada recursiva diversas vezes, apenas consultando
uma posição de memória em vez de executar diversas pilhas de recursão. Logo, podemos
definir a equação de Bellman para calcular o custo de ir de uma dada estação EA (estação
atual) até a estação final, considerando que o desconto começa de uma estação ED (estação
do desconto) da seguinte forma: