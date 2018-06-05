#include "jogodavelha.h"

int check_win(char *mapa) {
	int i, j, cont;
	if((mapa[0] == mapa[4] && mapa[4] == mapa[8]) || (mapa[2] == mapa[4] && mapa[4] == mapa[6]))
		return 1;
	if((mapa[0] == mapa[1] && mapa[1] == mapa[2]) || (mapa[3] == mapa[4] && mapa[4] == mapa[5]) || (mapa[6] == mapa[7] && mapa[7] == mapa[8]))
		return 1;
	if((mapa[0] == mapa[3] && mapa[3] == mapa[6]) || (mapa[1] == mapa[4] && mapa[4] == mapa[7]) || (mapa[2] == mapa[5] && mapa[5] == mapa[8]))
		return 1;
	cont = i = 0;
	while(i < 9){
		if(mapa[i] == 'X' || mapa[i] == 'O')
			cont++;
		i++;
	}
	if(cont == 9)
		return -1;
	return 0;
}

int jogar(int n, char *mapa, char jogada) {
	if(mapa[n] == 'X' || mapa[n] == 'O') {
		return 0;
	}
	mapa[n] = jogada;
	return 1;
}

void print_char(int qtd, char c, int type) {
	if(qtd == 0) {
		if(type)
			printf("|\n");
		else
			printf("\n");
		return;
	}
	printf("%c", c);
	print_char(qtd-1, c, type);
}

void resumo_jogo(_jogador *jog, int qtd_emp) {
	printf("\t ------------------------");
	int t = (strlen(jog[0].nome) > strlen(jog[1].nome) ? strlen(jog[0].nome) : strlen(jog[1].nome));
	
	print_char(t, '-', 0);
	
	printf("\t| RESUMO DO JOGO         ");
	print_char(t, ' ', 1);

	printf("\t| O(A) %s venceu %d veze(s) ", jog[0].nome, jog[0].qtd_vitorias);
	print_char(t - strlen(jog[0].nome), ' ', 1);
	
	printf("\t| O(A) %s venceu %d veze(s) ", jog[1].nome, jog[1].qtd_vitorias);
	print_char(t - strlen(jog[1].nome), ' ', 1);
	
	printf("\t| HOUVE(RAM) %d EMPATE(S) ", qtd_emp);
	print_char(t, ' ', 1);
	
	printf("\t ------------------------");
	print_char(t, '-', 0);
}

char *string_upr(char *str) {
	int i;
	for(i = 0; str[i] != '\0'; i++) {
		str[i] = toupper(str[i]);
	}
	return str;
}

void print_mapa(char *mapa) {
	int i, j, k = 0;
	for(i = 0; i < 3; i++){		
		for(j = 0; j < 3; j++){
			if(j == 1) {
				printf(" | %c | ", mapa[k]);
			} else {
				printf(" %c", mapa[k]);
			}
			k++;
		}
		if(i < 2)
			printf("\n------------\n");
		else 
			printf("\n");
	}
}

void restart(char *mapa) {
	int i = 0;
	while(i < 9) {
		mapa[i] = '0' + i;
		i++;
	}
}

