#ifndef METRO_H
#define METRO_h

class metro{
    private:
        int numero_estacoes;                                   //atributo para denotar o numero estacoes dentro do metro, ou seja, onde ocorrerao as escalas.
        int max_escalas_desconto_cumulativo;                   //atributo para denotar numero maximo de escalas que receberao desconto cumulativo dentro de um tempo T.
        double* vetor_descontos;                               //vetor para armazenar o complemento da porcentagem do desconto acumulado em cada escala i.
        int* vetor_tempos;                                     //vetor para armazenar o tempo acumulado levado para se alcancar a escala i.
        int* vetor_custos;                                     //vetor para armazenar o custo c_i de cada estacao i.

    public:
        metro(int , int );                                     //construtor da classe.
        void insere_desconto_acumulado(int , double );         //metodo recebe o desconto da escala na posicao i e o armazena devidamente no vetor de descontos.
        void insere_tempo_acumulado(int , int );               //metodo recebe tempo individual de cada escala i e o acumula devidamente no vetor de tempos.
        void insere_preco(int, int );                          //metodo recebe o custo individual da escala i e o armazena no vetor de custos.
        void calcula_custo(int );                              //metodo computa o menor custo e o imprime. 
        double min(double , double );                          //retorna o menor dentre dois numeros.
        
};

#endif