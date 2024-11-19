#ifndef VENDA_H
#define VENDA_H

typedef struct {
    char produto[100];
    int quantidade;
    float precoUnitario;
    float totalVenda;
    char data[11]; 
     char hora[6];  
} venda_t;

int carregarVendasDeArquivo(venda_t vendas[]);

#endif
