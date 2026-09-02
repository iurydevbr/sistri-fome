#include <stdio.h>   // Biblioteca padrão para entrada e saída (printf, scanf, fgets)
#include <stdlib.h>  // Biblioteca padrão para funções utilitárias e controle de arquivos
#include <string.h>  // Biblioteca para manipulação de strings (strcmp, strcpy, strcspn)

// Definição de uma constante para o tamanho máximo do vetor.
// Facilita a manutenção do código: se precisar mudar para 500, muda apenas aqui.
#define MAX_CIDADAOS 100

/* STRUCT (ESTRUTURA)
  Por que usar struct em vez de matriz de ponteiros?
  A struct agrupa variáveis de tipos diferentes (ou strings diferentes) sob um mesmo nome,
  representando perfeitamente um "objeto" ou "registro" do mundo real (um Cidadão).
*/
typedef struct {
    char nome[50];
    char cpf[15];
    char cidade[50];
    char bairro[50];
    char triagem[100]; // Guarda o resultado gerado automaticamente pela árvore de decisão
} Cidadao;

// Banco de dados em memória: um vetor de estruturas (matriz/vetor de registros)
Cidadao cadastros[MAX_CIDADAOS];

// Variável global que funciona como o índice atual e contador de cadastros ativos no sistema
int posicaoI = 0;

// Protótipos das funções: Avisa ao compilador que essas funções existem e serão detalhadas abaixo.
// Isso permite organizar o código de forma modularizada.
void menu();
void cadastrarUsuario();
void realizarTriagem();
void pesquisarBeneficiario();
void salvarDados();
void carregarDados();

