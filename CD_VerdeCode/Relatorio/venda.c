#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "venda.h"

int carregarVendasDeArquivo(venda_t vendas[]) {
    FILE *arquivo = fopen("Relatorio/vendas.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de vendas.\n");
        return 0;
    }

    int numVendas = 0;
    char linha[256];

    while (fgets(linha, sizeof(linha), arquivo)) {
        sscanf(linha, "Produto: %99[^,], Quantidade: %d, Preco Unitario: %f, Total: %f, Data: %10s, Hora: %5s\n", 
               vendas[numVendas].produto, 
               &vendas[numVendas].quantidade, 
               &vendas[numVendas].precoUnitario, 
               &vendas[numVendas].totalVenda, 
               vendas[numVendas].data, 
               vendas[numVendas].hora);
        numVendas++;
    }

    fclose(arquivo);
    return numVendas;
}
