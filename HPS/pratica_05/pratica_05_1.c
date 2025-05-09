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

#define PORT_1_MEM_BASE 0x40020
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
	

	uint32_t i;        		 //para iteracoes
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
	printf("* FUNCTION       : PRATICA 05\n");
	printf("* PROJECT        : TC2 - FPGA\n");
	printf("* DATE           : 09/05/2025\n");
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
			
			A = converteASCIItoInt(buf[0])*10 + converteASCIItoInt(buf[1]);
			B = converteASCIItoInt(buf[2])*10 + converteASCIItoInt(buf[3]);
			printf("Valores recebidos: A=%X B=%X\n", A, B);


			usleep(100);
			printf("writing in the memory \n");
				
			// escreve na memoria os valores de A e B em binário
			addr = 1;
			mem_write8 &= 0x00;
			mem_write8 |= (A & 0x0F);
			mem_write8 |= (B << 4);
			printf("Write: Endereco: %X, Valor: %X\n", addr, mem_write8);
			peripheral_write8(dualPortRam,addr,mem_write8);
			mem_read8 =  peripheral_read32(dualPortRam, 0);
			printf("Read: Endereco: %X, Valor: %X\n", addr, mem_read8);
		

			addr = 0;
			mem_write8 = 0x01; // control
			printf("Write: Endereco: %X, Valor: %X\n", addr, mem_write8);
			peripheral_write8(dualPortRam,addr,mem_write8);
			mem_read8 =  peripheral_read32(dualPortRam, 0);
			printf("Read: Endereco: %X, Valor: %X\n", 0, mem_read8);


			usleep(1000);
			printf("Reading the RAM:\n");

			addr = 3;
			mem_read8 =  peripheral_read8(dualPortRam, addr);
			printf("Read: Endereco: %X, Valor: %X\n", addr, mem_read8);
			while(!mem_read8)
			{
				usleep(1000);
				mem_read8 =  peripheral_read8(dualPortRam, addr);
				printf("Endereco: %X, Valor: %X\n", addr, mem_read8);
			}

			addr = 2;
			mem_read8 =  peripheral_read8(dualPortRam,addr);
			printf("Read: Endereco: %X, Valor: %X\n", addr, mem_read8);

			addr = 0;
			mem_write8 = 0x00; // control
			printf("Read: Endereco: %X, Valor: %X\n", addr, mem_write8);
			peripheral_write8(dualPortRam,addr,mem_write8);


			Y = mem_read8;
			converteInttoASCII(buf, Y, nCaracteres);
			printf("Devolvendo resultado: Y=%X\n",Y);

			n = sendto(sock,buf,N_BUF,0,(struct sockaddr *)&from,fromlen);
			if (n  < 0) printf("sendto");						
		}
	}	
}
