#ifndef CAD_PRODUTO_H
#define CAD_PRODUTO_H

typedef struct {
    char nome[100];
    float prec;
    int quant;
    int idProd;
    char dat[11];
    char cat[20];
} produto_t;

// Fun��es para manipular produtos (declaracoes)
void adicionarProduto(produto_t produto[], int *numProdutos);
void visualizarProdutos(produto_t produto[], int numProdutos);
void pesquisarProduto(produto_t produto[], int numProdutos);
void removerProduto(produto_t produto[], int *numProdutos);
void sobrescreverProdutosEmArquivo(produto_t produto[], int numProdutos);
int carregarProdutosDeArquivo(produto_t produto[]);

#endif
