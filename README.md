# Test de primalité de Fermat et de Miller-Rabin
Implémentation en C , en utilisant la librairie GMP , deux tests de primalité trés populaires :
- **Le test de Fermat**  et le **test de Miller-Rabin**

### prérequis 
Afin de pouvoir compilé ces deux Tests , il faut au préalable avoir installé la bibliothèque **GNU MP** .


### Installation de GMP:
* Récupérer l'archive de [GMP](https://gmplib.org/#DOWNLOAD) 
* Extraire le contenu de l'archive
* Compiler la bibliothèque
```
./configure
make
```
```
make check
```
```
sudo make install 
```
Vous pouvez trouver le manuel d'utilisation [ici .](https://gmplib.org/gmp-man-6.2.0.pdf)


### Complitaion 
pour executer le fichier **Fermat.c** vous devez taper sur le Terminale la commande :
```
gcc -Wall -o Fermat Fermat.c -lgmp 
```
Pour Executer taper :
```
./Fermat

```
Pour executer le fichier **millerrabin.c** sur le Terminale Taper :
```
gcc -Wall -o MR millerrabin.c -lgmp 
```
Pour Executer taper :
```
./MR
```



