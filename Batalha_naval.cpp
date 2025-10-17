
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int TAM = 10;
const char AGUA = '~';
const char NAVIO = 'N';
const char TIRO_ACERTO = 'X';
const char TIRO_ERRO = 'O';

struct Barco {
    string nome;
    int tamanho;
    int quantidade;
};

void inicializarTabuleiro(char tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tab[i][j] = AGUA;
}

void mostrarTabuleiro(char tab[TAM][TAM], bool mostrarNavios) {
    cout << "  ";
    for (int i = 0; i < TAM; i++) cout << i << " ";
    cout << endl;
    for (int i = 0; i < TAM; i++) {
        cout << i << " ";
        for (int j = 0; j < TAM; j++) {
            if (tab[i][j] == NAVIO && !mostrarNavios)
                cout << AGUA << " ";
            else
                cout << tab[i][j] << " ";
        }
        cout << endl;
    }
}

bool podeColocar(char tab[TAM][TAM], int x, int y, int tamanho, bool horizontal) {
    if (horizontal) {
        if (y + tamanho > TAM) return false;
        for (int i = 0; i < tamanho; i++)
            if (tab[x][y + i] != AGUA) return false;
    } else {
        if (x + tamanho > TAM) return false;
        for (int i = 0; i < tamanho; i++)
            if (tab[x + i][y] != AGUA) return false;
    }
    return true;
}

void colocarBarco(char tab[TAM][TAM], int x, int y, int tamanho, bool horizontal) {
    if (horizontal)
        for (int i = 0; i < tamanho; i++)
            tab[x][y + i] = NAVIO;
    else
        for (int i = 0; i < tamanho; i++)
            tab[x + i][y] = NAVIO;
}

void colocarBarcosAleatorios(char tab[TAM][TAM], Barco barcos[], int numBarcos) {
    for (int b = 0; b < numBarcos; b++) {
        for (int q = 0; q < barcos[b].quantidade; q++) {
            bool colocado = false;
            while (!colocado) {
                int x = rand() % TAM;
                int y = rand() % TAM;
                bool horizontal = rand() % 2;
                if (podeColocar(tab, x, y, barcos[b].tamanho, horizontal)) {
                    colocarBarco(tab, x, y, barcos[b].tamanho, horizontal);
                    colocado = true;
                }
            }
        }
    }
}

void colocarBarcosJogador(char tab[TAM][TAM], Barco barcos[], int numBarcos) {
    cout << "\n=== Coloque os seus barcos ===\n";
    for (int b = 0; b < numBarcos; b++) {
        for (int q = 0; q < barcos[b].quantidade; q++) {
            bool colocado = false;
            while (!colocado) {
                int linha, coluna;
                char orientacao;

                cout << "\nColocar " << barcos[b].nome
                     << " (tamanho " << barcos[b].tamanho << ")\n";
                mostrarTabuleiro(tab, true);
                cout << "Linha inicial (0-9): ";
                cin >> linha;
                cout << "Coluna inicial (0-9): ";
                cin >> coluna;
                cout << "Horizontal (H) ou Vertical (V)? ";
                cin >> orientacao;

                bool horizontal = (orientacao == 'H' || orientacao == 'h');

                if (podeColocar(tab, linha, coluna, barcos[b].tamanho, horizontal)) {
                    colocarBarco(tab, linha, coluna, barcos[b].tamanho, horizontal);
                    colocado = true;
                } else {
                    cout << " Nao e possivel colocar o barco aqui. Tente outra posicao.\n";
                }
            }
        }
    }
}

bool realizarTiro(char tab[TAM][TAM], int linha, int coluna) {
    if (linha < 0 || linha >= TAM || coluna < 0 || coluna >= TAM) {
        cout << "Coordenadas invalidas!\n";
        return false;
    }

    if (tab[linha][coluna] == NAVIO) {
        tab[linha][coluna] = TIRO_ACERTO;
        cout << "Acertou um navio!\n";
        return true;
    } else if (tab[linha][coluna] == AGUA) {
        tab[linha][coluna] = TIRO_ERRO;
        cout << " Agua!\n";
    } else {
        cout << " Ja atirou aqui!\n";
    }
    return false;
}

bool venceu(char tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            if (tab[i][j] == NAVIO)
                return false;
    return true;
}

int main() {
    srand(time(0));

    char jogador[TAM][TAM], computador[TAM][TAM];
    inicializarTabuleiro(jogador);
    inicializarTabuleiro(computador);

    Barco barcos[] = {
        {"Porta-avioes", 5, 1},
        {"Navio-tanque", 4, 1},
        {"Contratorpedeiro", 3, 1},
        {"Submarino", 3, 1},
        {"Destroier", 2, 1}
    };
    int numBarcos = sizeof(barcos) / sizeof(barcos[0]);

    colocarBarcosJogador(jogador, barcos, numBarcos);
    colocarBarcosAleatorios(computador, barcos, numBarcos);

    int linha, coluna;

    cout << "\n=== BATALHA NAVAL ===\n";

    while (true) {
        cout << "\nO teu tabuleiro:\n";
        mostrarTabuleiro(jogador, true);
        cout << "\nTabuleiro inimigo:\n";
        mostrarTabuleiro(computador, false);

        cout << "\nDigite linha e coluna para atacar (0-9): ";
        cin >> linha >> coluna;

        realizarTiro(computador, linha, coluna);

        if (venceu(computador)) {
            cout << " Tu venceste!\n";
            break;
        }

        linha = rand() % TAM;
        coluna = rand() % TAM;
        cout << "\nComputador atira em (" << linha << "," << coluna << ")\n";
        realizarTiro(jogador, linha, coluna);

        if (venceu(jogador)) {
            cout << " O computador venceu!\n";
            break;
        }
    }

    return 0;
}