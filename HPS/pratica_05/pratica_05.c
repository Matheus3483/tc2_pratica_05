/*
* FUNCAO : Testa a RAM do periferico 
* PROJETO: Finite Field 256 Cosine Transforms
* DATA DE CRIACAO: 27/08/2024
*/


//Do codigo basico
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "hwlib.h"
#include "socal.h"
#include "hps.h"
#include "alt_gpio.h"
#include "hps_0.h"

//do codigo de Breno
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <time.h> 
#include <math.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <unistd.h>

//Feitas por mim
#include "trataHEX.h"
#include "ram.h"
#include "peripheral.h"

#define PORT_1_MEM_BASE 0x40000
#define PORT_1_ADDR_SPAN 4
#define PORT_1_MEM_SPAN PORT_1_ADDR_SPAN*32

//UDP
#define N 		64
#define N_PACKET 8
#define N_BUF 8

int main() 
{
	//Codigo UDP:
	uint8_t A, B, Y, en = 1, addr;
	uint8_t nCaracteres = 3;
	int sock, length, n, flags;
	socklen_t fromlen;
	struct sockaddr_in server;
	struct sockaddr_in from;
	char buf[N_BUF];
	

	uint32_t i;        //para iteracoes
	uint32_t entrada;        //para iteracoes
	uint32_t mem_read;
	uint32_t mem_read_lsw;
	uint32_t mem_read_msw;
	uint32_t mem_write;
	uint8_t mem_write8;
	uint16_t mem_write16;
	uint16_t mem_read16;
	uint8_t  mem_read8;
	peripheral dualPortRam;


	sock=socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0) printf("Opening socket");

	length = sizeof(server);
	bzero(&server,length);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(9090);
	if (bind(sock,(struct sockaddr *)&server,length)<0) 
		printf("binding");
	fromlen = sizeof(struct sockaddr_in);
	//



	printf("*---------------------------------------------------------------------\n");
	printf("* FUNCTION       : PRATICA 04\n");
	printf("* PROJECT        : TC2 - FPGA\n");
	printf("* DATE           : 04/04/2025\n");
	printf("*---------------------------------------------------------------------\n");


	printf("defining the access to the memory peripherals\n");
	dualPortRam = peripheral_create(PORT_1_MEM_BASE, PORT_1_MEM_SPAN);
	//port02 = peripheral_create(PORT_2_MEM_BASE, PORT_2_MEM_SPAN);

	while(1)
	{
		printf("Aguardando pacote do PC...\n");
		bzero(buf,N_BUF);
	   	n = recvfrom(sock,buf,N_BUF,0,(struct sockaddr *)&from,&fromlen);
	   	if (n < 0) printf("recvfrom");
	   	else
	   	{
			printf("Esperando um tempo\n");
			usleep(1000); //Esperando um tempo para ver se o python espera a mensagem;
			
			// checar entradas de buf (pula esse passo)
			A = converteASCIItoInt(buf[0])*10 + converteASCIItoInt(buf[1]);
			B = converteASCIItoInt(buf[2])*10 + converteASCIItoInt(buf[3]);
			//entrada = converteASCIItoInt(buf[4]);
			
			//if (entrada)
			//{
			usleep(100);
			printf("writing in the memory \n");
				
			// escreve na memoria os valores de A e B em binário
			addr = 1;
			mem_write &= 0x0000;
			mem_write |= (A & 0x0F);
			mem_write |= (B << 4);
			printf("Endereco: %X, Valor: %X\n", 4*addr, mem_write);
			peripheral_write32(dualPortRam,addr,mem_write);

			en = 1; // control
			addr = 0;
			mem_write &= 0x0000;
			mem_write |= en;
			printf("Endereco: %X, Valor: %X\n", 4*addr, mem_write);
			peripheral_write32(dualPortRam,addr,mem_write);

			//}
			// observar bit de finalização
			// ler na memoria o valor Y

			usleep(1000);
			printf("Reading the RAM:\n");
			//for(i = 0; i < PORT_1_ADDR_SPAN; i++) // *CHECAR O ENDEREÇO*
			//{
			//	usleep(100);
			//	mem_read =  peripheral_read32(dualPortRam,i);
			//	printf("Endereco: %X, Valor: %X\n", 4*i, mem_read);
			//	
			//}
			addr = 3;
			mem_read =  peripheral_read32(dualPortRam, addr);
			printf("Endereco: %X, Valor: %X\n", 4*addr, mem_read);
			while(!mem_read)
			{
				usleep(1000);
				mem_read =  peripheral_read32(dualPortRam, addr);
				printf("Endereco: %X, Valor: %X\n", 4*addr, mem_read);
			}

			addr = 2;
			mem_read =  peripheral_read32(dualPortRam,addr);
			printf("Endereco: %X, Valor: %X\n", 4*addr, mem_read);

			// en = 0; // control
			addr = 0;
			mem_write &= 0x0000;
			//mem_write |= en;
			printf("Endereco: %X, Valor: %X\n", 4*addr, mem_write);
			peripheral_write32(dualPortRam,addr,mem_write);

			//
			Y = mem_read;
			//
			//// Y = A*B;
			converteInttoASCII(buf, Y, nCaracteres);
			printf("Devolvendo resultado:\n");
			n = sendto(sock,buf,N_BUF,0,(struct sockaddr *)&from,fromlen);
			if (n  < 0) printf("sendto");						
		}
	}	
}
