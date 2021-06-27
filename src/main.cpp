#include <iostream>
#include <sstream>
#include "headers/metro.h"


int main(){
    int N, D, T;                                        

    std::string linha;                                  //leitura da primeira linha e atribuicao dos valores nas devidas variaveis.
    std::getline(std::cin,linha);
    std::istringstream leitura_inicial(linha);
    leitura_inicial>>N;
    leitura_inicial>>D;
    leitura_inicial>>T;
    
    metro metro(N,D);                                   //instanciacao e chamada do construtor da classe metro.
    
    std::getline(std::cin, linha);                      //leitura e atribuicao dos descontos acumulados no metro.
    std::istringstream d_i(linha);
    for(int i = 0; i < D; i++){
        double desconto;
        d_i>>desconto;
        metro.insere_desconto_acumulado(i,desconto);
    }

    for(int i = 0; i < N; i++){                         //leitura e atribuicao dos tempos e precos associados a cada escala.
        int t_i,c_i;
        std::getline(std::cin, linha);
        std::istringstream tempos_e_precos(linha);       
        tempos_e_precos>>t_i;
        tempos_e_precos>>c_i;
        metro.insere_preco(i, c_i);
        metro.insere_tempo_acumulado(i,t_i);
    }

    metro.calcula_custo(T);                             //chamada do metodo calcula_custo() para impressao do resultado.

    return 0;
}