Groupe 1 : BOUHENAF Irfan/Romain MOLINA

Merci d'avoir pris le temps de télécharger notre projet et de voir les résultats.
Dans le dossier, il y a :
- le fichier source contenant le programme en séquentiel nommé sujet7.cpp
- le fichier source contenant le programme en parallèle nommé sujet7_omp.cpp
- un fichier pdf contenant le compte-rendu du projet

Pour compiler le fichier sujet7.cpp sur Windows :

- Une fois dans votre invité de commande avec le chemin d'accès dans le bon fichier
faite la commande suivante : g++ -Wall -c sujet7.cpp
ensuite faites : g++ -Wall -o sujet7.exe sujet7.o 
et pour exécuter le fichier, faites : sujet7.exe $1 (le paramètre 1 c'est le nombre de valeurs qu'on veut tester)

Pour compiler le fichier sujet7.cpp sur Unix :

- Une fois dans votre invité de commande avec le chemin d'accès dans le bon fichier
faite la commande suivante : g++ -Wall sujet7.cpp -o sujet7
et pour exécuter le programmes, faites : ./sujet7 $1 (le paramètre 1 c'est le nombre de valeurs qu'on veut tester)

Pour compiler le fichier sujet7_omp.cpp sur Windows :

- Une fois dans votre invité de commande avec le chemin d'accès dans le bon fichier
faite la commande suivante : g++ -Wall -o sujet7_omp.exe -fopenmp sujet7_omp.cpp
et pour exécuter le fichier, faites : sujet7_omp.exe $1 $2 (le paramètre 1 c'est le nombre de valeurs qu'on veut tester, le paramètre 2 c'est le nombre de threads)

Pour compiler le fichier sujet7_omp.cpp sur Unix :

- Une fois dans votre invité de commande avec le chemin d'accès dans le bon fichier
faite la commande suivante : g++ -Wall -fopenmp sujet7_omp.cpp -o sujet7_omp
et pour exécuter le fichier, faites : ./sujet7_omp $1 $2 (le paramètre 1 c'est le nombre de valeurs qu'on veut tester, le paramètre 2 c'est le nombre de threads)


Merci d'avance !
