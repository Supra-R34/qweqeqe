#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Cad_cliente.h"
#include "../Utilitarios/mascara.h"


//Função para verificar se um CPF ja existe para evitar duplicação de CPF
int verificarCpfExistente(cliente_t cliente[], int numClientes, const char *cpf) {
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(cliente[i].cpf, cpf) == 0) {
            return 1; 
        }
    }
    return 0; 
}

//Função para formatar o CPF com mascara e deixar mais apresentavel na tabela de dados
void formatar_cpf_com_mascara(const char *cpf, char *cpf_formatado) {
    snprintf(cpf_formatado, 15, "%.3s.%.3s.%.3s-%.2s", cpf, cpf + 3, cpf + 6, cpf + 9);
}


//Função para adicionar os cliente no arquivo TXT
void adicionarClienteEmArquivo(cliente_t cliente) {
    FILE *arquivo = fopen("Clientes/cliente.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar os dados.\n");
        return;
    }

    fprintf(arquivo, "Nome: %s\n", cliente.nome);
    fprintf(arquivo, "Endereco: %s\n", cliente.endereco);
    fprintf(arquivo, "Email: %s\n", cliente.email);
    fprintf(arquivo, "CPF: %s\n", cliente.cpf);
    fprintf(arquivo, "Telefone: %lld\n", cliente.tel);
    fprintf(arquivo, "Data: %s\n", cliente.dat);
    fprintf(arquivo, "--------------------\n");

    fclose(arquivo);
}

//Função para sobrescrevers os dados dos cliente no arquivo TXT
void sobrescreverClientesEmArquivo(cliente_t cliente[], int numClientes) {
    FILE *arquivo = fopen("Clientes/cliente.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para sobrescrever os dados.\n");
        return;
    }

    for (int i = 0; i < numClientes; i++) {
        fprintf(arquivo, "Nome: %s\n", cliente[i].nome);
        fprintf(arquivo, "Endereco: %s\n", cliente[i].endereco);
        fprintf(arquivo, "Email: %s\n", cliente[i].email);
        fprintf(arquivo, "CPF: %s\n", cliente[i].cpf);
        fprintf(arquivo, "Telefone: %lld\n", cliente[i].tel);
        fprintf(arquivo, "Data: %s\n", cliente[i].dat);
        fprintf(arquivo, "--------------------\n");
    }

    fclose(arquivo);
}

//Função para carregar os dados dos cliente no arquivo TXT
int carregarClientesDeArquivo(cliente_t cliente[]) {
    FILE *arquivo = fopen("Clientes/cliente.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhum arquivo de clientes encontrado. Iniciando sem Clientes.\n");
        return 0;
    }

    int numClientes = 0;
    char buffer[200];

    while (fgets(buffer, sizeof(buffer), arquivo)) {
        if (sscanf(buffer, "Nome: %[^\n]", cliente[numClientes].nome) == 1) {
            fgets(buffer, sizeof(buffer), arquivo);
            sscanf(buffer, "Endereco: %[^\n]", cliente[numClientes].endereco);
            fgets(buffer, sizeof(buffer), arquivo);
            sscanf(buffer, "Email: %[^\n]", cliente[numClientes].email);
            fgets(buffer, sizeof(buffer), arquivo);
            sscanf(buffer, "CPF: %s", &cliente[numClientes].cpf);
            fgets(buffer, sizeof(buffer), arquivo);
            sscanf(buffer, "Telefone: %lld", &cliente[numClientes].tel);
            fgets(buffer, sizeof(buffer), arquivo);
            sscanf(buffer, "Data: %[^\n]", cliente[numClientes].dat);
            fgets(buffer, sizeof(buffer), arquivo);
            numClientes++;
        }
    }

    fclose(arquivo);
    printf("Clientes carregados com sucesso. Total de clientes: %d\n", numClientes);
    return numClientes;
}

//Função para adicionar clientes 
void adicionarCliente(cliente_t cliente[], int *numClientes) {
    printf("\nDigite o nome do cliente: ");
    fgets(cliente[*numClientes].nome, sizeof(cliente[*numClientes].nome), stdin);
    strtok(cliente[*numClientes].nome, "\n");

    printf("\nDigite o endereco do cliente: ");
    fgets(cliente[*numClientes].endereco, sizeof(cliente[*numClientes].endereco), stdin);
    strtok(cliente[*numClientes].endereco, "\n");

    printf("\nDigite o email do cliente: ");
    fgets(cliente[*numClientes].email, sizeof(cliente[*numClientes].email), stdin);
    strtok(cliente[*numClientes].email, "\n");

    printf("\nDigite o CPF do cliente: ");
    ler_cpf_com_mascara(cliente[*numClientes].cpf); 

    
    if (verificarCpfExistente(cliente, *numClientes, cliente[*numClientes].cpf)) {
        printf("\n\nErro: O CPF %s ja esta cadastrado.\n", cliente[*numClientes].cpf);
        return;
    }


    printf("\n\nDigite o telefone do cliente: ");
    scanf("%lld", &cliente[*numClientes].tel);
    getchar();

    printf("\nDigite a data (dd/mm/aaaa): ");
    mascara_dat(cliente[*numClientes].dat);

    printf("\nCliente cadastrado com sucesso!\n");
    adicionarClienteEmArquivo(cliente[*numClientes]);
    (*numClientes)++;
}

