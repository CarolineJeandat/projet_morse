#include "text_to_morse.h"

namespace little_endian_io
{
  template <typename Word>
  std::ostream& write_word( std::ostream& outs, Word value, unsigned size = sizeof( Word ) )
  {
    for (; size; --size, value >>= 8)
      outs.put( static_cast <char> (value & 0xFF) );
    return outs;
  }
}
using namespace little_endian_io;




/* FONCTIONS */



/* prend en entrée un texte en français et le traduit en morse, avant de l'envoyer au créateur d'audio */

void text_to_morse ( std::string text ) 
{
    std::map <char,std::string> dico = make_dico_letters(); // je recrée à chaque fois le dico...
    int text_len = text.size();

    text_len = text.size();

    std::string morse;

    // traduction en morse
    for ( int i=0 ; i<text_len ; i++ ) {
        if ( text[i] == ' ' ) {
            morse += "/";
        }
        else {
            morse += dico[text[i]];
            morse += " ";
        }
    }
    morse_to_audio ( morse ) ;
}




/* lit un fichier .txt et met son contenu dans un string */

std::string file_reader ( std::string file_name ) 
{
    std::ifstream file_in;
    file_in.open ( file_name + ".txt" );
    std::string text = "";

    for ( std::string s ; file_in >> s ; )
    {
        text += s;
        text += " ";
    }

    file_in.close();
    return text;
}




/* crée un fichier audio correspondant à la chaîne de caractères en morse donnée en entrée */

void morse_to_audio ( const std::string morse )
{
    std::string file_name;
    std::cout << "Quel nom donner au fichier audio ?" << std::endl;
    getline(std::cin, file_name);
    std::ofstream f( file_name + ".wav", std::ios::binary );

    // Write the file headers
    f << "RIFF----WAVEfmt ";
    write_word( f,     16, 4 );  // no extension data
    write_word( f,      1, 2 );  // PCM - integer samples
    write_word( f,      2, 2 );  // two channels (stereo file)
    write_word( f,  44100, 4 );  // samples per second (Hz)
    write_word( f, 176400, 4 );  // (Sample Rate * BitsPerSample * Channels) / 8
    write_word( f,      4, 2 );  // data block size
    write_word( f,     16, 2 );  // number of bits per sample

    // Write the data chunk header
    size_t data_chunk_pos = f.tellp();
    f << "data----";
    
    // Write the audio samples
    const double two_pi = 6.283185307179586476925286766559;
    const double amplitude = 3276;

    const double hz        = 44100;
    const double frequency = 261.626; 
    const double seconds   = 0.5;

    int morse_len = morse.size();
    int time_ti = hz * seconds; // durée d'un ti : 0.5 seconde
    int time_ta = 3*time_ti; // durée d'un ta
    int time_silence_lettre = time_ti; // silence entre les lettres (1+1+1 à la fin de chaque lettre)
    int time_silence_mot = 5*time_ti; // silence entre les mots (6+1+1 à la fin de la dernière lettre)
    int time_silence = time_ti; // silence entre chaque ti / ta

    size_t file_length = f.tellp();

    // écriture des data dans le .wav

    for (int i_lettre = 0; i_lettre < morse_len; i_lettre++)
    {
        switch ( morse[i_lettre] )
        {
            case '.' : // ti
                for ( int n=0 ; n<time_ti ; n++ ) 
                {
                    double value = sin( (two_pi * n * frequency) / hz );
                    write_word( f, (int)( amplitude*value ), 2 );

                }
                break;
            case '-' : // ta
                for ( int n=0 ; n<time_ta ; n++ ) 
                {
                    double value = sin( (two_pi * n * frequency) / hz );
                    write_word( f, (int)( amplitude*value ), 2 );
                }
                break;
            case ' ' : // entre les lettres
                for ( int n=0 ; n<time_silence_lettre ; n++ ) 
                {
                    write_word( f, (int)(0), 2 );
                }
                break;
            case '/' : // entre les mots
                for ( int n=0 ; n<time_silence_mot ; n++ ) 
                {
                    write_word( f, (int)(0), 2 );
                }
                break;
            default :
                std::cout << "erreur" << std::endl;
                break;
        }
        // silence à la fin d'un ti / ta
        for ( int n=0 ; n<time_silence ; n++ ) 
        {
            write_word( f, (int)(0), 2 );
        }
        file_length = f.tellp();
    }
  
    file_length = f.tellp();

    f.seekp( data_chunk_pos + 4 );
    write_word( f, file_length - data_chunk_pos + 8 );

    f.seekp( 0 + 4 );
    write_word( f, file_length - 8, 4 );
}