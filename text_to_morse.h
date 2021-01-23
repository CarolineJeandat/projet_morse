#pragma once
#include "dictionnary.h"


//std::map <char,std::string> make_dico_letters ();
//génère le dictionnaire qui donne l'équivalent 
// morse des caractères français

void text_to_morse ( std::string );
// à partir d'un texte, renvoie le string de sa
// traduction en morse

void morse_to_audio ( const std::string morse );
// génère un fichier .wav correspondant au message
// en morse, de nom "message_morse.wav"

std::string file_reader ( std::string file_name );
// lit un fichier .txt et met son contenu dans un string
