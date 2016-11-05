genkey:
	gcc genkey.c -o genkey.out -lm
	./genkey.out $(MPRIME) $(NPRIME)

keycrack:
	gcc keycrack.c -o keycrack.out -lm
	./keycrack.out $(E) $(C)

server:
	gcc -pthread server.c csapp.c -o server.out -lm -g
	./server.out $(PORT) $(E) $(C) $(D) $(DC)

client:
	gcc -pthread client.c csapp.c -o client.out -lm -g
	./client.out $(SERVER) $(PORT) $(E) $(C) $(D) $(DC)

clean:
	rm *.out
