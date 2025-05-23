
// Formation de la couche basse de l'anneau (emulation couche physique)
// Chaque PC muni de 2 sockets :
// -> 1 oreille : socket serveur pour recevoir du PC precedent
// -> 1 bouche : socket client pour envoyer vers le PC suivant 
// Tous les PCs sur la boucle locale => diff�rencies que pas leur port serveur

Compilation :
> make 

Lancement (dans 3 terminaux differents):
> ./pc4
> ./pc3
> ./pc2
> ./pc1 

