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
std::vector<std::vector<int>> Problem7::max_salle_comb(int e) {
    std::vector<std::vector<int>> props;
    FOR(t, 1, this->_specs.T) {
        std::vector<int> timeProps;
        FOR(s, 1, this->_specs.S) {
            FOR(x, 1, this->_specs.X) {
                if (A(e, x)) {
                    timeProps.push_back(this->_props[x][s][t]);
                }
            }
        }
        props.push_back(timeProps);
    }
    return props;
}

void Problem7::setConstraints(){
    Problem6::setConstraints();
    this->_constraints["etudiant_max_salle"] = [this]() {
        FOR(e, 1, this->_specs.E) {
            std::vector<std::vector<int>> max = this->max_salle_comb(e);
        }
    };
}