#include "dictionnary.h"
#include "morse_to_text.h"
#include "text_to_morse.h"


int main () 
{
    int choice = 0;
    //entrer audio ou texte
    std::cout << "Choisissez un sens de traduction :" << std::endl;
    std::cout << "1. Du français au Morse à partir d'un fichier .txt" << std::endl;
    std::cout << "2. Du français au Morse à partir de la saisie clavier" << std::endl;
    std::cout << "3. Du Morse au français" << std::endl;
    std::cin >> choice;
    std::string text;
    std::string file_name;
    
    switch ( choice )
    {   
        case 1 :
            //Du fichier texte au morse
            std::cout << "Entrez le nom du fichier .txt : " << std::endl;
            std::cin.ignore ();
            getline ( std::cin, file_name );
            text = file_reader ( file_name );
            text_to_morse ( text );
            break;
        case 2 :
            //De la saisie clavier au morse
            std::cout << "Entrez un texte : " << std::endl;
            std::cin.ignore ();
            getline ( std::cin, text );
            text_to_morse ( text );
            break;
        case 3 :
            //Du morse au texte
            morse_to_text ( audio_to_morse () );
            break;
        default :
            std::cout << "Vous devez entrer 1, 2 ou 3" << std::endl;
            break;
    }
    
    return 0;
}