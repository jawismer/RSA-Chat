#include "csapp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void encrypt(char* msg, int len, int e, int c, int* msgArray){
	int i=0;
	for(i=0; i<len; i++){
		//int charNum  = (int)*msg;
		//double power = pow(charNum, e);
		//int mod = (long long int)power % c;
		int a = (int)*msg;
		int eCopy = e;
		int cCopy = c;
		int mod = 1;
		while(eCopy){
                        if(eCopy % 2){mod = (mod * a) % cCopy;}
                        a = (a * a) % cCopy;
                        eCopy = eCopy/2;
                }
	
		msgArray[i] = mod;
		msg++;
	}
	msgArray[len] = -1;
}

int main(int argc, char* argv[]){
	char* host = argv[1];
	int port = atoi(argv[2]);
	int clientfd = Open_clientfd(host, port);
	rio_t rio;
	char buf[MAXLINE];
	char fullString[MAXLINE];
	int e = atoi(argv[3]);
	int c = atoi(argv[4]);
	char endString[MAXLINE];
	int* encMsg = (int*)malloc(100*sizeof(int));
	
	strcpy(fullString, "New message incoming\n");
	strcpy(endString, "End of message\n");
	
	Rio_readinitb(&rio, clientfd);

	while(1){
		char msg[MAXLINE];
		printf("\n\nEnter message to send: ");
		fgets(msg, MAXLINE, stdin);
		Rio_writen(clientfd, fullString, strlen(fullString));
		int len = strlen(msg);
		//printf("[Client] %s\n", msg);
		encrypt(msg, len, e, c, encMsg);
		printf("[Client] Encrypted message: ");
		int i = 0;
		for(i=0; i<len; i++){
			printf("%d ", encMsg[i]);
		}
		while(*encMsg != -1){
			sleep(1);
			char msgBuf[MAXLINE];
			sprintf(msgBuf, "%d\n", *encMsg);
			//printf("%s", msgBuf);
			Rio_writen(clientfd, msgBuf, strlen(msgBuf));
			encMsg++;
		}
		Rio_writen(clientfd, endString, strlen(endString));
	}
	printf("\n");

	close(clientfd);
	return 0;
}
