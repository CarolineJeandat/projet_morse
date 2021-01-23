#pragma once
#include "dictionnary.h"


//std::map <std::string,char> make_dico_morse ();

std::string audio_to_morse ();

void morse_to_text ( std::string morse );

std::string convert ( std::string audio );

int count ( std::vector <int> tab , int n );

long getFileSize(FILE *file);

