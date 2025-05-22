all: pc1 pc2 pc3 pc4

pc1: pc1.c decapsuler.c encapsuler.c ip.c
	$(CC) -Wall -o $@ $^

pc2: pc2.c decapsuler.c encapsuler.c ip.c 
	$(CC) -Wall -o $@ $^

pc3: pc3.c decapsuler.c encapsuler.c ip.c
	$(CC) -Wall -o $@ $^

pc4: pc4.c decapsuler.c encapsuler.c ip.c
	$(CC) -Wall -o $@ $^
	