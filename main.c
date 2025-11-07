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
 * que parecem ser as melhores, se você tiver outra idea melhor pd falar tmb)
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
 * Bubble Sort (feito)
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
 * recebe o tamanho do vetor @param n numero de elementos @param modo 1-aleatorio, 2-ordenado e 3-inversamente ordenado
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

int medianadeTres(int lim) // quick sort
{
    int n1 = rand() % lim;
    int n2 = rand() % lim;
    int n3 = rand() % lim;

    if((n1 <= n2 && n2 <= n3) || (n3 <= n2 && n2 <= n1)){
        return n2;
    }
    else if((n2 <= n1 && n1 <= n3) || (n3 <= n1 && n1 <= n2)){
        return n1;
    }
    else{
        return n3;
    }
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
    double execution_time;
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


/**
* @deprecated
*/
Info quick_sort2(int* v, int inf, int sup){  //quick sort dps da primeira chamada


    // int aux;

    int indiceMediana = medianadeTres(sup);
    int pivo = v[indiceMediana];

    int i = inf;
    int j = sup;
    do{
        while(v[i] < pivo){
            i++;
        }
        while(v[j] > pivo){
            j--;
        }

        if(i <=j){
            swap(v, i, j);
            i++;
            j++;
        }
    }while(i<j);
    if(j>inf){
        quick_sort2(v, inf, j);
    }
    if(i<sup){
        quick_sort2(v, i, sup);
    }
    // retornar struct Info ou definir a função para retornar void ou outra coisa
}

/**
* @deprecated
* arrumar função de index para pivo (retornar a posição cujo valor seja a mediana, não a mediana do index)
* revisar variaveis não usadas no código
* função quick_sort 2 define retorno da struct Info mas não retorna
* testar código para ver se está certo e testar para diferentes tamanhos de n e modos (aleatorio, ordenado, inversamente ordenado)
*/
Info quick_sort(int* v, int inf, int sup){  //mandar inf=0 quando chamar a funcao
    ui comparisons = 0;
    ui swaps = 0;
    clock_t inicio = clock(); //inicio da marcação de tempo

    //int aux; que variavel é essa? pra que serve? tá acusando como "unused variable"

    int indiceMediana = medianadeTres(sup);
    int pivo = v[indiceMediana];

    int i = inf;
    int j = sup;
    do{
        while(v[i] < pivo){
            comparisons++;
            i++;
        }
        while(v[j] > pivo){
            comparisons++;
            j--;
        }

        if(i <=j){
            swap(v, i, j);
            swaps++;
            i++;
            j++;
        }
    }while(i<j);
    if(j>inf){
        quick_sort2(v, inf, j);
    }
    if(i<sup){
        quick_sort2(v, i, sup);
    }

    clock_t fim = clock(); // fim da marcação de tempo
    double tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC;
    Info qsort = {v, comparisons, swaps, tempo_gasto};
    return qsort;
}



// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

// PROCEDIMENTO (FUNÇÃO QUE NÃO RETORNA NADA) QUE VAI FAZER UM MINI "RELATORIO"
// SORTAR PARA DIFERENTES N E MODOS

// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

void relatorio(int id_sort) /** @param recebe id de qual sort vai ser analisado*/
{
    const int tamanhos_de_teste[4] = {100, 1000, 10000, 100000};

    printf("\033[2J\033[H"); // limpa a tela

    switch (id_sort)
    {
    case 1:
        printf("BUBBLE SORT\n\n");
        break;

    default:
            fprintf(stderr, "ID de sort inválido.\n");
            return;
    }

    printf("====================\n");
    printf("ELEMENTOS ORDENADOS:\n");
    printf("====================\n\n");

    for (int i=0; i<4; i++) // ITERA POR TODOS OS TAMANHOS DE VETOR QUE PRECISAMOS TESTAR
    {
        printf("Tamanho do vetor: %d\n", tamanhos_de_teste[i]);

        int* v = make_vector(tamanhos_de_teste[i], 2);

        switch (id_sort)
        {
            case 1: {//bubble sort
                Info bbs = bubble_sort(v, tamanhos_de_teste[i]);
                printf("Comparacoes: %u\nSwaps: %u\nTempo decorrido: %.3lf %s.\n", bbs.comparisons, bbs.swaps, (bbs.execution_time < 0.1 ? bbs.execution_time * 1000 : bbs.execution_time), (bbs.execution_time < 0.1 ? "ms" : "s"));
                printf("\n");
                break;
            }
            default:
                // já tem verificação acima.
        }

        free(v);
    }

    return;
}


int main()
{
    srand(time(NULL)); // iniciando o gerador de números aleatórios

    // 1 = bubble sort
    relatorio(1);

    return 0;
}
