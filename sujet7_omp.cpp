#include <iostream>
#include <fstream>
#include <chrono>
#include <cmath>
#include <string>
#include <omp.h>

//Programme fait par Irfan BOUHENAF et Romain MOLINA

//fonction permettant de rechercher les nombres premiers
void calcul(int max, bool * tab, char ** nbthread) 
{    
    //0 et 1 ne sont pas des nombres premiers, on ne peut pas tester ces valeurs car pas assez de diviseurs
    tab[0] = false;
    tab[1] = false;
    //création d'une section du programme parallélisable, argument : nombre de threads
    #pragma omp parallel num_threads(atoi(nbthread[2]))
    {
        //Création d'un section de parralélisation pour boucle for à l'aide de pragma
        //ici, on remplit le tableau dynamique avec des valeur booléenes
        #pragma omp for
        for (int i = 2; i<=max; ++i)
        {
            //si i est pair et est différent de 2
            if ((i%2 == 0) && (i!=2)) 
                tab[i] = false;
            else
                tab[i] = true;         
        }
           
        //Avec la clause schedule(dynamic), dès qu'un thread a terminé son lot de données, il peut reprendre un lot de données à traiter.
        //on cherche la plupart des diviseurs (j) d'un nombre (i)
        #pragma omp for schedule(dynamic)
        for (int i = 2; i <= max; i++)
        {
            //si j=2 alors j=j+1 sinon j=j+2 car un nombre pair est toujours divisible par 2 contrairement au nombre impairs
            //condition : j<=racine carré de i et i est premier, si une des condition n'est pas remplie, on sort de la boucle
            for (int j = 2; j <= sqrt(i) && tab[i]; j += ( j == 2) ? 1:2)
            {   
                //i divisible par j ?
                if (i%j == 0)
                    tab[i] = false;  
            } 
        } 
        //barrière de synchronisation
        #pragma omp barrier  
    }  
    
    
}

//fonction qui écrit les nombres premier dans un fichier
void ecriture_fichier(int max, bool * tab)
{
    //création d'un fichier premier.txt
    std::ofstream fichier("premier.txt");
    for (int i = 0; i <= max; i++)  
    {
        //écriture des nombre premiers dans le fichier texte
        //si le nombre est premier
        if (tab[i])
        {
            fichier << i << std::endl;
        }
    }
}

//fonction qui compte les nombres premiers
int nombre_premiers (int max, bool * tab)
{
    int compteur = 0;
    for (int i = 0; i <= max; i++)  
    {
        if (tab[i])
            compteur++;
    }
    return compteur;
}

//fonction permettant de tester les paramètres de la ligne de commande
void test_param(int nombre, char ** contenu)
{
    //le nom du fichier exécutable est compté comme un paramètre, c'est le paramètre 0
    //première paramètre = le nombre de valeurs qu'on veut tester, deuxième paramètre = nombre de threads
    int param1 = atoi(contenu[1]);
    int nbthread = atoi(contenu[2]);

    if (nombre !=3)
        throw std::runtime_error("Nombre de parametres invalides");
    if (param1 < 2)
        throw std::runtime_error("Impossible de trouver un nombre premier");
    if (nbthread < 1)
        throw std::runtime_error("Nombre de threads invalide");
}

int main(int argc, char ** argv)
{
    test_param(argc,argv);
    //c'est un tableau dynamique car il possède plus de cases qu'un tableau statique
    //la fonction atoi permet de convertir une varialble de type char * en int
    bool * estPremier = new bool[atoi(argv[1])+1]; 
    //début du chronomètre 
    std::chrono::time_point<std::chrono::system_clock> debut = std::chrono::system_clock::now();
    calcul(atoi(argv[1]),estPremier,argv);
    ecriture_fichier(atoi(argv[1]),estPremier);
    //fin du chronomètre 
    std::chrono::time_point<std::chrono::system_clock> fin = std::chrono::system_clock::now();
    std::chrono::duration<double> temps = fin - debut;
    std::cout << "Nombre de threads : " << atoi(argv[2]) << std::endl;
    std::cout << temps.count() << " secondes" << std::endl;
    std::cout << "Il y a " << nombre_premiers (atoi(argv[1]), estPremier) << " nombres premiers" << std::endl;
    //désallocation du tableau dynamique
    delete [] estPremier;
    return 0;
}