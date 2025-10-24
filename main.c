//importando bibliotecas
#include <stdio.h>              
#include <stdbool.h>            
#include <stdlib.h>             
#include <time.h>     

#define MIN_RAND 1
#define MAX_RAND 100000

#define ui unsigned int

/**
 * @attention em todos os sorts, criar e cuidar de contadores de:
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


// ------------------------------------------
//            FUNÇÕES AUXILIARES
// ------------------------------------------
/**
 * @note testado, mas ainda assim é melhor testar com mais exemplos
 * @attention tem que ter a mesma quantidade de free()'s que tem essa função chamada na main
 * @details como devemos testar cada método de ordenação com diferentes quantidades de vetores com diferentes tamanhos e modos,
 * é inteligente fazer uma função que trate a geração desses vetores
 * recebe o tamanho do vetor @param n e o @param modo de geração (aleatorio, ordenado e inversamente ordenado)
 * @return ponteiro pra array de inteiros alocados dinamicamente.
 */
int* make_vector(int n, int modo) // 1 -> aleatorio, 2 -> ordenado 3 -> inverso
{
    int* v = (int*)calloc(n, sizeof(int)); // v inicia com 0 em todos index, eu acho
    if (v != NULL)
    {    
        switch (modo)
//  acho que a gente não precisa fazer uma função pros vetores
//  a gente pdoe criar eles com malloc, no caso os 4 vetores de 100 1000 e tal e resetar o valor deles pra cada sort
//  
// :(( VOU ESCREVER TUDO EM BRAINFUCK MESMO FODASE >...++-->;>><<..<++-->>>.__ (HLO WORLD BLYAT)

// sim sim, a função seria só pra deixar mais claro, mas seria só pra gerar esses 4 vetores, em vez de deixar na main
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

/**
 * @brief função que realiza swap entre dois registros de um vetor
 * recebe o vetor, e as posições em index (0-indexado) que serão trocadas de lugar
 * @
 */
void swap(int* v, int a, int b)
{
    int temp = v[a];
    v[a] = v[b];
    v[b] = temp;
}

void print_vetor(int* v, int n) {
    for(int i=0; i<n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}


/**
 * $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
 *                 FUNÇÕES DE ORDENAÇÃO 
 * $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
 * 
 * @details cada função de ordenação @returns uma struct, contendo:
 * - ponteiro para vetor pós-ordenação (alocado dinamicamente)
 * - inteiro que representa o número de comparações realizadas
 * - inteiro representando número de movimentações de registros (provavelmente swaps?)
 * - float representando tempo de execução até terminar a ordenação
 * 
 * @attention uso de struct não é necessário, mas ajuda a modularizar o código
 * @deprecated por enquanto, é só isso, mas é importante lembrar que a gente vai ter que
 * guardar todas essas informações para todos os tamanhos de vetores e para cada tamanho, 
 * todas as formas de registros originais (ordenado, aleatório, inversamente ordenado)
*/

typedef struct info_ {
    int* sorted_array;
    ui comparisons;
    ui swaps;
    float execution_time;
}Info;


Info bubble_sort(int* v, int n)
{
    ui comparisons = 0;
    ui swaps = 0;
    clock_t inicio = clock(); //inicio da marcação de tempo


    for(int i=0; i<n-1; i++)
    {
        bool teve_swap = false;

        for(int j=0; j<n-1-i; j++)
        {          
            comparisons++; // if que verifica se o registro atual é maior que o próximo registro
            if(v[j] > v[j+1]) {
                swaps++; // sempre que tem swap incrimenta
                swap(v, j, j+1);
                teve_swap = true;
            }
        }
        if (!teve_swap) break; //se nenhum movimento é feito quer dizer que já está ordenado
    }

    clock_t fim = clock(); // fim da marcação de tempo
    double tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC;

    Info bbs_info = {v, comparisons, swaps, tempo_gasto};
    return bbs_info;
}


int main()
{   
    // NOTAS PARA DANILO: TÁ FUNCINOANDO AGORA! TESTE COM DIFERENTES TAMANHOS DE N,
    int n = 10000;
    int* vetor = make_vector(n, 1); //TESTE TAMBÉM COM DIFERENTES TIPOS DE DE MODOS (1, 2 OU 3) (ALEATORIO, ORDENADO, INVERSAMENTE ORDENADO)
    
    // print_vetor(vetor, n);

    Info bbs = bubble_sort(vetor, n);

    // print_vetor(bbs.sorted_array, n);
    printf("Comparacoes: %u, swaps: %u, tempo decorrido: %.3lf %s.\n", bbs.comparisons, bbs.swaps, (bbs.execution_time < 0.1 ? bbs.execution_time * 1000 : bbs.execution_time), (bbs.execution_time < 0.1 ? "ms" : "s"));

    free(vetor);
    return 0;
}