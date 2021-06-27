#include "headers/metro.h"
#include <iostream>
#include <stdio.h>

metro::metro(int _numero_estacoes, int _max_escalas_desconto_cumulativo){                           //construtor recebe o numero de estacoes (N) e o maximo de escalas a se aplicar desconto (D).
    this->numero_estacoes = _numero_estacoes;
    this->max_escalas_desconto_cumulativo = _max_escalas_desconto_cumulativo;
    vetor_descontos = new double[_max_escalas_desconto_cumulativo];
    vetor_tempos = new int[_numero_estacoes];
    vetor_custos = new int[_numero_estacoes];
}

void metro::insere_desconto_acumulado(int escala, double desconto){                                 //metodo para inserir desconto, recebe a posicao da escala e o valor do desconto.
    if(escala == 0){                                                                                //quando a escala eh 0, o desconto eh simplesmente o complemento da porcentagem.
        vetor_descontos[escala] = ((100-desconto)/100);
    }else{
        if (vetor_descontos[escala-1]-(desconto/100) < 0 || vetor_descontos[escala-1] == 0){        //condicao para evitar instabilidades, checa se o elemento anterior ja da desconto de 100% ou
            vetor_descontos[escala] = 0;                                                            //mesmo se ha valores negativos sendo entrados por alguma razao. caso contrario o desconto eh
        }else{                                                                                      //a % do valor anterior menos a % entrada.
            vetor_descontos[escala] = vetor_descontos[escala-1]-(desconto/100); 
        }
    }
}

void metro::insere_tempo_acumulado(int escala, int tempo){                                          //insere o tempo acumulando-o no vetor de tempos. caso a escala seja a primeira (0), na posicao
    if(escala == 0){                                                                                //0 insere-se o valor de 0, pois o tempo total acumulado ate a escala eh 0, e o tempo entrado eh
        vetor_tempos[escala] = 0;                                                                   //armazenado na proxima posicao.
        vetor_tempos[escala+1] = tempo;
    }else if(escala+1<numero_estacoes){                                                             //mesma ideia eh seguida ate a penultima escala (ou estacao), so que somando os tempos das escalas
        vetor_tempos[escala+1] = tempo;                                                             //anteriores para acumula-lo.
        vetor_tempos[escala] += vetor_tempos[escala-1];
    }else{                                                                                          //ultima estacao acumula o tempo anterior, e descarta o ultimo tempo inserido, pois eh o tempo ate
        vetor_tempos[escala] += vetor_tempos[escala-1];                                             //a chegada, que nao eh util para resolucao do problema.
    }
}

void metro::insere_preco(int escala, int preco){                                                    //recebe a posicao da escala e o preco, armazena na devida posicao no vetor de custos.
    vetor_custos[escala] = preco;
}

double metro::min(double a, double b){                                                              //funcao para retornar menor dentre dois numeros.
    if(a<=b){
        return a;
    }else{
        return b;
    }
}

void metro::calcula_custo(int Tmax){                                                                //metodo para calcular o custo e imprimi-lo, recebe o Tmax, o tempo maximo de um percurso (T).
    double** memoization = new double*[numero_estacoes+1];                                          //declaracao e alocacao de espaco para a matriz de memoizacao[numero_estacoes+1][numero_estacoes+1]
    for (int i = 0; i < numero_estacoes+1; ++i){                                                    //pois durante a primeira execucao do for externo precisaremos acessar posicoes que seriam proibidas,
        memoization[i] = new double[numero_estacoes+1];                                             //memoizacao[numero_estacoes+1][numero_estacoes+1] e memoizacao[numero_estacoes+1][ED].
    }
    
    for (int i = 0; i < numero_estacoes+1; i++){                                                    //zerando toda a matriz inicialmente.
        for (int j = 0; j < numero_estacoes+1; j++){
            memoization[i][j] = 0;
        }
    }

    for (int EA = numero_estacoes; EA>=0; EA--){                                                                //caminhando de baixo para cima na matriz de memoizacao. EA representa a estacao (ou escala) atual
        for (int ED=EA; ED>=0; ED--){                                                                           //e ED a estacao em que consideramos que o desconto comecou a ser aplicado.
            if(EA == numero_estacoes){                                                                          //quando a estacao atual eh a ultima, devemos atribuir custo 0 para ir dela ate a ultima.
                memoization[EA][ED] = 0;
            }else if(((EA-ED)>=max_escalas_desconto_cumulativo)||((vetor_tempos[EA]-vetor_tempos[ED])>=Tmax)){  //quando o numero de escalas percorridas excede o numero de escalas passiveis de receberem descontos ou 
                memoization[EA][ED] = 99999999999;                                                              //o tempo Tmax (tempo limite T de um percurso) eh atingido ou ultrapassado, nao vale a pena/nao se pode
            }                                                                                                   //continuar nessa sequencia, logo o custo atribuido eh infinito.
            else{
                memoization[EA][ED] = vetor_descontos[EA-ED]*vetor_custos[EA]+min(memoization[EA+1][EA+1],memoization[EA+1][ED]);  //quando em nenhuma das situacoes anteriores, calcula-se o custo a se pagar na estacao atual + o menor
            }                                                                                                                      //dentre os custos de se ir da proxima estacao ate o final, considerando-se que ou o desconto continua
        }                                                                                                                          //da estacao em que comecou (ED) ou comeca na proxima estacao (EA+1).
    }
    
    std::cout<<std::endl;
    for(int x=0;x<numero_estacoes+1;x++){
        for(int y=0;y<numero_estacoes+1;y++)
        {
            std::cout<<memoization[x][y]<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;

    std::cout<<"vetor de tempos: ";
    for (int i = 0; i < numero_estacoes; i++){
        std::cout<<vetor_tempos[i]<< " ";
    }
    std::cout<<std::endl;
    std::cout<<"vetor de custos: ";
    for (int i = 0; i < numero_estacoes; i++){
        std::cout<<vetor_custos[i]<< " ";
    }
    std::cout<<std::endl;
    std::cout<<"vetor de descontos: ";
    for (int i = 0; i < max_escalas_desconto_cumulativo; i++){
        std::cout<<vetor_descontos[i]<< " ";
    }
    std::cout<<std::endl;

    printf("%.2f", memoization[0][0]);                      //impressao da posicao [0][0] da matriz de memoizacao, onde teremos o custo de ir ate a estacao final, dado que a estacao atual e a estacao
                                                            //em que se comecou o desconto eh a primeira (0).
    delete memoization;                                     //liberando espaco ocupado ela matriz de memoizacao.
    std::cout<<std::endl;
}