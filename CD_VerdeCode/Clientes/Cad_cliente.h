#ifndef CLIENTE_H
#define CLIENTE_H

typedef struct cliente_t {
    char nome[100];
    char endereco[100];
    char email[100];
    char cpf[14];
    long long int tel;
    char dat[11];
} cliente_t;

void adicionarClienteEmArquivo(cliente_t cliente);
void sobrescreverClientesEmArquivo(cliente_t cliente[], int numClientes);
int carregarClientesDeArquivo(cliente_t cliente[]);
void adicionarCliente(cliente_t cliente[], int *numClientes);
void visualizarClientes(cliente_t cliente[], int numClientes);
void pesquisarCliente(cliente_t cliente[], int numClientes);
void removerCliente(cliente_t cliente[], int *numClientes);

#endif
