#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Cad_fornecedor.h"
#include "../Utilitarios/mascara.h"

// Função para adicionar o fornecedor no arquivo TXT
void adicionarFornecedorEmArquivo(fornecedor_t fornecedor) {
    FILE *arquivo = fopen("Fornecedores/fornecedor.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar os dados.\n");
        return;
    }

    fprintf(arquivo, "ID: %d\n", fornecedor.id);
    fprintf(arquivo, "Nome: %s\n", fornecedor.nome);
    fprintf(arquivo, "Endereco: %s\n", fornecedor.endereco);
    fprintf(arquivo, "Cidade: %s\n", fornecedor.cidade);
    fprintf(arquivo, "CEP: %s\n", fornecedor.cep);
    fprintf(arquivo, "Data: %s\n", fornecedor.dat);
    fprintf(arquivo, "CNPJ: %s\n", fornecedor.cnpj);
    fprintf(arquivo, "--------------------\n");

    fclose(arquivo);
}

// Função para sobrescrever os dados dos fornecedores no arquivo TXT
void sobrescreverFornecedoresEmArquivo(fornecedor_t fornecedor[], int numFornecedores) {
    FILE *arquivo = fopen("Fornecedores/fornecedor.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para sobrescrever os dados.\n");
        return;
    }

    for (int i = 0; i < numFornecedores; i++) {
        fprintf(arquivo, "ID: %d\n", fornecedor[i].id);
        fprintf(arquivo, "Nome: %s\n", fornecedor[i].nome);
        fprintf(arquivo, "Endereco: %s\n", fornecedor[i].endereco);
        fprintf(arquivo, "Cidade: %s\n", fornecedor[i].cidade);
        fprintf(arquivo, "CEP: %s\n", fornecedor[i].cep);
        fprintf(arquivo, "Data: %s\n", fornecedor[i].dat);
        fprintf(arquivo, "CNPJ: %s\n", fornecedor[i].cnpj);
        fprintf(arquivo, "--------------------\n");
    }

    fclose(arquivo);
}

// Função para carregar os dados dos fornecedores do arquivo TXT
int carregarFornecedoresDeArquivo(fornecedor_t fornecedor[]) {
    FILE *arquivo = fopen("Fornecedores/fornecedor.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhum arquivo de fornecedores encontrado. Iniciando sem Fornecedores.\n");
        return 0;
    }

    int numFornecedores = 0;
    char buffer[200];

    while (fgets(buffer, sizeof(buffer), arquivo)) {
        if (sscanf(buffer, "ID: %d", &fornecedor[numFornecedores].id) == 1) {
            fgets(buffer, sizeof(buffer), arquivo);
            sscanf(buffer, "Nome: %[^\n]", fornecedor[numFornecedores].nome);
            fgets(buffer, sizeof(buffer), arquivo);
            sscanf(buffer, "Endereco: %[^\n]", fornecedor[numFornecedores].endereco);
            fgets(buffer, sizeof(buffer), arquivo);
            sscanf(buffer, "Cidade: %[^\n]", fornecedor[numFornecedores].cidade);
            fgets(buffer, sizeof(buffer), arquivo);
            sscanf(buffer, "CEP: %s", &fornecedor[numFornecedores].cep);
            fgets(buffer, sizeof(buffer), arquivo);
            sscanf(buffer, "Data: %[^\n]", fornecedor[numFornecedores].dat);
            fgets(buffer, sizeof(buffer), arquivo);
            sscanf(buffer, "CNPJ: %s", &fornecedor[numFornecedores].cnpj);
            fgets(buffer, sizeof(buffer), arquivo);
            numFornecedores++;
        }
    }

    fclose(arquivo);
    printf("Fornecedores carregados com sucesso. Total de fornecedores: %d\n", numFornecedores);
    return numFornecedores;
}

// Função para adicionar fornecedores 
void adicionarFornecedor(fornecedor_t fornecedor[], int *numFornecedores) {
    fornecedor[*numFornecedores].id = *numFornecedores + 1; // Atribui o ID ao fornecedor

    printf("\nDigite o nome do fornecedor: ");
    fgets(fornecedor[*numFornecedores].nome, sizeof(fornecedor[*numFornecedores].nome), stdin);
    strtok(fornecedor[*numFornecedores].nome, "\n");

    printf("\nDigite o endereco do fornecedor: ");
    fgets(fornecedor[*numFornecedores].endereco, sizeof(fornecedor[*numFornecedores].endereco), stdin);
    strtok(fornecedor[*numFornecedores].endereco, "\n");

    printf("\nDigite a cidade do fornecedor: ");
    fgets(fornecedor[*numFornecedores].cidade, sizeof(fornecedor[*numFornecedores].cidade), stdin);
    strtok(fornecedor[*numFornecedores].cidade, "\n");

    printf("\nDigite o CEP do fornecedor: ");
    mascara_cep(fornecedor[*numFornecedores].cep);

    printf("\nDigite a data (dd/mm/aaaa): ");
    mascara_dat(fornecedor[*numFornecedores].dat);

    printf("\nDigite o CNPJ do fornecedor: ");
    fgets(fornecedor[*numFornecedores].cnpj, sizeof(fornecedor[*numFornecedores].cnpj), stdin);
    strtok(fornecedor[*numFornecedores].cnpj, "\n");

    printf("\nFornecedor cadastrado com sucesso!\n");
    adicionarFornecedorEmArquivo(fornecedor[*numFornecedores]);
    (*numFornecedores)++;
}

