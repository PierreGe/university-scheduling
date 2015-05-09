#include "parser.h"
#include "problem.h"

#include <iostream>

int main(int argc, char **argv)
{
    // Vérifier le nombre d'arguments
    if (argc != 3)
    {
        std::cerr << "Utilisation : " << argv[0] << " <contraintes> <sortie>" << std::endl;
        return 1;
    }

    std::string binary_name(argv[0]);
    std::string constraints(argv[1]);
    std::string output(argv[2]);

    // Le niveau de syntaxe est donné par le numéro de question : le fichier
    // exécutable s'appelle QuestionX.bin, avec X compris entre 1 et 4.
    int syntax_level = 4;   // Tester avec toutes les fonctionnalités

    if (binary_name.size() >= 13)
    {
        char c = binary_name[binary_name.size()-5];

        if (c == '1') syntax_level = 1;
        else if (c == '2') syntax_level = 2;
        else if (c == '3') syntax_level = 3;
        else if (c == '4') syntax_level = 4;
    }

    // Parser le fichier de contraintes
    Parser parser(constraints, syntax_level);

    // Résoudre le problème
    Problem problem(parser);

    problem.solve();
    problem.write(output);
}