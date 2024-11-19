// Cad_fornecedor.h

#ifndef CAD_FORNECEDOR_H
#define CAD_FORNECEDOR_H

typedef struct {
    char nome[100];
    char endereco[130];
    char cidade[40];
    char cep[10];
    char dat[11];
    char cnpj[20];
    int id;
} fornecedor_t;

void adicionarFornecedorEmArquivo(fornecedor_t fornecedor);
void sobrescreverFornecedoresEmArquivo(fornecedor_t fornecedor[], int numFornecedores);
int carregarFornecedoresDeArquivo(fornecedor_t fornecedor[]);
void adicionarFornecedor(fornecedor_t fornecedor[], int *numFornecedores);
void visualizarFornecedores(fornecedor_t fornecedor[], int numFornecedores);
void pesquisarFornecedor(fornecedor_t fornecedor[], int numFornecedores);
void removerFornecedor(fornecedor_t fornecedor[], int *numFornecedores);

#endif // CAD_FORNECEDOR_H
