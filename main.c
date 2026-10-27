#include <windows.h>    // Sleep()
#include <limits.h>     // INT_MAX, SHRT_MAX
#include <stdlib.h>     // malloc(), realloc(), free(), exit()
#include <stdio.h>      // printf(), fprintf(), fopen(), fclose()
#include <math.h>       // sqrt()
#include <time.h>       // clock()

// Variáveis globais:
// contador = controla atualização da porcentagem na tela
// ordem = numeração dos primos encontrados
// indice = quantidade de primos armazenados em memória
// numPrimos = vetor contendo os primos usados para testes de divisibilidade
int contador = 0, ordem = 0, indice = 0, *numPrimos;

// Arquivo onde os números primos serão gravados
FILE *file;

void mostrarTempo(clock_t inicio)
{
    // Converte o tempo decorrido para segundos
    long tempo = (clock() - inicio) / CLOCKS_PER_SEC;

    // Extrai horas, minutos e segundos
    long horas = tempo / 3600;
    long minutos = (tempo % 3600) / 60;
    long segundos = tempo % 60;

    // Força exibição de 100% ao final do processamento
    printf("\r%.2f%%", 100.0);
    fflush(stdout);

    // Exibe o tempo total de execução
    printf("\nTempo de execucao: %ldh %ldmin %lds\n",
           horas, minutos, segundos);

    // Mantém a janela aberta por 1 minuto
    Sleep(60000);
}

void iniciarListaPrimos()
{
    // Produz a sequência:
    // 2 -> 3 -> 5 -> 7
    for (int i = 2; i <= 7; i += 17 % i)
    {
        fprintf(file, "%d. %d\n", ++ordem, i);

        // Armazena apenas 5 e 7 no vetor.
        // 2 e 3 não são necessários porque
        // depois só serão testados números da forma 6k±1.
        if (i >= 5)
            numPrimos[indice++] = i;
    }
}

int definirLimite(int num, int acrescimo)
{
    // Ajusta o número até que ele seja congruente a 5 (mod 6),
    // ou seja, da forma 6k+5 (equivalente a 6k−1).
    while (num % 6 < 5)
        num += acrescimo;

    return num;
}

int ehPrimo(int num)
{
    // Basta testar divisores até a raiz quadrada
    int raiz = sqrt(num);

    // Percorre todos os primos previamente armazenados
    for (int i = 0; numPrimos[i] <= raiz; i++)
    {
        // Encontrou divisor => não é primo
        if (num % numPrimos[i] == 0)
            return 0;
    }

    // Nenhum divisor encontrado => é primo
    return 1;
}

void escreverPrimeirosPrimos(int num)
{
    if (ehPrimo(num))
    {
        // Aumenta o vetor de primos em duas posições
        size_t tam = sizeof(int) * (indice + 2);
        int *teste = realloc(numPrimos, tam);

        // Falha na realocação
        if (teste == NULL)
        {
            free(numPrimos);
            fclose(file);

            printf("\nErro ao alocar memória!\n");
            exit(3);
        }

        // Atualiza o ponteiro principal
        numPrimos = teste;

        // Salva o novo primo encontrado
        numPrimos[indice++] = num;

        // Escreve no arquivo
        fprintf(file, "%d. %d\n", ++ordem, num);
    }
}

void escreverDemaisPrimos(int num)
{
    if (ehPrimo(num))
    {
        // Escreve o primo encontrado
        fprintf(file, "%d. %d\n", ++ordem, num);

        // Atualiza o progresso somente
        // a cada SHRT_MAX primos encontrados
        if (contador++ == SHRT_MAX)
        {
            // Exibe percentual aproximado baseado
            // na posição atual dentro do intervalo até INT_MAX
            printf("\r%.2f%%", 100.0 * num / INT_MAX);
            fflush(stdout);

            contador = 0;
        }

    }
}

void comecarEscritaPrincipal()
{
    // Último número da forma 6k+5 antes da raiz de INT_MAX
    int limite1 = definirLimite(sqrt(INT_MAX) + 1, 1);

    // Último número da forma 6k+5 antes de INT_MAX
    int limite2 = definirLimite(INT_MAX, -1);

    // Primeira etapa:
    // encontra e armazena todos os primos até √INT_MAX
    for (int i = 11; i < limite1; i += 6)
    {
        escreverPrimeirosPrimos(i);
        escreverPrimeirosPrimos(i + 2);
    }

    // Adiciona um sentinela ao vetor.
    // Ele impede leituras indevidas em ehPrimo(),
    // pois será maior que qualquer raiz utilizada.
    numPrimos[indice] = limite1;

    // Segunda etapa:
    // percorre todos os candidatos 6k−1 e 6k+1
    // acima da raiz quadrada.
    for (int i = limite1; i < limite2; i += 6)
    {
        escreverDemaisPrimos(i);
        escreverDemaisPrimos(i + 2);
    }

    // Testa o último candidato do tipo 6k−1
    escreverDemaisPrimos(limite2);

    // Testa o último candidato do tipo 6k+1
    if (limite2 <= INT_MAX - 2)
        escreverDemaisPrimos(limite2 + 2);
}

int main()
{
    // Marca o início da execução
    clock_t inicio = clock();

    // Cria o arquivo de saída
    file = fopen("numeros_primos.txt", "w");

    // Reserva espaço inicial para dois primos
    numPrimos = malloc(sizeof(int) * 2);

    if (file && numPrimos)
    {
        // Escreve os primeiros primos conhecidos
        iniciarListaPrimos();

        // Inicia a geração principal
        comecarEscritaPrincipal();
    }
    else if(file == NULL && numPrimos == NULL)
    {
        printf("\nErro ao abrir o arquivo e ao alocar memória!\n");

        return 1;
    }
    else if(file == NULL)
    {
        printf("\nErro ao abrir o arquivo!\n");
        free(numPrimos);

        return 2;
    }
    else
    {
        printf("\nErro ao alocar memória!\n");
        fclose(file);

        return 3;
    }

    // Libera memória utilizada
    free(numPrimos);

    // Fecha o arquivo
    fclose(file);

    // Exibe tempo total de execução
    mostrarTempo(inicio);

    return 0;
}
