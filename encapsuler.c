#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FDU.h"
#include "ip.h"

#define PC_IP "172.0.0.1"
#define BROADCAST_IP "172.0.0.255"
#define PC1_PORT 8000
#define PC2_PORT 8001
#define PC3_PORT 8002
#define PC4_PORT 8003
#define BROADCAST_PORT 8004

#define PC1 (IP){PC_IP, PC1_PORT}
#define PC2 (IP){PC_IP, PC2_PORT}
#define PC3 (IP){PC_IP, PC3_PORT}
#define PC4 (IP){PC_IP, PC4_PORT}

void demander_message(FDU* paquet) {
    char choix;
    char message[100];
    char PC[10];

    printf("Voulez-vous envoyer un message ? (y/n) : ");
    scanf(" %c", &choix);
    if (choix == 'y') {
    printf("Entrez le message : ");
    scanf("%s", message);
    strcpy(paquet->message, message);
    printf("Vous envoyez le message à PC1, PC2, PC3, PC4 ou ALL : ");
    scanf("%s", PC);

    if (strcmp(PC, "PC1") == 0) {
        paquet->ip_destination = PC1;
    } else if (strcmp(PC, "PC2") == 0) {
        paquet->ip_destination = PC2;
    } else if (strcmp(PC, "PC3") == 0) {
        paquet->ip_destination = PC3;
    } else if (strcmp(PC, "PC4") == 0) {
        paquet->ip_destination = PC4;
    } else if (strcmp(PC, "ALL") == 0) {
        paquet->ip_destination.port = BROADCAST_PORT;  
    }
    }else {
        printf(".*.*.*.\n");
    }

}
void encapsuler(FDU* paquet, IP ip_courant) {
    paquet->ip_source = ip_courant;

    int tour = paquet->socket_st %4; // 4 est le nombre de PC dans l'anneau
    
    if (tour  == 0 && ip_compare(PC1, ip_courant)) {
        demander_message(paquet);
        paquet->status = 1; // message envoyé
    } else if (tour == 1 && ip_compare(PC2, ip_courant)) {
        demander_message(paquet);
        paquet->status = 1; // message envoyé
    } else if (tour == 2 && ip_compare(PC3, ip_courant)) {
        demander_message(paquet);
        paquet->status = 1; // message envoyé
    } else if (tour == 3 && ip_compare(PC4, ip_courant)) {
        demander_message(paquet);
        paquet->status = 1; // message envoyé
    } 
}

// test de la fonction encapsuler


/*
int main() {
    //test
    FDU paquet;
    IP ip_courant = PC1;
    IP ip_destination = PC2;
    paquet.socket_st = 0; // initialisation de socket_st
    paquet.ip_destination = ip_destination;
    paquet.status = 0; // initialisation de status
    strcpy(paquet.message, "Salut");

    encapsuler(&paquet, ip_courant);
    printf("Message : %s\n", paquet.message);
    printf("IP source : %s:%d\n", paquet.ip_source.nom, paquet.ip_source.port);
    printf("IP destination : %s:%d\n", paquet.ip_destination.nom, paquet.ip_destination.port);
    printf("Socket state : %d\n", paquet.socket_st);
    printf("Status : %d\n", paquet.status);
    return 0;
}

*/
