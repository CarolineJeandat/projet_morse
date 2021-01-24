#include "dictionnary.h"

char letters[47] =
    {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
        'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1',
        '2', '3', '4', '5', '6', '7', '8', '9', '.', ',', '?', '!', '/', '(',
        ')', ':', ';', '-', ' '
    };

char capital_letters[26] = 
    {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
        'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
    };

std::string morse_letters[] =
    {
        ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
        "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
        "..-", "...-", ".--", "-..-", "-.--", "--..", "-----", ".----", "..---",
        "...--", "....-", ".....", "-....", "--...", "---..", "----.", ".-.-.-",
        "--..--", "..--..", "-.-.--", "-..-.","-.--.", "-.--.-", "---...",
        "-.-.-.", "-....-", " "
    };

// création des dictionnaires du français au morse puis du morse au français

std::map <char,std::string> make_dico_letters () 
{
    std::map <char,std::string> dico;

    for ( int i=0 ; i<46 ; i++ ) 
    {
        dico.insert(std::pair<char,std::string>(letters[i], morse_letters[i]));
    }
    for ( int i=0 ; i<26 ; i++ ) 
    {
        dico.insert(std::pair<char,std::string>(capital_letters[i], morse_letters[i]));
    }

    return dico;
}

std::map <std::string,char> make_dico_morse () 
{
    std::map <std::string,char> dico;

    for ( int i=0 ; i<46 ; i++ ) 
    {
        dico.insert(std::pair<std::string,char>(morse_letters[i], letters[i]));
    }

    return dico;
}