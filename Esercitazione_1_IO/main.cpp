#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <numbers>
#include <cstdio>
#include <fstream>


//hello, my name is samuel coriat, matricola s307195, if you see some mistake or some things that could get better feel free to email me
//this is the first exercice, we have a file with int numbers, we want to read them and compute the sum of the square
// then we check if the numbers are fallowing each other on the file 

int exo1_1() {
    std::ifstream file("data.txt"); 
    if (file.fail()) {  // checking if everything is okay, the file could not be there or idk..
        std::cerr << "Erreur d'ouverture du fichier" << std::endl;
        return 1; // if fail retourne une erreur, 1= erreur en C++ !
    }

    std::string tm;
    std::getline(file, tm);  // read the first line of the file 

    int sum = 0;
    int val = 0;  
    while (file >> val) {  // read only the integer of the file !
        sum += val * val;  // add the square of the value to the total sum 
    }

    std::cout << "Somme des carrés : " << sum << std::endl; // Affiche la somme des carrés
    printf("last value %d\n", val);


    
    //exo 1.2 del problema calcul de la somme ....
    int n=val;
    int b=0;
    b=n*(n+1)*(2*n+1)/6;
    //exo 1.3
    //checking that the 2 formula are the same 
    
    if (b==sum)
    {
        printf("the formula is correct\n");
    }
    else{
        printf("there is a big probleme in the code, the 2 formula are different happy debuging\n");
    }
    
    
    return 0;
}


int checking__if__number__in__order (){// i want to check that all the numbers in the file are one after the other so ((next line =val+1))
    std::ifstream file("data.txt"); 
    if (file.fail()) {  
        std::cerr << "Erreur d'ouverture du fichier" << std::endl;
        return 1; 
    }
    std::string tm;
    std::getline(file, tm);

    bool numbers__are__okay=true;
    int quantiti = 0;
    int val__file = 0; 
    while (file >> val__file) {  
        quantiti += 1;//theoretical value on the file !
        if (val__file!=quantiti)
        {
            printf("the number on the file is  %d",val__file);
            printf("   the theoretical number that should be there is  %d\n",quantiti);
            numbers__are__okay=false;
        }
        
    }
    
    //because booleans are nice 
    if (numbers__are__okay==false){
        printf("the numbers on the file are not ordered in the right direction thats why the formula is wrong ");
    }
    else if (numbers__are__okay==true)
    {
        printf("if the code is okay the sum should be good else problem in code ");
    }
    else{
        printf("oulaaaaaaaa there is a big probleme in the code happy debugging ")
    }
    
    return 0;
}





int main(){
    exo1_1();
    checking__if__number__in__order();
    return 0;
}




