#pragma once

/* inclusion de toutes les bibliothèques utiles pour le projet,
qui seront insérées au début de tous les fichiers .cpp */

#include <iostream>
#include <fstream>
#include <cmath>

#include <map>
#include <string>
#include <vector>


std::map <char,std::string> make_dico_letters ();

std::map <std::string,char> make_dico_morse ();