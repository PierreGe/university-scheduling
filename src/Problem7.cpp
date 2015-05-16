#include "Problem7.hpp"

#include <iostream>
#include <cassert>


int Problem7::NA(int e) {
    int res = 0;
    FOR(x, 1, this->_specs.X) {
        res += A(e, x);
    }
    return res;
}

/*
    Renvoie toutes les combinaisons possibles d'examens et de salles pour l'etudiant e à chaque période de temps (dans l'ordre)
*/
void Problem7::permut_salles(int t, std::vector<int> salles = std::vector<int>()) {
    if (t > this->_specs.T) {
        int cpt = 0;
        int old_salle = salles[0];
        std::cout << salles[0];
        for (int i = 1; i < salles.size(); ++i) {
            if (salles[i] != old_salle) {
                cpt++;
            }
            old_salle = salles[i];
            std::cout << salles[i] << " ";
        }
        std::cout << std::endl << cpt << std::endl;
    }
    else {
        FOR(s, 1, this->_specs.S) {
            salles.push_back(s);
            permut_salles(t+1, salles);
            salles.pop_back();
        }
    }
}

void Problem7::setConstraints(){
    Problem6::setConstraints();
    this->_constraints["etudiant_max_salle"] = [this]() {
        this->permut_salles(1);
    };
}