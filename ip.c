#include <string.h>
#include "ip.h"

//return 1 if ip1 and ip2 are the same, 0 otherwise

int ip_compare(IP ip1, IP ip2) {
    if (strcmp(ip1.nom, ip2.nom)  && ip1.port == ip2.port) {
        return 1;
    }
    return 0;
}
