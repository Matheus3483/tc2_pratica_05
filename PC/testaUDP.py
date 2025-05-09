#OBJETIVO: Abrir um socket UDP escrever uma mensagem e esperar resposta
#PROJETO:  FINITE FIELD GF256 COSINE TRANSFORMS
#DATA DE CRIACAO: 28/08/2024 
import socket
import numpy


msgFromClient       = "0000"
bytesToSend         = str.encode(msgFromClient)
serverAddressPort   = ("10.42.0.102", 9090) 
bufferSize          = len(bytesToSend)

flag = 1
 

# Create a UDP socket at client side
UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

print("ATENÇÃO! ENVIANDO PACOTE PARA A PORTA -",serverAddressPort)

entrada = 1
en = str(entrada)
for a in range(0x0F+1):
    for b in range(0x0F+1):
        A = str(a)
        B = str(b)
        if len(A) == 1: A = '0' + A
        if len(B) == 1: B = '0' + B
        msgFromClient = A + B
        bytesToSend   = str.encode(msgFromClient)

        print("Mensagem  a ser enviada:", msgFromClient)

        #print("Enviando a mensagem pelo socket criado")
        UDPClientSocket.sendto(bytesToSend, serverAddressPort)


        #print("Esperando receber algo:")
        msgFromServer = UDPClientSocket.recvfrom(bufferSize)

        Y = msgFromServer[0] #.decode(encoding='utf-8', errors='strict')
        #print("Mensagem recebida:")
        msg = "Message from Server {}".format(Y)
        print(msg)
        

        y = int(Y[0:2],base=16)
        print(y)
        if y == a*b:
            print('OK!')
        else:
            print('Not OK!')
            flag = 0

if flag:
    print('Tudo ok!')
else:
    print('Contém erro!')
