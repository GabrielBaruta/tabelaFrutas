#include "tabelaFrutas.h"

int main() {
    TabelaHash *minhaTabela = inicializarTabelaHash();

    printf(">>> Inserindo frutas...\n");

    inserirFruta(minhaTabela, "Maca");
    inserirFruta(minhaTabela, "Kiwi");
    inserirFruta(minhaTabela, "Banana");
    inserirFruta(minhaTabela, "Abacaxi");
    inserirFruta(minhaTabela, "Morango");
    inserirFruta(minhaTabela, "Pera");
    inserirFruta(minhaTabela, "Uva");
    inserirFruta(minhaTabela, "Laranja");
    inserirFruta(minhaTabela, "Manga");
    inserirFruta(minhaTabela, "Amora");
    inserirFruta(minhaTabela, "Melao");

    exibirTabelaHash(minhaTabela);

    printf("\n>>> Realizando buscas...\n");
    buscarFruta(minhaTabela, "Banana");
    buscarFruta(minhaTabela, "Kiwi");
    buscarFruta(minhaTabela, "Manga");
    buscarFruta(minhaTabela, "Maca");

    printf("\n>>> Removendo frutas...\n");
    removerFruta(minhaTabela, "Abacaxi");
    removerFruta(minhaTabela, "Kiwi");
    removerFruta(minhaTabela, "Manga");

    exibirTabelaHash(minhaTabela);

    liberarTabelaHash(minhaTabela);

    //tempo Médio de Busca
    const char *frutas_teste_busca[] = {
        "Maca", "Banana", "Morango", "Abacaxi", "Kiwi", "Laranja", "Manga", "Uva", "Amora", "Pera", "Abacate"
    };
    int num_frutas_teste = sizeof(frutas_teste_busca) / sizeof(frutas_teste_busca[0]);

    // Calcula e exibe o tempo médio de busca
    double tempo_medio = calcularTempoMedioBusca(minhaTabela, frutas_teste_busca, num_frutas_teste);
    printf("Resultado: Tempo medio de busca por fruta = %.2f ms\n", tempo_medio);

    return 0;
}

