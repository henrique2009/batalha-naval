#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct jogador{
    string nome;
    int local = 1;
   
};

void layout(){
    cout << "=============================================================================\n";
    cout << "██████╗ ███████╗███╗   ███╗    ██╗   ██╗██╗███╗   ██╗██████╗  ██████╗       \n";
    cout << "██╔══██╗██╔════╝████╗ ████║    ██║   ██║██║████╗  ██║██╔══██╗██╔═══██╗      \n";
    cout << "██████╔╝█████╗  ██╔████╔██║    ██║   ██║██║██╔██╗ ██║██║  ██║██║   ██║      \n";
    cout << "██╔══██╗██╔══╝  ██║╚██╔╝██║    ╚██╗ ██╔╝██║██║╚██╗██║██║  ██║██║   ██║      \n";
    cout << "██████╔╝███████╗██║ ╚═╝ ██║     ╚████╔╝ ██║██║ ╚████║██████╔╝╚██████╔╝      \n";
    cout << "╚═════╝ ╚══════╝╚═╝     ╚═╝      ╚═══╝  ╚═╝╚═╝  ╚═══╝╚═════╝  ╚═════╝       \n";
    cout << "=============================================================================\n";
    cout << "                      A O   J O G O   D A   G L O R I A                      \n";
    cout << "=============================================================================\n";
}


int quantos_jogares(){
    int quantidade;
    bool automatico = true;

    while (automatico){
        cout<<"Quantidade de jogadores: ";
        cin >> quantidade;
        
        if(quantidade < 2){
            cout <<"Numero minimo de jogadores é de 2"<<endl;
        }
        else if(quantidade <= 5){
            automatico =false;
        }
        else{
            cout <<"Numero limite de jogadores é de 5"<<endl;
        }

       
    }

    
return quantidade;
}
int dado(){;
 return rand() % 6+1;
}
void mostrarTabuleiro(int posicaoJogador) {
    const int NUM_CASAS = 30;

    cout << "\n=== TABULEIRO DO JOGO DA GLÓRIA ===\n";

    for (int i = 1; i <= NUM_CASAS; i++) {
        // Se for a posição do jogador, mostra um marcador especial
        if (i == posicaoJogador)
            cout << "[P]";
        else
            cout << "[" << i << "]";

        // Quebra a linha a cada 10 casas (só estética)
        if (i % 10 == 0)
            cout << endl;
        else
            cout << " ";
    }

    cout << "\n";
}

int main(){
    srand(time(0));
        
    layout();
    int quantidade = quantos_jogares();
    jogador P[quantidade];
    
        for(int i=0; i<quantidade; i++){
            cout<<"Digite o nome para o jogador: "<< i+1 <<endl;
            cin >> P[i].nome;
        }  
    
    
    return 0;
}