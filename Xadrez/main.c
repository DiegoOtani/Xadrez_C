#include <stdio.h>

//Inicializar o tabuleiro
void inic_tab(char tabuleiro[8][8]){
    char pecas[8][8] = {
        {'t', 'c', 'b', 'q', 'k', 'b', 'c', 't'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'T', 'C', 'B', 'Q', 'K', 'B', 'C', 'T'}
    };

    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            tabuleiro[i][j] = pecas[i][j];
        }
    }

    for(int i=2;i<6;i++){
        for(int j=0; j<8; j++){
            tabuleiro[i][j] = '-';
        }
    }
}

//Apresentar o tabuleiro
void apres_tab(char m[8][8]){
    printf("\n  1 2 3 4 5 6 7 8\n");
    for (int i = 0; i < 8; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < 8; j++) {
            printf("%c ", m[i][j]);
        }
        printf("\n");
    }
}

//Verificar se o salto é válido
int salto_valido(char m[8][8], int lin_o, int col_o, int lin_d, int col_d) {
    if (lin_d < 0 || lin_d >= 8 || col_d < 0 || col_d >= 8) {                   //salto não é valido para valores fora do tabuleiro
        return 0;
    }
    return 1;
}

//função responsável por realizar Movimento
void realizar_movimento(char m[8][8], int lin_o, int col_o, int lin_d, int col_d){

    m[lin_d][col_d] = m[lin_o][col_o];
    m[lin_o][col_o] = '-';
}