int computer(char *mapa) {
	int points[9], pos_maior, maior, i;
	// zera todas as posições
	for(i = 0; i < 9; i++) {
		points[i] = 0;
	}
	// verifica o centro
	if(mapa[4] == '4'){
		points[4] += 2;
	}

	// verifica os cantos
	if(mapa[0] == '0'){
		points[0] += 1;
	} 
	if(mapa[2] == '2') {
		points[2] += 1;
	}
	if(mapa[6] == '6') {
		points[6] += 1;
	}
	if(mapa[8] == '8') {
		points[8] += 1;
	}

	// chance de vitória na posição 0
	if(mapa[0] == '0') {
		if(mapa[1] == 'O' && mapa[2] == 'O') {
			points[0] += 4;
		}
		if(mapa[3] == 'O' && mapa[6] == 'O') {
			points[0] += 4;
		}
		if(mapa[4] == 'O' && mapa[8] == 'O') {
			points[0] += 4;
		}
	}

	// chance de vitória na posição 1
	if(mapa[1] == '1') {
		if(mapa[0] == 'O' && mapa[2] == 'O') {
			points[1] += 4;
		}
		if(mapa[4] == 'O' && mapa[7] == 'O') {
			points[1] += 4;
		}
	}

	// chance de vitória na posição 2
	if(mapa[2] == '2'){
		if(mapa[0] == 'O' && mapa[1] == 'O'){
			points[2] += 4;
		}
		if(mapa[5] == 'O' && mapa[8] == 'O') {
			points[2] += 4;
		}
		if(mapa[4] == 'O' && mapa[6] == 'O') {
			points[2] += 4;
		}
	}

	// chance de vitória na posição 3
	if(mapa[3] == '3') {
		if(mapa[0] == 'O' && mapa[6] == 'O') {
			points[3] += 4;
		}
		if(mapa[4] == 'O' && mapa[5] == 'O') {
			points[3] += 4;
		}
	}

	// chance de vitória na posição 4
	if(mapa[4] == '4') {
		if(mapa[0] == 'O' && mapa[8] == 'O') {
			points[4] += 4;
		}
		if(mapa[1] == 'O' && mapa[7] == 'O') {
			points[4] += 4;
		}
		if(mapa[3] == 'O' && mapa[5] == 'O') {
			points[4] += 4;
		}
	}

	// chance de vitória na posição 5
	if(mapa[5] == '5'){
		if(mapa[3] == 'O' && mapa[4] == 'O'){
			points[5] += 4;
		}
		if(mapa[2] == 'O' && mapa[8] == 'O') {
			points[5] += 4;
		}
	}

	// chance de vitória na posição 6
	if(mapa[6] == '6') {
		if(mapa[0] == 'O' && mapa[3] == 'O') {
			points[6] += 4;
		}
		if(mapa[7] == 'O' && mapa[8] == 'O') {
			points[6] += 4;
		}
	}

	// chance de vitória na posição 7
	if(mapa[7] == '7') {
		if(mapa[6] == 'O' && mapa[8] == 'O') {
			points[7] += 4;
		}
		if(mapa[1] == 'O' && mapa[4] == 'O') {
			points[7] += 4;
		}
	}

	// chance de vitória na posição 8
	if(mapa[8] == '8') {
		if(mapa[2] == 'O' && mapa[5] == 'O') {
			points[8] += 4;
		}
		if(mapa[6] == 'O' && mapa[7] == 'O') {
			points[8] += 4;
		}
		if(mapa[0] == 'O' && mapa[4] == 'O') {
			points[8] += 4;
		}
	}

	// chance de evitar vitória na posiçao 0
	if(mapa[0] == '0') {
		if(mapa[4] == 'X' && mapa[8] == 'X') {
			points[0] += 4;
		}
		if(mapa[1] == 'X' && mapa[2] == 'X') {
			points[0] += 4;
		}
		if(mapa[3] == 'X' && mapa[6] == 'X') {
			points[0] += 4;
		}
	}

	// chance de evitar vitória na posição 1
	if(mapa[1] == '1') {
		if(mapa[0] == 'X' && mapa[2] == 'X') {
			points[1] += 4;
		}
		if(mapa[4] == 'X' && mapa[7] == 'X') {
			points[1] += 4;
		}
	}

	// chance de evitar vitória na posição 2
	if(mapa[2] == '2') {
		if(mapa[0] == 'X' && mapa[1] == 'X') {
			points[2] += 4;
		}
		if(mapa[4] == 'X' && mapa[6] == 'X') {
			points[2] += 4;
		}
		if(mapa[5] == 'X' && mapa[8] == 'X') {
			points[2] += 4;
		}
	}

	// chance de evitar vitória na posição 3
	if(mapa[3] == '3') {
		if(mapa[0] == 'X' && mapa[6] == 'X') {
			points[3] += 4;
		}
		if(mapa[4] == 'X' && mapa[5] == 'X') {
			points[3] += 4;
		}
	}
	// chance de evitar vitória na posição 4
	if(mapa[4] == '4') {
		if(mapa[0] == 'X' && mapa[8] == 'X') {
			points[4] += 4;
		}
		if(mapa[2] == 'X' && mapa[6] == 'X') {
			points[4] += 4;
		}
		if(mapa[1] == 'X' && mapa[7] == 'X') {
			points[4] += 4;
		}
		if(mapa[3] == 'X' && mapa[5] == 'X') {
			points[4] += 4;
		}
	}

	// chance de evitar vitória na posição 5
	if(mapa[5] == '5') {
		if(mapa[2] == 'X' && mapa[8] == 'X') {
			points[5] += 4;
		}
		if(mapa[3] == 'X' && mapa[4] == 'X') {
			points[5] += 4;
		}
	}

	// chance de evitar vitória na posição 6
	if(mapa[6] == '6') {
		if(mapa[0] == 'X' && mapa[3] == 'X') {
			points[6] += 4;
		}
		if(mapa[7] == 'X' && mapa[8] == 'X') {
			points[6] += 4;
		}
		if(mapa[2] == 'X' && mapa[4] == 'X') {
			points[6] += 4;
		}
	}

	// chance de evitar vitória na posição 7
	if(mapa[7] == '7') {
		if(mapa[1] == 'X' && mapa[4] == 'X') {
			points[7] += 4;
		}
		if(mapa[6] == 'X' && mapa[8] == 'X') {
			points[7] += 4;
		}
	}

	// chance de evitar vitória na posição 8
	if(mapa[8] == '8') {
		if(mapa[6] == 'X' && mapa[7] == 'X') {
			points[8] += 4;
		}
		if(mapa[0] == 'X' && mapa[4] == 'X') {
			points[8] += 4;
		}
		if(mapa[2] == 'X' && mapa[5] == 'X') {
			points[8] += 4;
		}
	}

	// checa se tem alguém na linha, coluna ou diagonal da posição 0
	if(mapa[0] == '0') {
		if(mapa[4] == 'X' || mapa[8] == 'X' || mapa[3] == 'X' || mapa[6] == 'X' || mapa[1] == 'X' || mapa[2] == 'X') {
			points[0] -= 2;
		}
	}
	// checa se tem alguém na linha, coluna ou diagonal da posição 1
	if(mapa[1] == '1') {
		if(mapa[4] == 'X' || mapa[7] == 'X' || mapa[0] == 'X' || mapa[2] == 'X') {
			points[1] -= 2;
		}
	}
	// checa se tem alguém na linha, coluna ou diagonal da posição 2
	if(mapa[2] == '2') {
		if(mapa[0] == 'X' || mapa[1] == 'X' || mapa[4] == 'X' || mapa[6] == 'X' || mapa[5] == 'X' || mapa[8] == 'X') {
			points[2] -= 2;
		}
	}
	// busca a maior pontuação salva sua posição, esta deve ser a jogada
	pos_maior = 0;
	maior = points[0];
	for(i = 1; i < 9; i++) {
		if(points[i] > maior) {
			maior = points[i];
			pos_maior = i;
		}
	}
	return pos_maior;
}