int main() {
    int opcao = 0;

    // REQUISITO: Leitura do arquivo ao iniciar o programa para persistência de dados
    carregarDados();

    /*
      ESTRUTURA DE REPETIÇÃO: do/while
      Garante que o menu principal seja executado pelo menos uma vez e se repita
      enquanto o usuário não digitar '0' (Sair).
    */
    do {
        menu(); // Chama a função modularizada que desenha o menu
        printf("Escolha uma opcao: ");

        // Validação de entrada: Se o usuário digitar uma letra, o scanf falha (não retorna 1).
        if (scanf("%d", &opcao) != 1) {
            // Limpa o buffer de entrada para evitar um loop infinito de erro
            while (getchar() != '\n');
            opcao = -1; // Força a cair no bloco 'default'
        }
        getchar(); // Consome o caractere de nova linha '\n' deixado pelo scanf/teclado

        /*
          ESTRUTURA DE DECISÃO: switch/case
          Ideal para menus, pois avalia diretamente o valor de uma variável inteira
          e direciona o fluxo para a função correspondente.
        */
        switch (opcao) {
            case 1:
                cadastrarUsuario(); // Invoca o módulo de cadastro
                break; // O break impede que o código continue executando os cases de baixo.
            case 2:
                realizarTriagem();  // Invoca o módulo de cálculo socioeconômico.
                break;
            case 3:
                pesquisarBeneficiario(); // Invoca o módulo de busca por campo.
                break;
            case 0:
                printf("\nSaindo do sistema e salvando dados... Obrigado!\n");
                salvarDados(); // Grava tudo no arquivo texto antes de fechar.
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

// Função simples para modularizar e limpar a função main
void menu() {
    printf("\n=============================================\n");
    printf("========== SISTRI - MENU DO SISTEMA =========\n");
    printf("=============================================\n");
    printf("[1] Cadastrar Usuario\n");
    printf("[2] Realizar Triagem\n");
    printf("[3] Pesquisar Beneficiario\n");
    printf("[0] Sair\n");
    printf("=============================================\n");
}

void cadastrarUsuario() {
    // Tratamento de erro: Verifica se o vetor atingiu o limite máximo de armazenamento
    if (posicaoI >= MAX_CIDADAOS) {
        printf("\nErro: Limite maximo de cadastros atingido!\n");
        return; // Encerra a função mais cedo
    }

    printf("\n--- CADASTRO DE CIDADAO ---\n");

    /*
      Motivo de usar fgets() em vez de scanf("%s"):
      O scanf("%s") encerra a leitura no primeiro espaço em branco (ex: se digitar "João Silva", ele lê só "João").
      O fgets() lê a linha inteira, incluindo os espaços.
      stdin significa que a leitura está vindo da entrada padrão (teclado).
    */
    printf("Digite o Nome do Cidadao: ");
    fgets(cadastros[posicaoI].nome, 50, stdin);
    // REMOÇÃO DO '\n': O fgets armazena a tecla 'Enter' (\n) no final da string.
    // strcspn localiza onde está esse '\n' e o substitui por '\0' (fim da string) para não quebrar o layout.
    cadastros[posicaoI].nome[strcspn(cadastros[posicaoI].nome, "\n")] = '\0';

    printf("Digite o CPF (apenas numeros): ");
    fgets(cadastros[posicaoI].cpf, 15, stdin);
    cadastros[posicaoI].cpf[strcspn(cadastros[posicaoI].cpf, "\n")] = '\0';

    printf("Digite a Cidade: ");
    fgets(cadastros[posicaoI].cidade, 50, stdin);
    cadastros[posicaoI].cidade[strcspn(cadastros[posicaoI].cidade, "\n")] = '\0';

    printf("Digite o Bairro: ");
    fgets(cadastros[posicaoI].bairro, 50, stdin);
    cadastros[posicaoI].bairro[strcspn(cadastros[posicaoI].bairro, "\n")] = '\0';

    // Inicializa o status de triagem padrão antes do questionário ser respondido
    strcpy(cadastros[posicaoI].triagem, "Nao realizada");

    printf("\nUsuario %s cadastrado com sucesso na posicao %d!\n", cadastros[posicaoI].nome, posicaoI + 1);

    // Incrementa o índice global para que o próximo cidadão seja salvo na posição seguinte do vetor
    posicaoI++;

    // Gravação preventiva no arquivo para evitar perda de dados se o programa fechar incorretamente.
    salvarDados();
}

void realizarTriagem() {
    char cpfBusca[15];
    int encontrado = -1;
    int r1, r2, r3, r4, r5, pontuacao = 0;

    printf("\n--- TRIAGEM SOCIOECONOMICA ---\n");
    printf("Digite o CPF do beneficiario para triagem: ");
    fgets(cpfBusca, 15, stdin);
    cpfBusca[strcspn(cpfBusca, "\n")] = '\0';

    /*
      ESTRUTURA DE REPETIÇÃO + PESQUISA (Busca Linear)
      Varre o vetor desde a posição 0 até o limite de cidadãos cadastrados ('posicaoI')
      procurando uma correspondência com o CPF digitado.
    */
    for (int i = 0; i < posicaoI; i++) {
        // strcmp() retorna 0 se as duas strings forem exatamente iguais
        if (strcmp(cadastros[i].cpf, cpfBusca) == 0) {
            encontrado = i; // Armazena o índice onde o cidadão foi localizado
            break; // Para o laço for, economizando processamento.
        }
    }

    if (encontrado == -1) {
        printf("\nCidadao nao localizado no sistema. Cadastre-o primeiro.\n");
        return;
    }

    printf("\nIniciando questionario para: %s\n", cadastros[encontrado].nome);
    printf("Localidade: %s - %s\n\n", cadastros[encontrado].bairro, cadastros[encontrado].cidade);

    // QUESTIONÁRIO DE TRIAGEM COM PESOS LÓGICOS
    printf("1. O cidadao realiza alguma refeicao regular diariamente? [1] Sim | [2] Nao: ");
    scanf("%d", &r1);
    if (r1 == 2) pontuacao += 5; // Respostas negativas geram maior pontuação (vulnerabilidade)

    printf("2. Qual a condicao de moradia atual? [1] Possui casa | [2] Abrigo/Rua: ");
    scanf("%d", &r2);
    if (r2 == 2) pontuacao += 5;

    printf("3. Qual a principal fonte de renda familiar? [1] Emprego/Aposentadoria | [2] Bicos/Sem Renda: ");
    scanf("%d", &r3);
    if (r3 == 2) pontuacao += 4;

    printf("4. Ha criancas ou idosos dependentes na residencia? [1] Nao | [2] Sim: ");
    scanf("%d", &r4);
    if (r4 == 2) pontuacao += 3;

    printf("5. Nos ultimos meses, faltou alimento por motivos financeiros? [1] Nao | [2] Sim: ");
    scanf("%d", &r5);
    if (r5 == 2) pontuacao += 3;

    /*
      ÁRVORE DE DECISÃO LOGICA (if / else if / else)
      Analisa a pontuação acumulada para definir o encaminhamento automático do cidadão.
      Cumpre a proposta de inovação de retirar a subjetividade da triagem manual.
    */
    if (pontuacao >= 14) {
        strcpy(cadastros[encontrado].triagem, "Inseguranca Extrema - Encaminhar p/ Cozinha Comunitaria e Abrigo Urgente");
    } else if (pontuacao >= 7) {
        strcpy(cadastros[encontrado].triagem, "Inseguranca Moderada - Encaminhar p/ Entrega de Cestas Basicas");
    } else {
        strcpy(cadastros[encontrado].triagem, "Inseguranca Leve - Inclusao em Programas Sociais de Renda");
    }

    printf("\nTriagem concluida! Resultado: %s\n", cadastros[encontrado].triagem);

    salvarDados(); // Atualiza o arquivo com a nova triagem realizada.
}

void pesquisarBeneficiario() {
    char cpfBusca[15];
    int encontrado = 0;

    printf("\n--- PESQUISAR BENEFICIARIO ---\n");
    printf("Digite o CPF para busca: ");
    fgets(cpfBusca, 15, stdin);
    cpfBusca[strcspn(cpfBusca, "\n")] = '\0';

    // Laço para pesquisar os dados na memória (Vetor)
    for (int i = 0; i < posicaoI; i++) {
        if (strcmp(cadastros[i].cpf, cpfBusca) == 0) {
            printf("\n-----------------------------------\n");
            printf("Nome: %s\n", cadastros[i].nome);
            printf("CPF: %s\n", cadastros[i].cpf);
            printf("Cidade: %s\n", cadastros[i].cidade);
            printf("Bairro: %s\n", cadastros[i].bairro);
            printf("Situacao/Triagem: %s\n", cadastros[i].triagem);
            printf("-----------------------------------\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\nBeneficiario com o CPF %s nao foi encontrado.\n", cpfBusca);
    }
}

/*
  A função 'salvarDados' abre um arquivo chamado 'dados.txt' em modo de escrita.
  Esse modo cria o arquivo se ele não existir ou limpa o conteúdo antigo caso já exista.
*/
void salvarDados() {
    FILE *arquivo = fopen("dados.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar!\n");
        return;
    }

    // Grava o número total de registros salvos na primeira linha do arquivo texto.
    // Isso é vital para que a função de leitura saiba quantos loops precisará fazer depois.
    fprintf(arquivo, "%d\n", posicaoI);

    // Escreve cada campo da nossa struct linha por linha de forma estruturada e previsível
    for (int i = 0; i < posicaoI; i++) {
        fprintf(arquivo, "%s\n", cadastros[i].nome);
        fprintf(arquivo, "%s\n", cadastros[i].cpf);
        fprintf(arquivo, "%s\n", cadastros[i].cidade);
        fprintf(arquivo, "%s\n", cadastros[i].bairro);
        fprintf(arquivo, "%s\n", cadastros[i].triagem);
    }

    fclose(arquivo); // Fecha o arquivo para salvar as alterações fisicamente no disco
}

/*
  A função 'carregarDados' abre o arquivo em modo de leitura.
  Ela reconstrói o banco de dados na memória RAM assim que o programa inicia.
*/
void carregarDados() {
    FILE *arquivo = fopen("dados.txt", "r");
    if (arquivo == NULL) {
        // Se o arquivo não existir (como na primeira vez que o sistema roda),
        // a função encerra silenciosamente sem gerar falhas.
        return;
    }

    // Lê a primeira linha do arquivo para descobrir quantos cidadãos cadastrados existem
    if (fscanf(arquivo, "%d\n", &posicaoI) != 1) {
        posicaoI = 0;
    }

    // Realiza o laço exatamente 'posicaoI' vezes, puxando as informações de volta para o vetor
    for (int i = 0; i < posicaoI; i++) {
        fgets(cadastros[i].nome, 50, arquivo);
        cadastros[i].nome[strcspn(cadastros[i].nome, "\n")] = '\0'; // Limpa o \n trazido do arquivo

        fgets(cadastros[i].cpf, 15, arquivo);
        cadastros[i].cpf[strcspn(cadastros[i].cpf, "\n")] = '\0';

        fgets(cadastros[i].cidade, 50, arquivo);
        cadastros[i].cidade[strcspn(cadastros[i].cidade, "\n")] = '\0';

        fgets(cadastros[i].bairro, 50, arquivo);
        cadastros[i].bairro[strcspn(cadastros[i].bairro, "\n")] = '\0';

        fgets(cadastros[i].triagem, 100, arquivo);
        cadastros[i].triagem[strcspn(cadastros[i].triagem, "\n")] = '\0';
    }

    fclose(arquivo); // Fecha o fluxo de leitura
}
