#include "Problem7.hpp"

#include <iostream>
#include <cassert>
#include <algorithm>


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
void Problem7::permut_salles(int s1, int max, std::vector<std::vector<int>>& salles_impossibles, std::vector<int> salles = std::vector<int>()) {
    if (s1 > max) {
        int cpt = 0;
        if (salles.size() > 0) {
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
    }
    else {
        FOR(s2, 1, this->_specs.S) {
            salles.push_back(s2);
            permut_salles(s1+1, max, salles_impossibles, salles);
            salles.pop_back();
        }
    }
}

void Problem7::permut_temps(int t, int max, std::vector<std::vector<int>>& temps_possibles, std::vector<int> temps = std::vector<int>()) {
    if (temps.size() == max) {
        temps_possibles.push_back(temps);
    }
    else {
        FOR(t2, t, this->_specs.T) {
            temps.push_back(t2);
            permut_temps(t2+1, max, temps_possibles, temps);
            temps.pop_back();
        }
    }
}

std::vector<std::vector<int>> Problem7::permut_examens(int e) {
    std::vector<std::vector<int>> examens_possibles;
    std::vector<int> examens;
    FOR(x, 1, this->_specs.X) {
        if (A(e, x))
            examens.push_back(x);
    }
    std::sort(examens.begin(), examens.end());
    do {
        examens_possibles.push_back(examens);
    }
    while (std::next_permutation(examens.begin(), examens.end()));
    return examens_possibles;
}

void Problem7::setConstraints(){
    Problem6::setConstraints();
    this->_constraints["etudiant_max_salle"] = [this]() {
        FOR(e, 1, this->_specs.E) {
            std::vector<std::vector<int>> salles_impossibles;
            this->permut_salles(1, NA(e), salles_impossibles);
            std::vector<std::vector<int>> temps_possibles;
            this->permut_temps(1, NA(e), temps_possibles);
            std::vector<std::vector<int>> examens_possibles = this->permut_examens(e);
            for (auto& temps : temps_possibles) {
                for (auto& salles : salles_impossibles) {
                    for (auto& examens: examens_possibles) {
                        vec<Lit> lits;
                        for (int i = 0; i < examens.size(); ++i) {
                            lits.push(~Lit(this->_props[examens.at(i)][salles.at(i)][temps.at(i)]));
                        }
                        this->_solver.addClause(lits);
                    }
                }
            }
        }
    };
}