//Verificar movimento dos peões
int salto_peao(char m[8][8], int lin_o, int col_o, int lin_d, int col_d) {
    //Verificar validade do Movimento do peão(p)
    if (m[lin_o][col_o] == 'p') {
        if (lin_d == lin_o + 1 && col_d == col_o && m[lin_d][col_d] == '-') {
            return 1;
        } else if (lin_o == 1 && lin_d == lin_o + 2 && col_d == col_o && m[lin_d][col_d] == '-') {
            return 1;
        } else if ((lin_d == lin_o + 1 && col_d == col_o + 1 && m[lin_d][col_d] != '-') ||
                   (lin_d == lin_o + 1 && col_d == col_o - 1 && m[lin_d][col_d] != '-')) {
            return 1;
        } else {
            return 0;
        }
    //Verificar validade do Movimento do peão (P)
    }else if(m[lin_o][col_o] == 'P') {
        if(lin_d == lin_o - 1 && col_d == col_o && m[lin_d][col_d] == '-'){
            return 1;
        }else if (lin_o == 6 && lin_d == lin_o - 2 && col_d == col_o && m[lin_d][col_d] == '-') {
            return 1;
        }else if((lin_d == lin_o - 1 && col_d == col_o + 1 && m[lin_d][col_d] != '-') ||
        (lin_d == lin_o - 1 && col_d == col_o - 1 && m[lin_d][col_d] != '-')){
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}
//Verificar movimento da torre
int salto_torre(char m[8][8], int lin_o, int col_o, int lin_d, int col_d) {
    //Movimento para a direita
    if(lin_d == lin_o && col_d > col_o){
        for(int i = col_o + 1; i < col_d; i++){
            if(m[lin_o][i] != '-'){
                return 0;
            }
        }
        return 1;
    //Movimento para a esquerda
    } else if (lin_d == lin_o && col_d < col_o){
        for(int i = col_d; i < col_o; i++){
            if(m[lin_o][i] != '-'){
                return 0;
            }
        }
        return 1;
    //Movimento para baixo
    }else if(col_d == col_o && lin_d > lin_o){
        for(int i = lin_o + 1; i < lin_d; i++){
            if(m[i][col_o] != '-'){
                return 0;
            }
        }
        return 1;
    //Movimento para cima
    }else if(col_d == col_o && lin_d < lin_o){
        for(int i = lin_d; i < lin_o; i++){
            if(m[i][col_o] != '-'){
                return 0;
            }
        }
        return 1;
    }
    return 0;
}
//Verificar movimento do cavalo
int salto_cavalo(char m[8][8], int lin_o, int col_o, int lin_d, int col_d){
    if(lin_d == lin_o + 2 && col_d == col_o + 1 || lin_d == lin_o + 2 && col_d == col_o - 1 || lin_d == lin_o -2 && col_d == col_o + 1||lin_d == lin_o -2 && col_d == col_o - 1||
    lin_d == lin_o + 1 && col_d == col_o + 2 ||lin_d == lin_o - 1 && col_d == col_o + 2||lin_d == lin_o + 1 && col_d == col_o - 2||lin_d == lin_o - 1 && col_d == col_o - 2){
        return 1;
    }else{
        return 0;
    }
}
//Verificar movimento do bispo
int salto_bispo(char m[8][8], int lin_o, int col_o, int lin_d, int col_d){
    // Verificar diagonal principal
    if (lin_d - lin_o == col_d - col_o) {
        int i, j;
        if (col_o < col_d && lin_o < lin_d) {
            for (i = lin_o + 1, j = col_o + 1; i < lin_d; i++, j++) {
                if (m[i][j] != '-') {
                    return 0;
                }
            }
            return 1;
        } else if (col_o > col_d && lin_o > lin_d) {
            for (i = lin_o - 1, j = col_o - 1; i > lin_d; i--, j--) {
                if (m[i][j] != '-') {
                    return 0;
                }
            }
            return 1;
        }
    }
    // Verificar diagonal secundária
    else if (lin_d - lin_o == -(col_d - col_o)) {
        int i, j;
        if (col_o < col_d && lin_o > lin_d) {
            for (i = lin_o - 1, j = col_o + 1; i > lin_d; i--, j++) {
                if (m[i][j] != '-') {
                    return 0;
                }
            }
            return 1;
        } else if (col_o > col_d && lin_o < lin_d) {
            for (i = lin_o + 1, j = col_o - 1; i < lin_d; i++, j--) {
                if (m[i][j] != '-') {
                    return 0;
                }
            }
            return 1;
        }
    }
    return 0;
}
//Verificar validade do movimento da rainha
int salto_rainha(char m[8][8], int lin_o, int col_o, int lin_d, int col_d){
    if(salto_torre(m, lin_o, col_o, lin_d, col_d)){
        return 1;
    }else if(salto_bispo(m, lin_o, col_o, lin_d, col_d)){
        return 1;
    } else {
        return 0;
    }
}
//Verificar validade do movimento do rei
int salto_rei(char m[8][8], int lin_o, int col_o, int lin_d, int col_d){
    if(lin_d == lin_o + 1 && col_d == col_o || lin_d == lin_o - 1 && col_d == col_o){
        return 1;
    } else if(lin_d == lin_o && col_d == col_o + 1 || lin_d == lin_o && col_d == col_o - 1){
        return 1;
    } else if(lin_d == lin_o + 1 && col_d == col_o + 1||lin_d == lin_o + 1 && col_d == col_o -1||lin_d == lin_o - 1 &&col_d==col_o + 1||lin_d==lin_o - 1 &&col_d==col_o - 1){
        return 1;
    }else{
        return 0;
    }
}

//Verificar se a casa de destino contém uma peça que pode ser comida
int verificar_comer(char m[8][8], int lin_o, int col_o, int lin_d, int col_d){
    if(m[lin_o][col_o] == 'p'||m[lin_o][col_o] =='c'||m[lin_o][col_o] =='t'||m[lin_o][col_o] =='b'||m[lin_o][col_o] =='q'||m[lin_o][col_o] =='k'){
        if(m[lin_d][col_d] == 'p'||m[lin_d][col_d] =='c'||m[lin_d][col_d] =='t'||m[lin_d][col_d] =='b'||m[lin_d][col_d] =='q'||m[lin_d][col_d] =='k'){
            return 0;
        } else{
            return 1;
        }
    }else if(m[lin_o][col_o] == 'P'||m[lin_o][col_o] =='C'||m[lin_o][col_o] =='T'||m[lin_o][col_o] =='B'||m[lin_o][col_o] =='Q'||m[lin_o][col_o] =='K'){
        if(m[lin_d][col_d] == 'P'||m[lin_d][col_d] =='C'||m[lin_d][col_d] =='T'||m[lin_d][col_d] =='B'||m[lin_d][col_d] =='Q'||m[lin_d][col_d] =='K'){
            return 0;
        } else{
            return 1;
        }
    }
}

//Verificar a peça que realizará o salto
int reconhecer_peca(char m[8][8], int lin_o, int col_o, int lin_d, int col_d){
    if(m[lin_o][col_o] != '-'){
        if(m[lin_o][col_o]== 'p' || m[lin_o][col_o]== 'P'){
            if(salto_peao(m, lin_o, col_o, lin_d, col_d)){
                return 1;
            } else{
                return 0;
            }
        } else if(m[lin_o][col_o]== 't' || m[lin_o][col_o]== 'T'){
            if(salto_torre(m, lin_o, col_o, lin_d, col_d)){
                return 1;
            } else{
                return 0;
            }
        }else if (m[lin_o][col_o] == 'c' || m[lin_o][col_o] == 'C'){
            if(salto_cavalo(m, lin_o, col_o, lin_d, col_d)){
                return 1;
            } else{
                return 0;
            }
        }else if (m[lin_o][col_o] == 'b' || m[lin_o][col_o] == 'B'){
            if(salto_bispo(m, lin_o, col_o, lin_d, col_d)){
                return 1;
            } else{
                return 0;
            }
        }else if (m[lin_o][col_o] == 'q' || m[lin_o][col_o] == 'Q'){
            if(salto_rainha(m, lin_o, col_o, lin_d, col_d)){
                return 1;
            } else{
                return 0;
            }
        }else if (m[lin_o][col_o] == 'k' || m[lin_o][col_o] == 'K'){
            if(salto_rei(m, lin_o, col_o, lin_d, col_d)){
                return 1;
            } else{
                return 0;
            }
        }
    } else {
        return 0;
    }
}
//Função responsável por verificar a vitória
int verificar_vitoria(char m[8][8], int lin_d, int col_d){
    if(m[lin_d][col_d] == 'k'||m[lin_d][col_d] == 'K'){
        printf("\nFim de partida.\n");
        return 1;
    }
    return 0;
}

char verificar_equipe(char m[8][8], int lin_o, int col_o){
    if(m[lin_o][col_o] == 'p' || m[lin_o][col_o] == 't' || m[lin_o][col_o] == 'c' || m[lin_o][col_o] == 'b' || m[lin_o][col_o] == 'q'){
        return 'B';
    } else if(m[lin_o][col_o] == 'P' || m[lin_o][col_o] == 'T' || m[lin_o][col_o] == 'C' || m[lin_o][col_o] == 'B' || m[lin_o][col_o] == 'Q'){
        return 'P';
    }

    return 'N';
}

//Verificar se o rei está em xeque
int verificar_xeque(char m[8][8], int lin_o, int col_o, int lin_d, int col_d) {
    int rei_branco_linha = 0, rei_branco_coluna = 0;
    int rei_preto_linha = 0, rei_preto_coluna = 0;

    // Encontrar as posições dos reis branco e preto
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (m[i][j] == 'k') {
                rei_preto_linha = i;
                rei_preto_coluna = j;
            } else if (m[i][j] == 'K') {
                rei_branco_linha = i;
                rei_branco_coluna = j;
            }
        }
    }

    // Verificar se a peça movida pode atacar o rei adversário
    if (verificar_equipe(m, lin_o, col_o) == 'B') {
        if (reconhecer_peca(m, lin_o, col_o, lin_d, col_d)) {
            if (reconhecer_peca(m, lin_o, col_o, rei_preto_linha, rei_preto_coluna)) {
                return 1; // Está em xeque
            }
        }
    } else if (verificar_equipe(m, lin_o, col_o) == 'P') {
        if (reconhecer_peca(m, lin_o, col_o, lin_d, col_d)) {
            if (reconhecer_peca(m, lin_o, col_o, rei_branco_linha, rei_branco_coluna)) {
                return 1; // Está em xeque
            }
        }
    }

    return 0; // Não está em xeque
}


