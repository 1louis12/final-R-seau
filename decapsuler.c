#include "FDU.h"
#include "ip.h"
#include <stdio.h>
#include <string.h>

#define PC_IP "172.0.0.1"
#define BROADCAST_PORT 8004
#define IP_broadcast ((IP){PC_IP, BROADCAST_PORT})



void decapsuler(FDU* paquet, IP ip_courant){
    // test destinateur
    if (paquet->status == 0) {
        // Aucun message n'est encore envoyé
        printf(".*.*.*.*\n");
        // passer le paquet au suivant
    } else {
        if (ip_compare(paquet->ip_source, ip_courant) == 1 ) {
        //le message à fait un tour complet
        printf("#####\n");
        printf("destinataire non trouvé\n");
        printf("Contenu : %s\n", paquet->message);
        paquet->status = 0; 
        printf("@@@@@\n");

        } else if (ip_compare(paquet->ip_destination, ip_courant) == 1 ) {
        printf("#####\n");
        printf("Nouveau message\n");
        printf("contenu: %s\n", paquet->message);
        printf("@@@@@\n");
        }

        if (paquet->status == 1) {
        if (ip_compare(paquet->ip_destination, IP_broadcast) == 1) {
            printf("#####\n");
            printf("Nouveau message\n");
            printf("contenu: %s\n", paquet->message);
            printf("@@@@@\n");
            if (ip_compare(paquet->ip_source, ip_courant) == 1) {
                paquet->status = 0; // tout le monde a reçu le message
            }
        } else {
            printf(".*.*.*.\n");
        }
    }
}
}

/*

int main() {
    FDU paquet;
    IP ip_courant = { PC_IP, 8001 }; // Adresse IP courante
    // Initialiser le paquet
    strcpy(paquet.message, "Bonjour");
    paquet.ip_source = ip_courant;
    paquet.ip_destination = (IP){ PC_IP,  8000 }; // Adresse IP de destination
    paquet.status = 1; // Message envoyé
    paquet.socket_st = 0; // État du socket
    // Appeler la fonction decapsuler
    decapsuler(&paquet, (IP){ PC_IP,  8000 });
    return 0;
}

*/



