/*
* FUNCAO : biblioteca para tratar pacote em formato intel HEX e gravar na RAM
* PROJETO: MIPS de Gabor na FPGA DE10nano
* DATA DE CRIACAO: 09/06/2022
*/

#include "trataHEX.h"

/*
* Desempacota os dados de uma linha do arquivo HEX
*/
linhaHEX desempacotaLinha(char* linhaIn)
{
    unsigned int i; 
    unsigned int numWords; 
    unsigned int initChecksum; 

    linhaHEX linhaOut;
    char comprimento[MAX_COMPRIMENTO];                     //Numero de bytes de dados
    char endereco[MAX_ENDERECO];                           //Endereco inicial de gravacao
    char tipo[MAX_TIPO];                                   //Tipo de pacote: 00 = Dados 01 = EoF
    char dados[MAX_DADOS] = {'0','0','0','0'};             //Dados a serem gravados da memoria
    char checksum[MAX_CHECKSUM];       //cheksum
    
    for(i = 0; i < MAX_COMPRIMENTO; i++)
    {
        comprimento[i] = linhaIn[INIT_COMPRIMENTO+i];
        tipo[i]        = linhaIn[INIT_TIPO       +i];    
    }

    for(i = 0; i < MAX_ENDERECO; i++)
    {
        endereco[i] = linhaIn[INIT_ENDERECO+i];
    }
    
    linhaOut.comprimento = converteVetorToInt(comprimento,MAX_COMPRIMENTO,1);
    linhaOut.tipo        = converteVetorToInt(tipo       ,MAX_COMPRIMENTO,1);
    linhaOut.endereco    = converteVetorToInt(endereco   ,MAX_ENDERECO,1);

    if(linhaOut.comprimento > 0)//tem dados
    {
        for(i = 0; i < (linhaOut.comprimento*2); i++) //copia todos os dados (cada numero ocupa 2 espacos)
        {
            dados[i] = linhaIn[INIT_DADOS+i];
        }
        numWords = linhaOut.comprimento/4;            //quantas palavras de 32 bits temos
        for(i = 0; i < numWords; i++)
        {
            linhaOut.dados[i] = converteVetorToInt( (dados + TAMANHO_WORD*i), TAMANHO_WORD, 1);
        }

    }

    initChecksum  = (linhaOut.comprimento*2) + INIT_DADOS;
    for(i = 0; i < MAX_ENDERECO; i++)
    {
        checksum[i] = linhaIn[initChecksum+i];
    }
    linhaOut.checksum  = converteVetorToInt(checksum   ,MAX_CHECKSUM, 1);    

    return(linhaOut);
}


/*
* Testa se o checksum do pacote bate
*/
unsigned int calculaChecksum(char* linhaIn)
{
    unsigned int i; 
    unsigned int numWords; 
    unsigned int numComprimento; 
    unsigned int initChecksum; 
    unsigned int valorChecksum = 0; 

    char comprimento[MAX_COMPRIMENTO]; //Numero de bytes de dados
    unsigned int linha[MAX_BYTES/2];   //Endereco inicial de gravacao

    
    for(i = 0; i < MAX_COMPRIMENTO; i++)
    {
        comprimento[i] = linhaIn[INIT_COMPRIMENTO+i];
    }
    
    numComprimento = converteVetorToInt(comprimento,MAX_COMPRIMENTO,1);

    for(i = 0; i < MAX_BYTES/2; i++)
    {
        linha[i] = converteVetorToInt( (linhaIn + TAMANHO_BYTE*i), TAMANHO_BYTE,1);
    }

    initChecksum  = numComprimento + INIT_DADOS/2;
    for(i = 0; i < initChecksum; i++)
    {
        valorChecksum += linha[i];
        
    }
    valorChecksum &= 0xFF;
    valorChecksum ^= 0xFF;
    valorChecksum += 0x01;
    //printf("Checksum: %X\n",linha[initChecksum]);
    if(linha[initChecksum] == valorChecksum)
    {
        return(1);
    }
    else
    {
        return(0);
    }
}


/*
* Converte um vetor de char em um inteiro sem sinal
*/
unsigned int converteVetorToInt(char* vetorIn, int comprimento, int inv)
{
    unsigned int i;
    unsigned int valorOut = 0; 
    unsigned int valorAux = 0; 
    if(inv)
    {
        for(i = 0; i < comprimento; i++)
        {
        
            valorOut += converteASCIItoInt(vetorIn[comprimento-i-1]) << 4*i;
        }
        
    }
    else
    {
        for(i = 0; i < comprimento/2; i++)
        {
            valorAux = converteASCIItoInt(vetorIn[2*i+0]) << 4;
            valorAux += converteASCIItoInt(vetorIn[2*i+1]);
            valorOut += valorAux << 8*i;
        }
    }
    
    return(valorOut);
}  

/*
* Converte um char em um inteiro sem sinal
*/
unsigned int converteASCIItoInt(char valorIn)
{
    unsigned int valorOut = 0;
    unsigned int valorAscii = valorIn;
    if((valorAscii >= 0x30)&&(valorAscii <= 0x39))
    {
        valorOut = valorAscii - 0x30;
    }

    if((valorAscii >= 0x41)&&(valorAscii <= 0x46))
    {
        valorOut = valorAscii - 0x41 + 0x0A;
    }
    
    if((valorAscii >= 0x61)&&(valorAscii <= 0x66))
    {
        valorOut = valorAscii - 0x61 + 0x0A;
    }
    return(valorOut);
}


/*
* Converte um de inteiro em ASCII
*/
void converteInttoASCII(char* vetorOut, unsigned int valorIn, unsigned int nCaracteres)
{
    int i;
    unsigned int valorByte;
    for(i = 0; i < nCaracteres; i++)
    {
        valorByte =  0xFF & (valorIn >> 8*i);
        if( (0x0F & valorByte) < 0x0A)
        {
            vetorOut[1+2*i] = (0x0F & valorByte) + '0';
        } 
        else 
        {
            vetorOut[1+2*i] = (0x0F & valorByte) + 'a' - 10;
        }

        if( (0x0F & (valorByte >> 4)) < 0x0A)
        {
            vetorOut[0+2*i] = (0x0F & (valorByte >> 4)) + '0';
        } 
        else 
        {
            vetorOut[0+2*i] = (0x0F & (valorByte >> 4)) + 'a' - 10;
        }
    }
}

/*
* fazendo na marra um funcao de pontencializacao, pq a pow() nao quer fucionar passando
* parametros
*/
unsigned int powInt(unsigned int x, unsigned int y)
{
    unsigned int resultado = 1;
    unsigned int i;
    for(i = 0; i < y; i++)
    {
        resultado *= x;
    }
    return resultado;
}

/*
* Grava dados de uma linhaHex na memoria
*/
void  gravaLinha(unsigned int* ram_base_addr, linhaHEX linha)
{
    unsigned int i;
    unsigned int tamanho = linha.comprimento/4;
    if(tamanho%4)
    {
        tamanho++;
    }
    for(i = 0; i < tamanho; i++)
    {
        write_ram((unsigned int *)(ram_base_addr + (linha.endereco >> 2) + i),linha.dados[i]);
    }

}