int main()
{
    char tab[8][8];     //Tabuleiro
    int lin_o, col_o, lin_d, col_d;  // Dados da jogada

    inic_tab(tab);

    do{
        apres_tab(tab);

        // Solicitar a casa de origem
        printf("\nDigite a linha da casa de origem (1-8) ou 0 para desistir: ");
        scanf("%d", &lin_o);
        if (lin_o == 0) {
            break;
        }
        printf("\nDigite a coluna da casa de origem (1-8) ou 0 para desistir: ");
        scanf("%d", &col_o);
        if (col_o == 0) {
            break;
        }

        // Solicitar a casa de destino
        printf("\nDigite a linha da casa de destino (1-8) ou 0 para desistir: ");
        scanf("%d", &lin_d);
        if (lin_d == 0) {
            break;
        }
        printf("\nDigite a coluna da casa de destino (1-8) ou 0 para desistir:");
        scanf("%d", &col_d);
        if (col_d == 0) {
            break;
        }

        if(!salto_valido(tab, lin_o - 1, col_o - 1, lin_d - 1, col_d - 1)) {
            printf("\nJogada inválida, tente novamente.\n");
        } else{
            if(verificar_comer(tab, lin_o - 1, col_o - 1, lin_d - 1, col_d - 1)){
                if((reconhecer_peca(tab, lin_o - 1, col_o - 1, lin_d - 1, col_d - 1))){
                    if(verificar_vitoria(tab, lin_d - 1, col_d - 1)){
                        break;
                    }else {
                        //verificar se o rei está em Xeque-mate
                        if(verificar_xeque(tab, lin_o - 1, col_o - 1, lin_d - 1, col_d - 1)){
                            printf("\nXeque!\n");
                        }
                        realizar_movimento(tab, lin_o - 1, col_o - 1, lin_d - 1, col_d - 1);
                    }
                } else{
                    printf("\nJogada inválida, tente novamente.\n");
                }
            } else{
                printf("\nJogada inválida, tente novamente.\n");
            }
        }
    }while(1);

    // Perguntar ao jogador se deseja jogar novamente
    char jogar_novamente;
    printf("\nDeseja jogar novamente? (S/N):\n");
    scanf(" %c", &jogar_novamente);

    if (jogar_novamente == 'S' || jogar_novamente == 's') {
        // Reiniciar o jogo
        printf("\n");
        main();
    } else {
        printf("\nFim do jogo.\n");
    }

    return 0;
}

