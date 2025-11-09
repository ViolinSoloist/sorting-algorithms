//importando bibliotecas
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define MIN_RAND 1

#define QNTD_TESTES 4

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
 * Heap Sort (feito)
 * Merge Sort
 * Contagem dos Menores
 * Radix Sort
*/


// ------------------------------------------
//            FUNÇÕES AUXILIARES
// ------------------------------------------
/**
 * @attention tem que ter a mesma quantidade de free()'s que tem essa função chamada na main
 * @details como devemos testar cada método de ordenação com diferentes quantidades de vetores com diferentes tamanhos,
 * é inteligente fazer uma função que trate a geração desses vetores
 * recebe o tamanho do vetor @param n numero de elementos
 * @return ponteiro pra array de inteiros alocados dinamicamente.
 */
int* make_rand_vector(int n)
{
    int* v = (int*)calloc(n, sizeof(int)); // v inicia com 0 em todos index, eu acho
    //  acho que a gente não precisa fazer uma função pros vetores
    //  a gente pdoe criar eles com malloc, no caso os 4 vetores de 100 1000 e tal e resetar o valor deles pra cada sort
    // sim sim, a função seria só pra deixar mais claro, mas seria só pra gerar esses 4 vetores, em vez de deixar na main

    if (v != NULL) {
        // TODO <stdlib.h> rand() preencher com números aleatórios
        srand(time(NULL)); //seed

        int maximo = (int)(n * 1.2);

        for(int i=0; i<n; i++) {
            int rand_num = (rand() % maximo) + MIN_RAND;
            v[i] = rand_num;
        }
    }
    return v;
}

/**
* @attention se chamar, lembrar de dar free no vetor
*/
int* make_ordered_vector(int n)
{
    int* v = (int*)calloc(n, sizeof(int));

    if (v != NULL)
    {
        for(int i=0; i<n; i++) {
            v[i] = i+1;
        }
    }
    return v;
}

