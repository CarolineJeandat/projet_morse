#pragma once
#include "dictionnary.h"


std::string audio_to_morse ();
// transcrit un audio en chaîne de caractère en morse

void morse_to_text ( std::string morse );
// traduit le message du morse au français

std::string convert ( std::string audio );
// traduit un message en "pseudo-morse" (des 0 et des 1)
// en un message en morse

int count ( std::vector <int> tab , int n );
// fonction auxiliaire qui compte le nombre de n dans
// tab

long getFileSize(FILE *file);
// fonction auxiliaire qui renvoie la longueur de file

