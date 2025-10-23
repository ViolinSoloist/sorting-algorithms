//importando bibliotecas
#include <stdio.h>              
#include <stdbool.h>            
#include <stdlib.h>             
#include <time.h>     

#define MIN_RAND 1
#define MAX_RAND 69420

//  acho que a gente não precisa fazer uma função pros vetores
//  a gente pdoe criar eles com malloc, no caso os 4 vetores de 100 1000 e tal e resetar o valor deles pra cada sort
//  
// :(( VOU ESCREVER TUDO EM BRAINFUCK MESMO FODASE >...++-->;>><<..<++-->>>.__ (HLO WORLD BLYAT)

// sim sim, a função seria só pra deixar mais claro, mas seria só pra gerar esses 4 vetores, em vez de deixar na main
/**
 * @attention a gente vai precisar, em todos os sorts, criar e cuidar de contadores de:
 * número de comparações
 * número de movimentações de registro
 * tempo de execução (usar biblioteca <time.h>)
*/ 

/**
 *  @attention a gente também vai precisar considerar vetores de tamanho 100, 1000, 10000 e 100000 elementos
 * mas são três tipos de vetores
 *  1. ordenados
 *  2. Inversos
 *  3. aleatórios
 * 
 *  Tem duas opções para isso (pode ter outras opções, mas por enquanto só pensei nessas duas
 * que parecem ser as melhores, se você tiver outra idea melhor pd falar tmb) 8==========D
 *  @details a gente cria uma função que cria um vetor de tamanho N com alocação dinâmica (retorna ponteiro de ponteiro)
 * e da free conforme a gente for usando e deixando de usar, e usa stdlib pra ir preenchendo os vetores com números aleatórios
 * (não importa quando for ordenado ou inverso porque a gente faz um for loop incrementando ou decrementando, não faz diferença)
 * 
 *  @details criamos novos arquivos de entrada (ex: 1.in, 2.in) que são literalmente uma linha com a quantidade de números
 * e na hora de executar o código a gente passa o arquivo como entrada, em vez de fornecer a entrada do teclado
 *  (Ex: ./a.out < 1.in) no linux
 *  Mas a gente teria que pedir pra IA gerar os arquivos
 *  MAS não teria dor de cabeça de mexer com ponteiros e principalmetne lidar com todos os free()'s que a gente vai ter que
 * lembrar e usar
*/

// vou deixar anotado todos os sorts, a gente vai marcando no final de cada linha os completos
/**
 * Bubble Sort
 * Selection Sort
 * Insertion Sort
 * Shell Sort
 * Quick Sort
 * Heap Sort
 * Merge Sort
 * Contagem dos Menores
 * Radix Sort
*/


/**
 * @attention AINDA NÃO TESTEI
 * @attention tem que ter a mesma quantidade de free()'s que tem essa função chamada na main
 */
int* make_vector(int n, int modo) // 1 -> aleatorio, 2 -> ordenado 3 -> inverso
{
    int* v = (int*)calloc(n, sizeof(int)); // v inicia com 0 em todos index, eu acho
    if (v != NULL) {
        // melhor fazer o tratamento de erro pro algo que for chamar essa função, em vez de fazer aqui mesmo
        // porque se for erro ele vai retornar o vetor que é NULL
        
        switch (modo)
        {
            case 1: //aleatorio
                // TODO <stdlib.h> rand() preencher com números aleatórios
                srand(time(NULL)); //seed 
                for(int i=0; i<n; i++) {
                    int rand_num = (rand() % MAX_RAND) + MIN_RAND;
                    v[i] = rand_num;
                }

            break;

            case 2: //ordenado {1, 2, 3, 4, 5, ... , 98, 99}
                for (int i=0; i<n; i++) {
                    v[i] = i+1;
                }
            break;

            case 3: // inversamento ordenado {99, 98, 97, ... , 3, 2, 1}
                for (int i=n-1; i>=0; i--) {
                    v[i] = n-i;
                }
            break;

            default:
                fprintf(stderr, "Modo inválido.\n");
            break;
        }

    }
    return v;
}

void print_vetor(int* v, int n) {
    for(int i=0; i<n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

int main()
{
    int* vetor = make_vector(10, 3);
    
    print_vetor(vetor, 10);

    free(vetor);

    return 0;
}