// Função para visualizar os fornecedores e seus dados salvos no arquivo TXT
void visualizarFornecedores(fornecedor_t fornecedor[], int numFornecedores) {
    if (numFornecedores == 0) {
        printf("Nenhum fornecedor cadastrado.\n");
        return;
    }

    printf("+------------------ :: DADOS DOS FORNCEDORES :: -------------------+\n");
    printf("|------------------------------------------------------------------|\n");
    printf("| ID | Nome                                | Cidade                |\n");
    printf("+------------------------------------------------------------------+\n");
    for (int i = 0; i < numFornecedores; i++) {
        printf("| %-2d | %-35s | %-20s  |\n", fornecedor[i].id, fornecedor[i].nome, fornecedor[i].cidade);
    
    }
    printf("+------------------------------------------------------------------+\n");

    system("pause");
    system("cls");
}

// Função para pesquisar fornecedor no arquivo TXT usando seu ID como base 
void pesquisarFornecedor(fornecedor_t fornecedor[], int numFornecedores) {
    int id;
    printf("Digite o ID para pesquisar: ");
    scanf("%d", &id);
    getchar();

    int encontrado = 0;
    for (int i = 0; i < numFornecedores; i++) {
        if (fornecedor[i].id == id) {

          printf("\n+------ Dados do Cliente ------------------------+\n");
            printf("|------------------------------------------------|\n");
            printf("| ID:                 | %-24d |\n", fornecedor[i].id);
            printf("| Nome:               | %-24s |\n", fornecedor[i].nome);
            printf("| Endereco:           | %-24s |\n", fornecedor[i].endereco);
            printf("| Cidade:             | %-24s |\n", fornecedor[i].cidade);
            printf("| CEP:                | %-24s |\n", fornecedor[i].cep);
            printf("| Data:               | %-24s |\n", fornecedor[i].dat);
            printf("| CNPJ:               | %-24s |\n", fornecedor[i].cnpj);
            printf("+------------------------------------------------+\n");
            encontrado = 1;

            char opcao;
            printf("\nDeseja editar os dados do Fornecedor? (s/n): ");
            scanf("%c", &opcao);
            getchar();
            system("cls");

            if (opcao == 's' || opcao == 'S') {
                int editOp;
                do {
                    printf("\nQual dado deseja editar?\n");
                    printf("1 - Nome\n");
                    printf("2 - Endereco\n");
                    printf("3 - Cidade\n");
                    printf("4 - CEP\n");
                    printf("5 - Data\n");
                    printf("6 - CNPJ\n");
                    printf("7 - Sair\n");
                    printf("Opcao: ");
                    scanf("%d", &editOp);
                    getchar();

                    switch (editOp) {
                    case 1:
                        printf("Digite o novo nome (Nome atual: %s ): ", fornecedor[i].nome);
                        fgets(fornecedor[i].nome, sizeof(fornecedor[i].nome), stdin);
                        strtok(fornecedor[i].nome, "\n");
                        printf("Nome alterado com sucesso!\n");

                        break;

                    case 2:
                        printf("Digite o novo endereco (Endereco atual: %s ): ", fornecedor[i].endereco);
                        fgets(fornecedor[i].endereco, sizeof(fornecedor[i].endereco), stdin);
                        strtok(fornecedor[i].endereco, "\n");
                        printf("Endereco alterado com sucesso!\n");
                        break;

                    case 3:
                        printf("Digite a nova cidade (Cidade atual: %s ): ", fornecedor[i].cidade);
                        fgets(fornecedor[i].cidade, sizeof(fornecedor[i].cidade), stdin);
                        strtok(fornecedor[i].cidade, "\n");
                        printf("Cidade alterada com sucesso!\n");

                        break;

                    case 4:
                        printf("Digite o novo CEP (CEP atual: %s ): ", fornecedor[i].cep);
                        mascara_cep(fornecedor[i].cep);
                        strtok(fornecedor[i].cep, "\n");
                        printf("CEP alterado com sucesso!\n");
                        break;

                    case 5:
                        printf("Digite a nova data (dd/mm/aaaa) (Data atual: %s ): ", fornecedor[i].dat);
                        mascara_dat(fornecedor[i].dat);
                        strtok(fornecedor[i].dat, "\n");
                        printf("Data alterada com sucesso!\n");

                        break;

                    case 6:
                        printf("Digite o novo CNPJ (CNPJ atual: %s ): ", fornecedor[i].cnpj);
                        scanf("%s", fornecedor[i].cnpj);
                        getchar();
                        printf("CNPJ alterado com sucesso!\n");
                        break;


                    case 7:
                        printf("Saindo da edicao...\n");
                        break;

                    default:
                        printf("Opcao invalida.\n");
                        break;
                    }

                    printf("\n");
                    system("pause");
                    system("cls");
                    
                    sobrescreverFornecedoresEmArquivo(fornecedor, numFornecedores);

                } while (editOp != 7);
            }
            break;
        }
    }

    if (!encontrado) {
        printf("Fornecedor com ID %d nao encontrado.\n", id);
    }
}

// Função para remover fornecedor do arquivo TXT
void removerFornecedor(fornecedor_t fornecedor[], int *numFornecedores) {
    int id;
    printf("Digite o ID para remover: ");
    scanf("%d", &id);
    getchar();

    int encontrado = 0;
    for (int i = 0; i < *numFornecedores; i++) {
        if (fornecedor[i].id == id) {
            for (int j = i; j < *numFornecedores - 1; j++) {
                fornecedor[j] = fornecedor[j + 1];
            }
            (*numFornecedores)--;
            printf("Fornecedor removido com sucesso!\n");

            sobrescreverFornecedoresEmArquivo(fornecedor, *numFornecedores);

            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Fornecedor com ID %d nao encontrado.\n", id);
    }
}

