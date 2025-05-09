/*
* FUNCAO : biblioteca para tratar pacote em formato intel HEX e gravar na RAM
* PROJETO: MIPS de Gabor na FPGA DE10nano
* DATA DE CRIACAO: 09/06/2022
*/

#ifndef TRATA_HEX_H
#define TRATA_HEX_H


#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "ram.h"

//DEFINES
#define MAX_BYTES        42
#define MAX_WORDS         4
#define TAMANHO_WORD      8
#define TAMANHO_BYTE      2
//# 
#define MAX_COMPRIMENTO   2
#define MAX_ENDERECO      4
#define MAX_TIPO          2
#define MAX_DADOS        32
#define MAX_CHECKSUM      2
//#
#define INIT_COMPRIMENTO  0
#define INIT_ENDERECO     2
#define INIT_TIPO         6
#define INIT_DADOS        8


//TIPOS LOCAIS
typedef struct
{
    unsigned int comprimento;
    unsigned int endereco;
    unsigned int tipo;
    unsigned int dados[MAX_WORDS];
    unsigned int checksum;
} linhaHEX;

//PROTOTIPACAO DAS FUNCOES:
/*
* Desempacota os dados de uma linha do arquivo HEX
*/
linhaHEX desempacotaLinha(char* linhaIn);

/*
* Testa se o checksum do pacote bate
*/
unsigned int calculaChecksum(char* linhaIn);


/*
* Converte um vetor de char em um inteiro sem sinal
*/
unsigned int converteVetorToInt(char* vetorIn, int comprimento, int inv);

/*
* Converte um de char em um inteiro sem sinal
*/
unsigned int converteASCIItoInt(char valorIn);

/*
* Converte um de inteiro de 8 bits em dois caracteres ASCII
*/
void converteInttoASCII(char* vetorOut, unsigned int valorIn, unsigned int nCaracteres);

/*
* fazendo na marra um funcao de pontencializacao, pq a pow() nao quer fucionar passando
* parametros
*/
unsigned int powInt(unsigned int x, unsigned int y);

/*
* Grava dados de uma linhaHex na memoria
*/
void  gravaLinha(unsigned int* ram_base_addr, linhaHEX linha);


#endif