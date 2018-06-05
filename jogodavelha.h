#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#ifndef jogodavelha_h
#define jogodavelha_h

typedef struct jogador {
	char nome[100];
	int qtd_vitorias;
} _jogador;

int check_win(char *mapa);
int jogar(int n, char *mapa, char jogada);
void print_char(int qtd, char c, int type);
void resumo_jogo(_jogador *jog, int qtd_emp);
char *string_upr(char *str);
void print_mapa(char *mapa);
void restart(char *mapa);
void game(int type_game);

#endif