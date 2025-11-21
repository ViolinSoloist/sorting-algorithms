Danilo Salmen Stocco - 16861501
Erik Min Soo Chung - 15450334

LINK PARA RELATÓRIO:
https://docs.google.com/document/d/1t7LfjXGAWvf93IhjtAK_N6gjeYtYipndhzALaI0oEyc/edit?usp=sharing

LINK PARA PLANILHA COM TABELINHA E GRÁFICO COM DADOS:
https://docs.google.com/spreadsheets/d/1r1YK6LzX1DBLR9PH7Ghol0iBDrMqGy1KzylE7ADGurM/edit?gid=781478231#gid=781478231



INSTRUÇÕES DE COMPILAÇÃO EXECUÇÃO DE PROGRAMA:

Em ambientes possíveis de usar Makefile:
make run -> compila e já executa o programa
make clean -> limpa arquivo de execução

Compilar e executar manualmente:
gcc main.c fila.c -o main -Wall
./main

INSTRUÇÕES PARA USO DO PROGRAMA (Necessário editar parte main() do código para testar diferentes sorts):
* ir para função main() (linha 963)
* editar a chamada da função relatório()
* inserir número que corresponde ao método de ordenação que deseja verificar
* isso gerara um "mini relatório" no terminal exibindo as informações de cada sort
* (é possível verificar todas as informações na tabelinha de dados)