#pragma once
#include "ip.h"
// la priorité est équilibré pour n PC dans l'anneau on a n-1 état de socket_st pour soket state
// elle est initialié à 0 pour dire que le pC1 peut envoyer le message donc O modulo n pour le PC1
// 1 modulo n pour le PC2 et ainsi de suite
// 2 modulo n pour le PC3 et ainsi de suite
// 3 modulo n pour le PC4 et ainsi de suite

// socket_st est incrémenter de 1 a chaque tour complet de l'anneau
// si j'envoie à mon tour je dois incrémenter le socket_st de 1


typedef struct FDU {
    IP ip_source;
    IP ip_destination;
    char message[100];
    int socket_st; // peut on envoyer le message
    int status; // etat du message
} FDU;