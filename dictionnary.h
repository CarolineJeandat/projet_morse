#pragma once

#include <iostream>
#include <fstream>
#include <cmath>

#include <map>
#include <string>
#include <vector>


//constexpr char letters[47];

//constexpr char capital_letters[26];

//constexpr std::string morse_letters[];

std::map <char,std::string> make_dico_letters ();

std::map <std::string,char> make_dico_morse ();