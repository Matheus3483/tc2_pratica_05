/*
* FUNCAO : biblioteca escrever e ler da ONCHIP MEMORY RAM DUAL PORT criada dentro da FPGA
* PROJETO: MIPS de Gabor na FPGA DE10nano
* DATA DE CRIACAO: 10/06/2022
*/

#ifndef RAM_H
#define RAM_H


//DEFINES
//Memoria ON CHIP MEMORY (RAM)
#define OC_MEM_BASE 0x40000
#define OC_MEM_END  0x7FFFF

//Prototipacao
/*
*  Le 32 bits da memoria de um endereco dado
*/
unsigned int read_ram(unsigned int *ram_addr);

//Prototipacao
/*
*  Escreve 32 bits na memoria de um endereco dado
*/
void write_ram(unsigned int *ram_addr, unsigned int dado);

#endif