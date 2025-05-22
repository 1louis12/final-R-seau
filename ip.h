#pragma once
// definir la structure IP
typedef struct {
    char nom[16]; // "127.0.0.1"
    int port;
} IP;

int ip_compare(IP ip1, IP ip2);
