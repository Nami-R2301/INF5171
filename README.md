INF5171 - Programmation concurrente et parallèle
=====================================

Répertoire de ressources et d'exemples pour le cours INF5171.

## Accéder au contenu git

1. [Installez un client git](https://git-scm.com/)
2. Téléchargez une nouvelle copie du dépôt. Dans une console, exécutez:
    ```
    git clone git@gitlab.info.uqam.ca:inf5171/inf5171-scratchpad.git
    ```
3. Pour mettre à jour les exemples, exécutez:
    ```
    cd inf5171-scratchpad
    git pull
    ```
Tous les fichiers seront synchronisés à la version la plus récente.

## Compilation sous Ubuntu 22.04

Installer les paquets suivants:

```
sudo apt-get update
sudo apt-get install build-essential
sudo apt-get install cmake ninja-build
sudo apt-get install libtbb-dev libomp-dev
sudo apt-get install libopenmpi-dev openmpi-bin
```

## Compilation sous Mac OS 

- Installer xcode à partir du App Store 
- Installer [HomeBrew](https://brew.sh/index_fr)
- Installer les paquets suivants: 
```
xcode-select --install
brew install cmake
brew install ninja
brew install tbb
```

Notes :
- OSX ne supporte pas les sémaphores anonymes (`sem_init()` et `sem_destroy()`).
  Il faut utiliser les sémaphores nommés (`sem_open()` et `sem_close()`).

## Instructions de compilation

Dans QtCreator, simplement double-cliquer sur le fichier CMakeLists.txt à la racine du projet. Sélectionner le kit MinGW 64-bit sous Windows et le kit GCC sous Linux. Faire un `build` pour que le répertoire de compilation soit créé. 

Compilation en ligne de commande: 

```
# création d'un répertoire de compilation
mkdir build-debug
cd build-debug

# Configuration du projet, utilisation du générateur Ninja et du mode Debug, puis le chemin vers le répertoire des sources.
cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug ..

# compilation
ninja
```

Lorsque vous faites des bancs d'essai de performance, assurez-vous de configurer avec l'option `-DCMAKE_BUILD_TYPE=Release` ou pour le profilage `-DCMAKE_BUILD_TYPE=RelWithDebInfo`. Le mode debug est particulièrement lent à l'exécution et vous n'obtiendrez pas de bons résultats. Pour changer l'option, il suffit d'exécuter CMake avec la nouvelle valeur. Par exemple: 

```
cmake -DCMAKE_BUILD_TYPE=Release ..
```

## Licence

Le contenu de ce dépôt est couvert par la licence [Licence Creative Commons Attribution 4.0 International](http://creativecommons.org/licenses/by/4.0/).

<img alt="Licence Creative Commons" style="border-width:0" src="https://i.creativecommons.org/l/by/4.0/88x31.png"/>

Cependant, pour des fins académiques, on demande à ce que les solutions soient conservées dans un dépôt privé, pour que chaque étudiant ait la possibilité d'apprendre par soi-même. 
