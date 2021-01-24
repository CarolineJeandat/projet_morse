#pragma once
#include "dictionnary.h"


void text_to_morse ( std::string );
// à partir d'un texte, renvoie le string de sa
// traduction en morse

void morse_to_audio ( const std::string morse );
// génère un fichier .wav correspondant au message
// en morse ; le nom est choisi par l'utilisateur

std::string file_reader ( std::string file_name );
// lit un fichier .txt de nom file_name.txt et met
// son contenu dans un string