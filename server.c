#include "csapp.h"
#include <stdio.h>
#include <math.h>

void decrypt(int* encMsg, int len, int d, int c, char* decMsg){
	int i = 0;
	for(i=0; i<len; i++){
		int a = *encMsg;
		int dCopy = d;
		int cCopy = c;
		int mod = 1;
		while(dCopy){
			if(dCopy % 2){mod = (mod * a) % cCopy;}
			a = (a * a) % cCopy;
			dCopy = dCopy/2;
		}
		*decMsg = (char)mod;
		decMsg++;
		encMsg++;
	}
}

int main(int argc, char* argv[]){
	int port = atoi(argv[1]);
	int listenfd = Open_listenfd(port);
	struct sockaddr_in clientaddr;
	int clientaddrlen = sizeof(clientaddr);
	int connfd;
	rio_t rio;
	int n;
	char buf[MAXLINE];
	int msgArray[100];
	int* msgPtr = msgArray;
	int flag = 0;
	char* decMsg = (char*)malloc(100*sizeof(char));
	int msgCount = 0;
	int d = atoi(argv[4]);
	int c = atoi(argv[3]);

	while(1){
		connfd = Accept(listenfd, (SA*)&clientaddr, &clientaddrlen);
		
		Rio_readinitb(&rio, connfd);
		while((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0){
			//printf("Client: %s", buf);
			if((int)buf[0]-'0' >= 0 && (int)buf[0]-'0' <= 9){
				*msgPtr = atoi(buf);
				msgPtr++;
				flag = 1;
				msgCount++;
			}else{
				if(flag == 1){
					msgPtr = msgArray;
					char* decPtr = decMsg;
					//printf("[Client] Encrypted message: %s\n", msgPtr);
					decrypt(msgPtr, msgCount, d, c, decPtr);
					printf("[Client] Encrypted message: ");
					int i = 0;
					for(i=0; i<msgCount; i++){
						printf("%d ", msgPtr[i]);
					}
					printf("\n[Client] Decrypted message: %s\n", decMsg);
					flag = 0;
					msgPtr = msgArray;
					msgCount = 0;
				}
			}
		}
		close(connfd);
	}
	close(listenfd);
	return 0;
}
