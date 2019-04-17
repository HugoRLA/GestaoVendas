# Trabalho prático de Sistemas Operativos

# Gestão de Vendas


## 1 Descrição

Neste trabalho pretende-se construir um protótipo de um sistema de gestão de inventário e vendas. O
sistema deverá ser constituído por vários programas: manutenção de artigos, servidor de vendas, cliente
de vendas, e agregador de dados.

### 1.1 Manutenção de artigos

Este programa deverá permitir inserir novos artigos (especificando o nome e preço de venda), ou alterar
atributos de um dado artigo (nome ou preço). Cada artigo tem um código numérico, atribuído na criação
como o próximo de uma sequência (1, 2, 3,... ). Para o acesso a um artigo no ficheiro ARTIGOS
poder ser feito usando o código como índice, as entradas devem ter um tamanho fixo. Sendo o nome
de tamanho variável, este atributo no ficheiro de artigos deve conter apenas “referências” (e.g., posição)
onde se encontram num ficheiro STRINGS, em separado, contendo os respectivos nomes.
É aceitável que o ficheiro STRINGS contenha nomes obsoletos, desperdiçando algum espaço, de
forma a que se possa apenas acrescentar conteúdo mesmo aquando da alteração de nomes.
Este programa recebe todo o seu input pelo seu stdin, lendo linhas de texto com o formato do exemplo
seguinte:

~~~
$ ma
i <nome> <preço> --> insere novo artigo, mostra o código
n <código> <novo nome> --> altera nome do artigo
p <código> <novo preço> --> altera preço do artigo
...
<EOF>
~~~
### 1.2 Servidor de vendas

Este programa deve controlar stocks, receber pedidos do cliente de vendas, e registar as vendas efec-
tuadas. A quantidade em stock de cada artigo deverá ser mantida num único ficheiro STOCKS, para
todos os artigos. Cada venda efectuada deverá ser registada, acrescentando uma entrada a um ficheiro
VENDAS, contendo código, quantidade e montante total da venda.
O servidor de vendas deve ainda providenciar para correr o agregador a pedido, fazendo com que este
receba o intervalo (para ser agregado) do ficheiro de vendas desde a última agregação, e fazendo com que
o resultado da agregação seja escrito num ficheiro cujo nome reflecte o momento em que a agregação foi
solicitada (e.g., 2019-03-29T14:23:56).


### 1.3 Cliente de vendas

O cliente de vendas deve interagir com o servidor de vendas, solicitando-lhe a execução de (uma sequên-
cia de) operações que se distinguem facilmente pelo número de parâmetros introduzidos. Uma das
operações retorna a quantidade em stock e o preço de um artigo (identificado pelo código). A outra
operação permite efectuar vendas ou entrada em stock, especificando o código e quantidade (negativa ou
positiva, respectivamente):


~~~
$ cv
<código_numérico> --> mostra no stdout stock e preço
<código_numérico> <quantidade> --> actualiza stock e mostra novo stock
...
<EOF>
~~~

O sistema deverá permitir a execução concorrente de vários clientes de vendas. Teste o seu trabalho
com dois ou mais clientes a "martelarem" simultaneamente o mesmo artigo!
A interação dos utilizadores com este cliente de vendas é feita apenas pelostdin, sendo os resultados
retornados nostdout. Por favor não invente, não escreva mais nenhuma mensagem para o stdout. Inici-
almente poderá querer testar manualmente o servidor de vendas mas depois não se esqueça de criar um
ficheiro contendo (muitos, centenas ou milhares de) comandos de compra e venda de um artigo, lançar
uma dúzia de clientes que lêem esse ficheiro e verificar pelo stock final se alguma operação se "perdeu".

### 1.4 Agregador

O programa agregador funciona como filtro. Recebe pelo stdin entradas no formato do ficheiro de ven-
das, até end-of-file. Nessa altura produz para o stdout os dados agregados de cada artigo com vendas
efectuadas, contendo o código do artigo, a quantidade total e o montante total de vendas do artigo res-
pectivo (mantendo o formato do ficheiro de vendas).

## 2 Alguns aspectos valorizados

### 2.1 Caching de preços

No servidor de vendas, para evitar o acesso constante ao ficheiro ARTIGOS, e tendo em conta que vários
artigos populares serão continuamente requisitados, mantenha em memória a informação de preços que
foi lida deste ficheiro, tendo cuidado com a sua invalidação por uma alteração de preços. Ou seja, quando
são efectuadas alterações a preços de artigos, tal deve comunicado ao servidor de vendas, para este poder
usar os preços actualizados.

### 2.2 Agregação concorrente

Para permitir explorar agregação concorrente, faça com que o servidor de vendas ponha a correr vá-
rias instâncias do programa agregador, dividindo o intervalo a agregar por estas, e fazendo com que os
resultados das sub-agregações sejam por sua vez agregados.

### 2.3 Compactação do ficheiro STRINGS

Para reduzir o desperdício de espaço, quando este superar os 20% do ficheiro, deverá ser feita a compac-
tação para um novo ficheiro e ajustadas as posições no ficheiro de artigos. Esta operação deverá ser a
última a acrescentar ao seu trabalho.


Lembre-se que "a verdade" está nos ficheiros e que esses ficheiros poderão ter dimensão "muito
grande". Em memória estará a cache. Isto facilitará a recuperação do serviço após um crash (oukill) do
servidor.


