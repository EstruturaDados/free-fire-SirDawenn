#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 20

// ===============================================================
// Estrutura principal: Item
// ===============================================================
typedef struct
{
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// ===============================================================
// Função auxiliar para retirar o '\n' inserido pelo fgets
// ===============================================================
void removerQuebraLinha(char *str)
{
    str[strcspn(str, "\n")] = '\0';
}

// ===============================================================
// Função: listarComponentes
// Mostra todos os itens cadastrados
// ===============================================================
void listarComponentes(Componente c[], int n)
{
    printf("\n================== COMPONENTES REGISTRADOS ==================\n");
    printf("%-25s %-20s %-10s\n", "Nome", "Categoria", "Prioridade");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        printf("%-25s %-20s %-10d\n", c[i].nome, c[i].tipo, c[i].prioridade);
    }
    printf("=============================================================\n");
}

// ===============================================================
// Bubble Sort - Ordenação por nome
// ===============================================================
void bubbleSortNome(Componente c[], int n, int *comparacoes)
{
    *comparacoes = 0;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            (*comparacoes)++;
            if (strcmp(c[j].nome, c[j + 1].nome) > 0)
            {
                Componente aux = c[j];
                c[j] = c[j + 1];
                c[j + 1] = aux;
            }
        }
    }
}

// ===============================================================
// Insertion Sort - Ordenação por tipo
// ===============================================================
void insertionSortTipo(Componente c[], int n, int *comparacoes)
{
    *comparacoes = 0;
    for (int i = 1; i < n; i++)
    {
        Componente atual = c[i];
        int j = i - 1;
        while (j >= 0 && strcmp(c[j].tipo, atual.tipo) > 0)
        {
            (*comparacoes)++;
            c[j + 1] = c[j];
            j--;
        }
        c[j + 1] = atual;
    }
}

// ===============================================================
// Selection Sort - Ordenação por prioridade
// ===============================================================
void selectionSortPrioridade(Componente c[], int n, int *comparacoes)
{
    *comparacoes = 0;
    for (int i = 0; i < n - 1; i++)
    {
        int menor = i;
        for (int j = i + 1; j < n; j++)
        {
            (*comparacoes)++;
            if (c[j].prioridade < c[menor].prioridade)
                menor = j;
        }
        if (menor != i)
        {
            Componente aux = c[i];
            c[i] = c[menor];
            c[menor] = aux;
        }
    }
}

// ===============================================================
// Busca Binária por nome
// ===============================================================
int buscaBinariaPorNome(Componente c[], int n, char chave[], int *comparacoes)
{
    int inicio = 0, fim = n - 1;
    *comparacoes = 0;

    while (inicio <= fim)
    {
        int meio = (inicio + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(c[meio].nome, chave);

        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

// ===============================================================
// Função: medirTempoExecucao
// Calcula o tempo gasto no algoritmo
// ===============================================================
void medirTempoExecucao(void (*algoritmo)(Componente[], int, int *), Componente c[], int n, int *comparacoes)
{
    clock_t ini, fim;
    ini = clock();
    algoritmo(c, n, comparacoes);
    fim = clock();

    double tempo = ((double)(fim - ini)) / CLOCKS_PER_SEC;
    printf("\nTempo registrado: %.6f segundos\n", tempo);
    printf("Total de comparações: %d\n", *comparacoes);
}

// ===============================================================
// Programa principal
// ===============================================================
int main()
{
    Componente componentes[MAX];
    int n = 0;
    int opcao, comparacoes;
    char chave[30];

    do
    {
        printf("\n===================== PAINEL DE CONTROLE =====================\n");
        printf("1. Registrar novo componente\n");
        printf("2. Exibir todos os componentes\n");
        printf("3. Ordenar por nome (Bubble Sort)\n");
        printf("4. Ordenar por tipo (Insertion Sort)\n");
        printf("5. Ordenar por prioridade (Selection Sort)\n");
        printf("6. Procurar componente por nome (Busca Binária)\n");
        printf("0. Encerrar programa\n");
        printf("==============================================================\n");
        printf("Selecione uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 1:
            if (n < MAX)
            {
                printf("Nome do item: ");
                fgets(componentes[n].nome, 30, stdin);
                removerQuebraLinha(componentes[n].nome);

                printf("Categoria do item: ");
                fgets(componentes[n].tipo, 20, stdin);
                removerQuebraLinha(componentes[n].tipo);

                printf("Nível de prioridade (1 a 10): ");
                scanf("%d", &componentes[n].prioridade);
                getchar();

                n++;
                printf("\nItem registrado com êxito!\n");
            }
            else
            {
                printf("\nLimite máximo atingido!\n");
            }
            break;

        case 2:
            if (n > 0)
                listarComponentes(componentes, n);
            else
                printf("\nNenhum item registrado até agora!\n");
            break;

        case 3:
            if (n > 0)
            {
                medirTempoExecucao(bubbleSortNome, componentes, n, &comparacoes);
                printf("\nOrdenação concluída por NOME.\n");
                listarComponentes(componentes, n);
            }
            else
                printf("\nCadastre algo antes de ordenar!\n");
            break;

        case 4:
            if (n > 0)
            {
                medirTempoExecucao(insertionSortTipo, componentes, n, &comparacoes);
                printf("\nOrdenação concluída por TIPO.\n");
                listarComponentes(componentes, n);
            }
            else
                printf("\nCadastre algo antes de ordenar!\n");
            break;

        case 5:
            if (n > 0)
            {
                medirTempoExecucao(selectionSortPrioridade, componentes, n, &comparacoes);
                printf("\nOrdenação concluída por PRIORIDADE.\n");
                listarComponentes(componentes, n);
            }
            else
                printf("\nCadastre algo antes de ordenar!\n");
            break;

        case 6:
            if (n > 0)
            {
                printf("\nNome a ser localizado: ");
                fgets(chave, 30, stdin);
                removerQuebraLinha(chave);

                int pos = buscaBinariaPorNome(componentes, n, chave, &comparacoes);

                if (pos != -1)
                {
                    printf("\nItem encontrado!\n");
                    printf("Nome: %s | Tipo: %s | Prioridade: %d\n",
                           componentes[pos].nome,
                           componentes[pos].tipo,
                           componentes[pos].prioridade);
                }
                else
                {
                    printf("\nNenhum registro encontrado!\n");
                }

                printf("Comparações: %d\n", comparacoes);
            }
            else
            {
                printf("\nCadastre e ordene por nome antes de pesquisar!\n");
            }
            break;

        case 0:
            printf("\nEncerrando... Sistema finalizado.\n");
            break;

        default:
            printf("\nOpção inválida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
