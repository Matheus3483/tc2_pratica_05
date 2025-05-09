/*
* FUNCAO : biblioteca escrever e ler da ONCHIP MEMORY RAM DUAL PORT criada dentro da FPGA
* PROJETO: MIPS de Gabor na FPGA DE10nano
* DATA DE CRIACAO: 10/06/2022
*/

#include "ram.h" 

/*
*  Le 32 bits da memoria de um endereco dado
*/
unsigned int read_ram(unsigned int *ram_addr)
{
    unsigned int dadoOut = 0;
    dadoOut = *(unsigned int *)(ram_addr);
}

//Prototipacao
/*
*  Escreve 32 bits na memoria de um endereco dado
*/
void write_ram(unsigned int *ram_addr, unsigned int dado)
{ 
    *(unsigned int *)(ram_addr)= dado; 
}
