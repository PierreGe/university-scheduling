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
    Renvoie toutes les combinaisons possibles de salles à chaque période dans le temps (dans l'ordre)
*/
void Problem7::permut_salles(int t, int max, std::vector<std::vector<int>>& salles_impossibles, std::vector<int> salles = std::vector<int>()) {
    if (t > max) {
        int cpt = 0;
        int old_salle = salles[0];
        for (int i = 1; i < salles.size(); ++i) {
            if (salles[i] != old_salle) {
                cpt++;
            }
            old_salle = salles[i];
        }
        if (cpt > this->_specs.k) {
            salles_impossibles.push_back(salles);
        }
    }
    else {
        FOR(s, 1, this->_specs.S) {
            salles.push_back(s);
            permut_salles(t+1, max, salles_impossibles, salles);
            salles.pop_back();
        }
    }
}



void Problem7::setConstraints(){
    Problem6::setConstraints();
    this->_constraints["etudiant_max_salle"] = [this]() {
        FOR(e, 1, this->_specs.E) {
            std::vector<std::vector<int>> salles_impossibles;
            this->permut_salles(1, NA(e), salles_impossibles);
            for (auto& permut : salles_impossibles) {
                for (auto& salle : permut) {
                    std::cout << salle << " ";
                }
                std::cout << std::endl;
            }
        }
    };
}