//Função para vizualisar os clientes e seus dados salvos no arquivo TXT
void visualizarClientes(cliente_t cliente[], int numClientes) {
    if (numClientes == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    printf("+----------------------- :: DADOS DOS CLIENTES :: -------------------------------+\n");
    printf("|--------------------------------------------------------------------------------|\n");
    printf("| Nome                                                    | CPF                  |\n");
    printf("+--------------------------------------------------------------------------------+\n");
    
   for (int i = 0; i < numClientes; i++) {
        char cpf_com_mascara[15];
        
        
        aplicar_mascara_cpf(cliente[i].cpf, cpf_com_mascara);

        
        printf("| %-25s                               | %-20s |\n", cliente[i].nome, cpf_com_mascara);
    }
    printf("+--------------------------------------------------------------------------------+\n");

    system("pause");
    system("cls");
}

//Função para pesquisar cliente no arquivo TXT usando seu CPF como base 
void pesquisarCliente(cliente_t cliente[], int numClientes) {
    char CPF[15];
    printf("Digite o CPF para pesquisar: ");
    ler_cpf_com_mascara(CPF);
    getchar();

     
    if (!verificarCpfExistente(cliente, numClientes, CPF)) {
        printf("\n\nErro: Cliente com CPF %s nao encontrado.\n", CPF);
        return; 
    }


    
    int encontrado = 0;
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(cliente[i].cpf, CPF) == 0) {

            char cpf_formatado[15];
            formatar_cpf_com_mascara(cliente[i].cpf, cpf_formatado);

          printf("\n+------ Dados do Cliente --------------+\n");
            printf("|--------------------------------------|\n");
            printf("| Nome:     | %-24s |\n", cliente[i].nome);
            printf("| Endereco: | %-24s |\n", cliente[i].endereco);
            printf("| Email:    | %-24s |\n", cliente[i].email);
            printf("| CPF:      | %-24s |\n", cpf_formatado);
            printf("| Telefone: | %-24.lld |\n", cliente[i].tel);
            printf("| Data:     | %-24s |\n", cliente[i].dat);
            printf("+--------------------------------------+\n");
            encontrado = 1;

            char opcao;
            printf("\nDeseja editar os dados do Cliente? (s/n): ");
            scanf("%c", &opcao);
            getchar();
            system("cls");


            if (opcao == 's' || opcao == 'S') {
                int editOp;
                do {
                    printf("\nQual dado deseja editar?\n");
                    printf("1 - Nome\n");
                    printf("2 - Endereco\n");
                    printf("3 - Email\n");
                    printf("4 - CPF\n");
                    printf("5 - Telefone\n");
                    printf("6 - Data\n");
                    printf("7 - Sair\n");
                    printf("Opcao: ");
                    scanf("%d", &editOp);
                    getchar();

                   

                    switch (editOp) {
                    case 1:
                        printf("Digite o novo nome (Nome atual: %s ): ", cliente[i].nome);
                        fgets(cliente[i].nome, sizeof(cliente[i].nome), stdin);
                        strtok(cliente[i].nome, "\n");
                        printf("Nome alterado com sucesso!\n");
                        break;

                    case 2:
                        printf("Digite o novo endereco (Endereco atual: %s ): ", cliente[i].endereco);
                        fgets(cliente[i].endereco, sizeof(cliente[i].endereco), stdin);
                        strtok(cliente[i].endereco, "\n");
                        printf("Endereco alterado com sucesso!\n");
                        break;

                    case 3:
                        printf("Digite o novo Email (Email atual: %s ): ", cliente[i].email);
                        fgets(cliente[i].email, sizeof(cliente[i].email), stdin);
                        strtok(cliente[i].email, "\n");
                        printf("Email alterado com sucesso!\n");
                        break;

                   case 4:
                        printf("Digite o novo CPF (CPF atual: %s ): ", cliente[i].cpf);

                        char novoCpf[15];
                        ler_cpf_com_mascara(novoCpf); 

                        if (verificarCpfExistente(cliente, numClientes, novoCpf)) {
                            printf("\nErro: O CPF %s ja esta cadastrado.\n", novoCpf);
                            break;  
                        }

                        strcpy(cliente[i].cpf, novoCpf);
                        printf("\nCPF alterado com sucesso!\n");
                        getchar();
                        break;

                    case 5:
                        printf("Digite o novo Telefone (Telefone atual: %s ): ", cliente[i].tel);
                        scanf("%lld", &cliente[i].tel);
                        printf("Telefone alterado com sucesso!\n");
                        getchar();
                        break;

                    case 6:
                        printf("Digite a nova data (dd/mm/aaaa) (Data atual: %s ): ", cliente[i].dat);
                        mascara_dat(cliente[i].dat);
                        strtok(cliente[i].dat, "\n");
                        printf("Data alterada com sucesso!\n");
                        break;

                    case 7:
                        printf("Saindo da edicao...\n");
                        break;
                    default:
                        printf("Opcao invalida.\n");
                        break;
                    }

                    sobrescreverClientesEmArquivo(cliente, numClientes);
                    
                    printf("\n");
                    system("pause");
                    system("cls");

                } while (editOp != 7);
            }
            break;
        }
    }

    if (!encontrado) {
        printf("Cliente com CPF %s nao encontrado.\n", CPF);
    }
}

//Função para remover cliente no arquivo TXT
void removerCliente(cliente_t cliente[], int *numClientes) {
    char CPF[14];
    printf("Digite o CPF para remover: ");
    scanf("%s", &CPF);
    getchar();

    int encontrado = 0;
    for (int i = 0; i < *numClientes; i++) {
        if (strcmp(cliente[i].cpf, CPF) == 0) {
            for (int j = i; j < *numClientes - 1; j++) {
                cliente[j] = cliente[j + 1];
            }
            (*numClientes)--;
            printf("Cliente removido com sucesso!\n");

            sobrescreverClientesEmArquivo(cliente, *numClientes);

            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Cliente com CPF %s nao encontrado.\n", CPF);
    }
}
