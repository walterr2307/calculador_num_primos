# Calculador de Números Primos

Programa escrito em C que encontra números primos positivos até `INT_MAX` e grava os resultados em `numeros_primos.txt`.

## Sobre o projeto

O programa percorre candidatos a números primos, testa sua divisibilidade por primos previamente encontrados e registra cada primo encontrado em um arquivo de texto. A saída contém a posição do primo na sequência e seu valor, em linhas no formato:

```text
1. 2
2. 3
3. 5
4. 7
...
```

## Como funciona

- **Candidatos `6k ± 1`:** depois dos casos iniciais, o programa testa números das formas `6k - 1` e `6k + 1`. Isso elimina candidatos divisíveis por 2 ou 3, embora nem todo número dessa forma seja primo.
- **Teste de divisibilidade:** para cada candidato, `ehPrimo()` verifica divisores primos armazenados até a raiz quadrada do candidato.
- **Vetor dinâmico:** os primos encontrados até aproximadamente `√INT_MAX` são armazenados em um vetor redimensionado com `realloc()`. Esses valores são usados como divisores na etapa seguinte.
- **Gravação em arquivo:** os primos encontrados são escritos sequencialmente em `numeros_primos.txt`.
- **Progresso:** o programa exibe uma porcentagem aproximada durante a segunda etapa e o tempo de execução ao final.

## Requisitos

- Windows, devido ao uso de `Sleep()` de `windows.h`.
- Compilador C com suporte às bibliotecas padrão utilizadas.
- `INT_MAX` define o limite superior de acordo com a implementação e a plataforma. Em ambientes comuns com `int` de 32 bits, esse limite é `2.147.483.647`.

## Como compilar

Com GCC instalado, abra o terminal na pasta do código e execute:

```bash
gcc main.c -o calculador_num_primos.exe -lm
```

A opção `-lm` é necessária em alguns ambientes para a biblioteca matemática. Se estiver usando o Code::Blocks, também é possível abrir o projeto pela configuração `.cbp` e compilá-lo por lá.

## Como executar

No Prompt de Comando do Windows:

```cmd
calculador_num_primos.exe
```

O arquivo `numeros_primos.txt` será criado no diretório de trabalho atual. Como o arquivo é aberto com o modo `"w"`, uma execução nova sobrescreve um arquivo de mesmo nome que já exista.

## Desempenho observado

Em uma execução neste computador, o processamento levou aproximadamente **10 minutos** e produziu um arquivo de texto com **pouco mais de 2 GB**.

Configuração informada da máquina:

- **Sistema operacional:** Windows 11 Pro, 64 bits
- **Computador:** Dell OptiPlex Micro Plus 7020
- **Processador:** Intel Core i7-14700T
- **Memória RAM instalada:** 16 GB

Esse resultado é uma medição observada nessa máquina, não uma garantia de desempenho em outros computadores. O tempo também pode variar conforme o compilador, as opções de otimização, o armazenamento e as condições de execução.

## Observações

- O arquivo gerado é muito grande; verifique se há espaço livre suficiente antes de executar o programa.
- Evite enviar `numeros_primos.txt` para o GitHub se ele ultrapassar os limites de tamanho aceitos. Em geral, arquivos de dados gerados podem ser excluídos do versionamento com `.gitignore`.
- O tempo exibido é calculado com `clock()`. Dependendo da implementação da biblioteca C, ele pode representar tempo de CPU, e não necessariamente o tempo real transcorrido.
- O programa usa um vetor dinâmico para os primos necessários aos testes, mas a saída completa é armazenada em disco.

## Estrutura

```text
calculador_num_primos/
├── main.c
├── numeros_primos.cbp
└── README.md
```

Os arquivos auxiliares de compilação e as pastas geradas pela IDE podem variar conforme o ambiente.

## Objetivo

Projeto de estudo em C para praticar laços, funções, alocação dinâmica de memória, testes de primalidade, operações com arquivos e medição de tempo de execução.
