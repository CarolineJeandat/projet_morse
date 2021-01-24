DOCUMENTATION UTILISATEUR :

L'algorithme permet de traduire un texte en français en Morse, sur un fichier audio .wav, et inversement. Le texte en français peut être entré via un fichier .txt, ou directement en le saisissant sur le clavier.

Attention : tous les caractères ne sont pas disponibles. Les caractères autorisés sont : les lettres de l'alphabet latin, en majuscule et en minuscule ; les chiffres de 0 à 9 ; les caractères de ponctuation suivants : . , ? ! / ( ) : ; -
On notera notamment que les lettres avec accent, le ç, l'apostrophe et les guillemets ne sont pas disponibles.

Lorsque le terminal demande de saisir le nom d'un fichier, entrer un fichier sous le format indiqué (.txt ou .wav), sans préciser .txt ou .wav à la fin du nom du fichier (entrer "nom_fichier" et pas "nom_fichier.txt").

Ce dossier comporte 2 fichiers audio .wav test, et 5 fichiers test .txt (leur traduction en audio morse n'a pas été ajoutée dans ce dossier car ils sont trop volumineux).

Un Makefile permet la compilation des différentes fonctions.
