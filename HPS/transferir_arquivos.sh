#!/bin/bash
PASTA_LOCAL="./pratica_05"
IP_DESTINO="root@10.42.0.102"
PASTA_DESTINO="pratica_05"
echo "Subindo Arquivos do Projeto - $PASTA_LOCAL:"
scp $PASTA_LOCAL/* $IP_DESTINO:/home/root/tc2_fpga_pds/$PASTA_DESTINO
echo "Subindo Bibliotecas comuns a todos os projetos:"
scp ./INC/* $IP_DESTINO:/home/root/INC


