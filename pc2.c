#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "FDU.h"
#include "ip.h"
#include "encapsuler.h"
#include "decapsuler.h"

#define IP_addr_PC "127.0.0.1" // Adresse IP des PCs

#define port_S_courant 8001 // Port serveur courant (oreille courante)
#define port_S_suivant 8002 // Port serveur suivant (oreille suivante)

#define Port_broadcast 8004 // Port de broadcast

#define IP_courant (IP){IP_addr_PC , port_S_courant}
#define IP_suivant (IP){IP_addr_PC, port_S_suivant}
#define IP_courabt (IP){IP_addr_PC, Port_broadcast}



int main()
{
    IP ip_courant;
    ip_courant.port = port_S_courant;
    strcpy(ip_courant.nom, IP_addr_PC);

    int sock_C, sock_S;
    struct sockaddr_in sa_S_courant, sa_S_suivant, sa_S_precedent;
    unsigned int taille_sa;

    FDU paquet;
    paquet.ip_source = IP_courant;
    paquet.ip_destination = IP_suivant;
    paquet.status = 0;
    paquet.socket_st = 0;
    strcpy(paquet.message, "Salut");

    int nb_boucle = 1;

    taille_sa = sizeof(struct sockaddr);

    // Création de l'oreille (socket serveur courant)
    sock_S = socket(PF_INET, SOCK_DGRAM, 0);
    perror("socket ");

    bzero((char *) &sa_S_courant, sizeof(struct sockaddr_in));
    sa_S_courant.sin_family = AF_INET;
    sa_S_courant.sin_addr.s_addr = inet_addr(IP_addr_PC);
    sa_S_courant.sin_port = htons(port_S_courant); 

    bind(sock_S, (struct sockaddr *) &sa_S_courant, sizeof(struct sockaddr));
    perror("bind ");

    // Creation de la bouche (parle au serveur suivant)
    sock_C = socket(PF_INET, SOCK_DGRAM, 0);
    perror("socket");

    bzero((char *) &sa_S_suivant, sizeof(struct sockaddr_in));
    sa_S_suivant.sin_family = AF_INET;
    sa_S_suivant.sin_addr.s_addr = inet_addr(IP_addr_PC);
    sa_S_suivant.sin_port = htons(port_S_suivant);


    if ( (port_S_courant == 8000) && (nb_boucle == 1) ) {
        encapsuler(&paquet, ip_courant);
		sendto(sock_S, &paquet, sizeof(FDU), 0, (struct sockaddr *)&sa_S_suivant, sizeof(sa_S_suivant));
		nb_boucle--; 
	}
    // Pas d'amorce ici pour pc4

    while(1)
    {
        // Reception sur Oreille courante
        recvfrom(sock_S, &paquet, sizeof(FDU), 0, (struct sockaddr *)&sa_S_precedent, &taille_sa);

        // Traitement
        decapsuler(&paquet, ip_courant);
        encapsuler(&paquet, ip_courant);
        sleep(1);

        // Envoi vers PC suivant 
        sendto(sock_S, &paquet, sizeof(FDU), 0, (struct sockaddr *)&sa_S_suivant, sizeof(sa_S_suivant));
    }

    close(sock_S);
    close(sock_C);
    exit(EXIT_SUCCESS);
}