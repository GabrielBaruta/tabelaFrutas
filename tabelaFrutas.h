#ifndef tabelaFrutas_h
#define tabelaFrutas_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAMANHO_TABELA 10

// Estrutura para representar uma fruta
typedef struct Fruta {
    char nome[50];
    struct Fruta *proxima;
} Fruta;

// Estrutura para a Tabela Hash
typedef struct TabelaHash {
    Fruta *entradas[TAMANHO_TABELA];
    int numero_colisoes;
} TabelaHash;

TabelaHash* inicializarTabelaHash();
int funcao_hash_analise_digitos(const char *chave);

void inserirFruta(TabelaHash *th, const char *nomeFruta);
void imprimirTabelaHash(TabelaHash *th);
Fruta* buscarFruta(TabelaHash *th, const char *nomeFruta);
void removerFruta(TabelaHash *th, const char *nomeFruta);
void exibirTabelaHash(TabelaHash *th);
void liberarTabelaHash(TabelaHash *th);

double calcularTempoMedioBusca(TabelaHash *th, const char *frutasParaBuscar[], int numFrutas);
#endif // tabelaFrutas_h