/**
* @attention mesma coisa, dar free() se chamar
*/
int* make_reversed_sorted_vector(int n)
{
    int* v = (int*)calloc(n, sizeof(int));

    if (v != NULL)
    {
        int j=1;
        for(int i=n-1; i>=0; i--) {
            v[i] = j;
            j++;
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

int medianadeTres(int* v, int min, int lim) // quick sort
{
    int n1 = (rand() % (lim-min))+min;
    int n2 = (rand() % (lim-min))+min;
    int n3 = (rand() % (lim-min))+min;

    if((v[n1] <= v[n2] && v[n2] <= v[n3]) || (v[n3] <= v[n2] && v[n2] <= v[n1])){
        return n2;
    }
    else if((v[n2] <= v[n1] && v[n1] <= v[n3]) || (v[n3] <= v[n1] && v[n1] <= v[n2])){
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
        for(int j=0; j<n-1-i; j++)
        {
            comparisons++; // if que verifica se o registro atual é maior que o próximo registro
            if(v[j] > v[j+1]) {
                swaps++; // sempre que tem swap incrimenta
                swap(v, j, j+1);
            }
        }
        if (!swaps) break; //se nenhum movimento é feito quer dizer que já está ordenado
    }

    clock_t fim = clock(); // fim da marcação de tempo
    double tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC;

    Info bbs_info = {v, comparisons, swaps, tempo_gasto};
    return bbs_info;
}


/**
* @deprecated
*/
void quick_sort2(int* v, int inf, int sup, ui* comparisons, ui* swaps){  //quick sort dps da primeira chamada
    /* adicionei os parâmetros comparisons e swaps apra contar nas chamadas recursivas, e são ponteiros pra mudar o valor da chamada inicial*/
    int indiceMediana = medianadeTres(v, inf, sup);
    int pivo = v[indiceMediana];

    int i = inf;
    int j = sup;
    do{
        while(v[i] < pivo){
            (*comparisons)++;
            i++;
        }
        while(v[j] > pivo){
           (*comparisons)++;
            j--;
        }
        if(i <=j){
            swap(v, i, j);
            (*swaps)++;
            i++;
            j--;
        }
        
    }while(i<j);
    if(j>inf){
        quick_sort2(v, inf, j, comparisons, swaps);
    }
    if(i<sup){
        quick_sort2(v, i, sup, comparisons, swaps);
    }
    // retornar struct Info ou definir a função para retornar void ou outra coisa
}

/**
* @details
* arrumei a mediana, agora manda o vetor e ela analisa os valores
* revisei a variavel aux e as de tempo que estavam incompletas ou erradas
* agora quicksort2 é void
* testei e ta funcionando
*/

Info quick_sort(int* v, int sup){  
    ui comparisons = 0;
    ui swaps = 0;
    clock_t inicio = clock(); //inicio da marcação de tempo

    //tirei a variavel aux, tinha colocado ela pq no codigo do manzato ele usa ela pra fazer o swap, aí esqueci de tirar

    int indiceMediana = medianadeTres(v,0, sup);
    int pivo = v[indiceMediana];

    int i = 0;
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
            comparisons++;
            swap(v, i, j);
            swaps++;
            i++;
            j--;
        }
    }while(i<j);
    if(j>0){
        quick_sort2(v, 0, j, &comparisons, &swaps);
    }
    if(i<sup){
        quick_sort2(v, i, sup, &comparisons, &swaps);
    }

    clock_t fim = clock(); // fim da marcação de tempo
    double tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC;
    Info qsort = {v, comparisons, swaps, tempo_gasto};
    return qsort;
}

// HEAP SORT


/**
* @brief reorganiza a heap a partir de um nó "i" e propaga até a raíz, no máximo
*/
Info balance_heap(int* v, int n, int i, Info info)
{
    Info hp_info = info;

    int left = 2*i + 1;
    int right = 2*i + 2;

    int maior = i;

    hp_info.comparisons++;
    if (left < n && v[left] > v[i]) maior = left;
    hp_info.comparisons++;
    if (right < n && v[right] > v[maior]) maior = right;

    if (maior != i) {
        hp_info.swaps++;
        swap(v, i, maior);
        hp_info = balance_heap(v, n, maior, hp_info);
    }
    return hp_info;
}

/**
* @brief transforma o vetor em uma heap
*/
Info make_heap(int *v, int n, Info hp_sort)
{
    Info info = hp_sort;
    int middle = n/2-1;
    for(int i=middle; i>=0; i--)
        info = balance_heap(v,n,i,info);

    return info;
}

Info heap_sort(int* v, int n)
{
    Info hp_sort = {v, 0, 0, 0.0};
    clock_t inicio = clock(); //inicio da marcação de tempo

    hp_sort = make_heap(v, n, hp_sort);
    while (--n)
    {
        hp_sort.swaps++;
        swap(v, 0, n);

        hp_sort = balance_heap(v, n, 0, hp_sort);
    }

    clock_t fim = clock(); // fim da marcação de tempo
    double tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC;

    hp_sort.execution_time = tempo_gasto;

    return hp_sort;
}



// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

// PROCEDIMENTO (FUNÇÃO QUE NÃO RETORNA NADA) QUE VAI FAZER UM MINI "RELATORIO"
// SORTAR PARA DIFERENTES N E MODOS

// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

void print_nome_do_sort(int id_sort)
{
    switch (id_sort)
    {
    case 1:
        printf("BUBBLE SORT\n\n");
        return;

    case 2:
        printf("HEAP SORT\n\n");
        return;
    
    case 3:
        printf("QUICK SORT\n\n");
        return;
    default:
        fprintf(stderr, "ID de sort inválido.\n");
        return;
    }
}

void mostrar_info(int* v, int n, int id_sort)
{
    Info sort_info;
    switch (id_sort)
    {
        case 1:
            sort_info = bubble_sort(v, n);
            break;

        case 2:
            sort_info = heap_sort(v, n);
            break;
        case 3:
            sort_info = quick_sort(v, n);
    }

    printf("Comparacoes: %u\nSwaps: %u\nTempo decorrido: %.3lf %s.\n",
        sort_info.comparisons, sort_info.swaps, (sort_info.execution_time < 0.1 ?
        sort_info.execution_time * 1000 :
        sort_info.execution_time), (sort_info.execution_time < 0.1 ? "milisegundos" : "segundos"));
    printf("\n");

    return;
}

void randomize_vector(int* v, int n)
{
    int maximo = n;

    for(int i=0; i<n; i++)
    {
        int rand_num = (rand() % maximo) + MIN_RAND;
        v[i] = rand_num;
    }

    return;
}

void do_5_calls_v_rand(int n, int id_sort)
{
    int* v = make_rand_vector(n);
    if (v == NULL) {
        fprintf(stderr, "Falha na alocação de memória para vetor de tamanho %d.\n", n);
        return;
    }

    printf("Testes para tamanho n = %d.\n\n", n);

    for (int j=0; j<5; j++)
    {
        // a primeira vez já tá aleatório, mas nas outras vezes precisa aleatorizar de novo
        // (poderia fazer free e malloc todas as vezes, mas melhor não)
        if (j!=0)
            randomize_vector(v, n);

        printf("Teste %d:\n", j+1);

        mostrar_info(v, n, id_sort);
        printf("\n");
    }
    printf("\n");

    free(v);
    return;
}

void relatorio(int id_sort) /** @param recebe id de qual sort vai ser analisado*/
{
    const int tamanhos_de_teste[QNTD_TESTES] = {100, 1000, 10000, 100000};

    printf("\033[2J\033[H"); // limpa a tela

    print_nome_do_sort(id_sort);

    printf("====================\n");
    printf("ELEMENTOS ALEATORIOS:\n");
    printf("====================\n\n");

    for (int i=0; i<QNTD_TESTES; i++) // ITERA POR TODOS OS TAMANHOS DE VETOR QUE PRECISAMOS TESTAR
    {
        int tam_v_atual = tamanhos_de_teste[i];
        // cinco chamadas por tamanho de vetor aleatorio

        if (tam_v_atual == 100000) {
            printf("ATENCAO: para cada sort aleatorio desse tamanho, demora um pouco mais de 20 seg.\n");
            printf("Vai demorar um pouco menos de 2 min para mostrar todos os 5 vetores ordenados.\n\n");
        }

        // condição temporária (pra poder testar n = 100000 com outros modos, mas não com esse se não vai demorar muito)
        // if (tam_v_atual != 100000)
            do_5_calls_v_rand(tam_v_atual, id_sort);

    }

    printf("===================\n");
    printf("ELEMENTOS ORDENADOS:\n");
    printf("===================\n\n");

    for(int i=0; i<QNTD_TESTES; i++)
    {
        int tam_v_atual = tamanhos_de_teste[i];

        // alocação dinamica para criar vetor em cada loop
        // (não faço um único porque pra cada loop, o tamanho muda)
        // e usar realloc é paia dms
        int* v_sorted = make_ordered_vector(tam_v_atual);
        if (v_sorted == NULL) {
            fprintf(stderr, "Falha na alocação de memória para vetor de tamanho %d.\n", tam_v_atual);
            return;
        }
        printf("Tamanho: %d\n", tam_v_atual);
        mostrar_info(v_sorted, tam_v_atual, id_sort);

        free(v_sorted);
    }

    printf("=================================\n");
    printf("ELEMENTOS INVERSAMENTE ORDENADOS:\n");
    printf("=================================\n\n");

    for (int i=0; i<QNTD_TESTES; i++)
    {
        int tam_v_atual = tamanhos_de_teste[i];

        int* vetor = make_reversed_sorted_vector(tam_v_atual);
        if (vetor == NULL) {
            fprintf(stderr, "Falha na alocação de memória para vetor de tamanho %d.\n", tam_v_atual);
            return;
        }
        printf("Tamanho: %d\n", tam_v_atual);
        mostrar_info(vetor, tam_v_atual, id_sort);


        free(vetor);
    }
    printf("\n\n");

    return;
}

void testar_sort(int id_sort)
{
    const int n = 30;
    int* v = make_rand_vector(n);

    for (int i=0; i<5; i++)
    {
        if (i!=0) randomize_vector(v, n);
        print_vetor(v, n);

        switch (id_sort)
        {
            case 1:
                bubble_sort(v, n);
                break;

            case 2:
                heap_sort(v, n);
                break;

            case 3:
                quick_sort(v, n);
                break;
        }

        print_vetor(v, n);

        printf("\n");
    }
    if (v!=NULL) free(v);
}

int main()
{
    srand(time(NULL)); // iniciando o gerador de números aleatórios

    /**
    * 1 = bubble sort
    * 2 = heap sort
    */
    //relatorio(1);
    //relatorio(2);
    relatorio(3);

    return 0;
}
