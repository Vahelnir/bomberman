# Bomberman

Réalisé par HAMAYON VOISIN Valentin, PICHON Léo, MEGIA Antonin, GUTMAN Chloé et GUEURET Élodie.

**ATTENTION: Le jeu a principalement été testé sous Linux, si un quelconque bug est rencontré sous window, merci de le faire remarquer en ouvrant une issue sur le dépot.**

## Sommaire
 - [Description du projet](#description)
 - [Installation](#install)

## <a name="description"></a>Description
Pour notre projet, nous avons décider de recréer le jeu bomberman

Le but du jeu est d'être le dernier joueur en vie sur la carte.  
Le gagant est donc le dernier joueur en vie, ou sinon, en cas ou plusieurs joueur seraient encore en vie a la fin des 4 min, le gagnant sera celui avec le plus de point.
Pour cela chaque joueur doit éliminer les autres en posant des bombes sur la carte.
Notre jeu ce joueur en fonction du temps, et non en fonction du nombre de tours. Les IA devrons donc jouer en même temps.

### Les regles

Les règles sont simples. Ce sont celle d'un bomberman classique.

Sur notre carte, il y a 2 types de "bloc": des blocs fixes, qu'on ne peut pas casser, et des blocs qu'on peut casser.

Au début de la partie chaque joueur a 3 bombes. 
Il faut donc poser des bombes sur la carte pour pouvoir éliminer les autres joueur, et donc gagner.  A chaque fois qu'une bombe explose, il est possible de recouperez une autre bombe, à la place du bloc explosé.

Il y aura aussi la possibilité d'avoir des bonus et des malus dans une partie.


### Bonus et Malus

 1. Les bonus

- Accéleration : Dans une partie, les joueurs se déplacent tous a la même vitesse. Avec ce bonus, le joueur pourra se déplacer plus vite que les autres.
- Amelioration de la capacité de bombe ( + que 3): Les joueurs avec ce bonus ne seront pas obliger de se déplacer pour prendre une recharge de bombe, car il pourrons en avoir plus.
- Bouclier : ce bonus permet au joueur de rester en vie si il reçoit une bombe.
- Amelioration de la porte de la bombe : Chaque bombe "classique"  a la même portée sur la carte. Avec ce bonus cette porte pourra être plus grande et donc le joueur pourra avoir plus de chance de toucher les autres joueurs.
- Bonus de point

 2. Les Malus

- Deceleration : Le joueur se déplacera plus lentement que les autres.
- Reduction de la portée de la bombe
- Pose de bombe automatique : Pendant un certain temps, un bombe se posera a chaque pas fait par le joueur disposant de ce malus. Ce joueur aura donc plus de chance d'être touche par une bombe, donc de perdre.
- Malus de point

### Quelles sont les stratégies pour gagner ?

Il peut y avoir plusieurs stratégies pour gagner une partie

- Eliminer les adversaire en posant le plus de bombe possible, d'une manière stratégique .
- ramasser le plus de bonus possible, et essayer d'avoir le plus de points possible
- Ne rien faire et éviter le combat


## <a name="install"></a>Installation
Le programme a besoin de plusieures dépendances pour fonctionner :
 - CMake
 - PkgConfig: Permet de chercher des packages. 
 - GLM: Bibliothèque pour faciliter les calculs vectoriels et matriciels
 - GLFW3: Permet de créer/manager la fenetre ainsi que de récuperer le contexte OpenGL
 - Glad: Permet de charger les fonctions d'OpenGL que l'on va utiliser 
 - OpenGL: Permet de gerer l'affichage et l'utilisation de la carte graphique.
Glad doit être extrait à la racine du projet:
```
 Bomberman
 ├── glad
 │    └── include
 │       ├── glad
 │       └── KHR
 ├── src
 │   └── glad.c
 ├── src
 ├── images
 ├── include
 └── shaders
```

