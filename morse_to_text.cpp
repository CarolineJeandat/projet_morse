#include "morse_to_text.h"


// convertit un string en pseudo-morse (ie pour une durée de la longueur d'un ti,
// il y a un 0 si l'audio est silencieux, et un 1 sinon

std::string convert ( std::string audio )
{
    std::string morse = "";

    int length = audio.size();
    int i = 0;
    while ( i<length )
    {
        if ( audio[i] == '1' and audio[i+1] == '1' ) { morse += "-"; i+=3; }
        else if ( audio[i] == '1' and audio[i+1] == '0' ) { morse += "."; i+=1; }
        else if ( audio[i] == '0' and audio[i+1] == '1' ) { i+=1; }
        else if ( audio[i] == '0' and audio[i+3] == '0' ) { morse += " /"; i+=9; }
        else { morse += " "; i+=3; }
    }
    return morse;
}


// compte l'occurence d'un certain entier dans un vecteur ; cette fonction sert 
// lors de la conversion des datas d'un .wav à son équivalent en pseudo-morse

int count ( std::vector <int> tab , int n )
{
    int length = tab.size();
    int c = 0;
    for ( int i=0 ; i<length ; i++ )
    {
        if ( tab[i] == n ) { c += 1; }
    }
    return c;
}


// An unsigned char can store 1 Bytes (8bits) of data (0-255)
typedef unsigned char BYTE;

// renvoie la longueur d'un fichier

long getFileSize(FILE *file)
{
	long lEndPos;
	fseek(file, 0, 2);
	lEndPos = ftell(file);
    fseek(file, 44, 0);
	return lEndPos;
}


// ouvre et lit un fichier audio dont le nom est entré par l'utilisateur ; renvoie
// le string du message en morse

std::string audio_to_morse () 
{
	const int hz = 44100;

    std::string file_name;    
    std::cout << "Quel fichier ouvrir ?" << std::endl;
    std::cin.ignore();
    getline(std::cin, file_name);
    file_name += ".wav";

    const char *filePath = file_name.c_str();
	BYTE *fileBuf;			// Pointer to our buffered data
	FILE *file = NULL;		// File pointer

    file = fopen(filePath, "rb");

	long fileSize = getFileSize(file);
    int nb_samples = (fileSize-44) / hz;

	fileBuf = new BYTE[fileSize];

	fread(fileBuf, fileSize, 1, file);
    std::string morse = "";
    
    /* transcription de l'audio en pseudo-morse : si pendant la durée de base, ie celle
    d'un ti, l'audio est silencieux, on transcrit par un 0 ; sinon, on transcrit par un 1. 
    Ainsi, ti = 1, ta = 111, les silences entre les ti et les ta = 0, les silences entre
    les lettres = 000, les silences entre les mots = 000000000 */

    for ( int sample=0 ; sample<nb_samples ; sample++ )
    {
        std::vector <int> val_sample ( hz, 0 );
        for ( int val=0 ; val<hz ; val++ )
        {
            int amp = fileBuf[ hz*sample + val + 44 ];
            val_sample[val] = amp;
        }
        if ( count ( val_sample, 0 ) >= hz-1000 ) // le son déborde parfois sur une zone de silence;
        // cette condition assure que 43 100 valeurs sur 44 100 sont des silences, ce qui garantit que
        // cette unité de temps est bien un silence
        {
            morse += '0';
        }
        else 
        {
            morse += '1';
        }
    }

	delete[]fileBuf;
	fclose(file);
    morse = convert ( morse ); // on convertit le "pseudo-morse" en vrai morse
	return morse;
}


// à partir du string du message codé en morse, renvoie sa traduction en français,
// soit dans le terminal, soit sous la forme d'un fichier .txt dont le nom est entré
// par l'utilisateur

void morse_to_text ( std::string morse ) 
{
    /* traduction du message */
    
    std::map <std::string,char> dico = make_dico_morse(); // je recrée le dictionnaire à chaque fois...
    int morse_len = morse.size();

    std::string text;
    std::string letter;

    int i = 0;
    while ( i < morse_len ) {
        if ( morse[i] == '/' ) {
            text += ' ';
            i += 1 ;
        }
        else {
            if ( morse[i] != ' ' ) {
                letter += morse[i];
                i += 1 ;
            }
            else {
                text += dico[letter];
                i += 1 ;
                letter = "";
            }
        }
    }
    
    /* renvoi de la traduction */

    int choice = 0;

    std::cout << "Renvoyer le message :" << std::endl;
    std::cout << "1. Dans le terminal" << std::endl;
    std::cout << "2. Dans un fichier .txt" << std::endl;
    std::cin >> choice;

    if ( choice == 1 ) 
    {
        std::cout << "Le message est : " << text << std::endl;
    }
    else if ( choice == 2 )
    {
        std::string file_name;
        std::cout << "Quel nom donner au fichier texte ?" << std::endl;
        std::cin.ignore();
        getline(std::cin, file_name);
        std::ofstream file_out;
        file_out.open( file_name + ".txt" );
        file_out << text << std::endl;
        file_out.close();
    }
    else 
    {
        std::cout << "Vous devez entrer 1 ou 2" << std::endl;
    }
  }