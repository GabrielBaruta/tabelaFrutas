/*PARA RODAR: gcc main.c tabelaFrutas.c -o tabelaFrutas
./tabelaFrutas*/

#include "tabelaFrutas.h"
#include <time.h>

// --- FUNÇÕES DA TABELA HASH ---

TabelaHash* inicializarTabelaHash() {
    TabelaHash *novaTabela = (TabelaHash *) malloc(sizeof(TabelaHash));
    if (novaTabela == NULL) {
        perror("Erro ao alocar memoria para a tabela hash");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        novaTabela->entradas[i] = NULL;
    }
    novaTabela->numero_colisoes = 0;
    return novaTabela;
}

/* Função de Hash usando Análise de Dígitos:
Esta função demonstra o conceito de Análise de Dígitos para strings. Ela seleciona o primeiro, o terceiro e o último caractere (se existirem) da chave (nome da fruta)
e usa seus valores ASCII, combinados com fatores multiplicadores, para gerar um valor hash.
A escolha dessas posições é uma simulação, pois em um cenário real exigiria uma análise estatística prévia da distribuição dos caracteres nas chaves.*/

int funcao_hash_analise_digitos(const char *chave) {
    int valor_hash = 0;
    int tamanho_chave = strlen(chave);

    if (tamanho_chave > 0) {
        valor_hash += chave[0]; // Considera o primeiro caractere
    }
    if (tamanho_chave > 2) {
        valor_hash += chave[2] * 7; // Considera o terceiro caractere, com um peso
    }
    if (tamanho_chave > 1) {
        valor_hash += chave[tamanho_chave - 1] * 13; // Considera o último caractere, com outro peso
    }

    return valor_hash % TAMANHO_TABELA;
}

void inserirFruta(TabelaHash *th, const char *nomeFruta) {
    int indice = funcao_hash_analise_digitos(nomeFruta);

    Fruta *novaFruta = (Fruta *) malloc(sizeof(Fruta));
    if (novaFruta == NULL) {
        perror("Erro ao alocar memoria para a fruta");
        exit(EXIT_FAILURE);
    }
    strncpy(novaFruta->nome, nomeFruta, sizeof(novaFruta->nome) - 1);
    novaFruta->nome[sizeof(novaFruta->nome) - 1] = '\0';
    novaFruta->proxima = NULL;

    if (th->entradas[indice] == NULL) {
        th->entradas[indice] = novaFruta;
    } else {
        // Colisão: insere no início da lista encadeada
        th->numero_colisoes++;
        novaFruta->proxima = th->entradas[indice];
        th->entradas[indice] = novaFruta;
        printf("  >> Colisao detectada para '%s' (indice %d).\n", nomeFruta, indice);
    }
    printf("Fruta '%s' inserida no indice %d.\n", nomeFruta, indice);
}

Fruta* buscarFruta(TabelaHash *th, const char *nomeFruta) {
    int indice = funcao_hash_analise_digitos(nomeFruta);
    Fruta *atual = th->entradas[indice];

    printf("Buscando '%s' no indice %d...\n", nomeFruta, indice);
    while (atual != NULL) {
        if (strcmp(atual->nome, nomeFruta) == 0) {
            printf("  Fruta '%s' encontrada!\n", nomeFruta);
            return atual;
        }
        atual = atual->proxima;
    }
    printf("  Fruta '%s' NAO encontrada.\n", nomeFruta);
    return NULL;
}

void removerFruta(TabelaHash *th, const char *nomeFruta) {
    int indice = funcao_hash_analise_digitos(nomeFruta);
    Fruta *atual = th->entradas[indice];
    Fruta *anterior = NULL;

    printf("Removendo '%s' do indice %d...\n", nomeFruta, indice);
    while (atual != NULL && strcmp(atual->nome, nomeFruta) != 0) {
        anterior = atual;
        atual = atual->proxima;
    }

    if (atual == NULL) {
        printf("  Fruta '%s' NAO encontrada para remocao.\n", nomeFruta);
        return;
    }

    if (anterior == NULL) {
        th->entradas[indice] = atual->proxima;
    } else {
        anterior->proxima = atual->proxima;
    }
    free(atual);
    printf("  Fruta '%s' removida com sucesso.\n", nomeFruta);
}

void exibirTabelaHash(TabelaHash *th) {
    printf("\n--- Conteudo da Tabela Hash ---\n");
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        printf("Indice %d:", i);
        Fruta *atual = th->entradas[i];
        while (atual != NULL) {
            printf(" -> %s", atual->nome);
            atual = atual->proxima;
        }
        printf(" -> NULL\n");
    }
    printf("--- Fim da Tabela Hash ---\n");
    printf("Total de colisoes registradas: %d\n", th->numero_colisoes);
}

void liberarTabelaHash(TabelaHash *th) {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        Fruta *atual = th->entradas[i];
        while (atual != NULL) {
            Fruta *temp = atual;
            atual = atual->proxima;
            free(temp);
        }
    }
    free(th);
    printf("\nMemoria da tabela hash liberada.\n");
}

// Calcula o tempo médio para buscar um conjunto de frutas na tabela hash (Retorna o tempo médio em milissegundos)
double calcularTempoMedioBusca(TabelaHash *th, const char *frutasParaBuscar[], int numFrutas) {
    clock_t inicio_total, fim_total;
    double tempo_total_em_ms = 0.0;

    printf("\n>>> Calculando tempo medio de busca para %d frutas...\n", numFrutas);

    inicio_total = clock(); // Marca o tempo de início para todas as buscas

    for (int i = 0; i < numFrutas; i++) {
        buscarFruta(th, frutasParaBuscar[i]);
    }

    fim_total = clock(); // Marca o tempo de fim após todas as buscas

    // Calcula o tempo total em milissegundos
    tempo_total_em_ms = ((double)(fim_total - inicio_total) * 1000.0) / CLOCKS_PER_SEC;

    printf("Total de buscas realizadas: %d\n", numFrutas);
    printf("Tempo total gasto: %.2f ms\n", tempo_total_em_ms);
    printf("Tempo medio por busca: %.2f ms\n", tempo_total_em_ms / numFrutas);

    return tempo_total_em_ms / numFrutas; // Retorna o tempo médio em milissegundos
}