void game(int type_game) {
	char mapa[9], jogada;
	_jogador jog[2];
	int num, qtd_jogadas, end, continuar, qtd_emp;
	
	restart(mapa);	

	printf("Digite o nome do primeiro jogador: ");
	scanf("%[^\n]s", jog[0].nome);
	
	if(type_game == 1){
		printf("Digite o nome do segundo jogador: ");
		scanf(" %[^\n]s", jog[1].nome);
	} else {
		strcpy(jog[1].nome, "Ambrosildo");
	}
	
	jogada = 'X';
	qtd_jogadas = end = qtd_emp = jog[0].qtd_vitorias = jog[1].qtd_vitorias = 0;
	continuar = 1;
	
	while(end == 0) {	
		system("clear");
		printf("O jogo esta na %d rodada\n", qtd_jogadas+1);
		if(qtd_jogadas % 2 == 0) {
			printf("Eh a vez do(a) %s\n", jog[0].nome);
			jogada = 'X';
		} else {
			printf("Eh a vez do(a) %s\n", jog[1].nome);
			jogada = 'O';
		}
		print_mapa(mapa);
		if(jogada == 'O') {
			if(type_game == 1) {
				printf("Digite o numero onde voce quer jogar: ");
				scanf("%d", &num);
			} else {
				num = computer(mapa);
			}
		} else {
			printf("Digite o numero onde voce quer jogar: ");
			scanf("%d", &num);
		}
		if(jogar(num, mapa, jogada)) {
			end = check_win(mapa);
			if(end != 0) {
				if(end == -1) {
					printf("EMPATE\n");
					qtd_emp++;
				} else if(end == 1) {
					system("clear");
					printf("O(A) %s VENCEU, PARABENS\n", string_upr(jog[qtd_jogadas % 2].nome));
					jog[qtd_jogadas % 2].qtd_vitorias++;
				}
				print_mapa(mapa);
				printf("Gostaria de jogar de novo?\n[ 1 ] sim\n[outro valor] nao\n=> ");
				scanf("%d", &continuar);
				if(continuar == 1) {
					qtd_jogadas = -1;
					restart(mapa);
					end = 0;
				}
			}
			if(continuar == 1){
				qtd_jogadas++;
				print_mapa(mapa);
			} else {
				system("clear");
				resumo_jogo(jog, qtd_emp);
			}
		} else {
			printf("Posicao invalida, tente novamente\n");
		}
	}
}
