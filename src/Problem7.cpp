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
std::vector<std::vector<int>> Problem7::permut_etudiant_temps(int e) {
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

void Problem7::iter_time(int t1, int nx, std::vector<int> permut_time, const std::vector<std::vector<int>>& permuts) {
    if (nx == 0) {
        for(auto& t : permut_time) {

        }
    }
    else {
        FOR(t2, t1, this->_specs.T) {
            permut_time.push_back(t2);
            iter_time(t1, nx-1, permut_time, permuts);
            permut_time.pop_back();
        }
    }
}

void Problem7::setConstraints(){
    Problem6::setConstraints();
    this->_constraints["etudiant_max_salle"] = [this]() {
        FOR(e, 1, this->_specs.E) {
            std::vector<std::vector<int>> permut = this->permut_etudiant_temps(e);
            FOR(t1, 1, this->_specs.T) {
                std::vector<int> permut_time;
                permut_time.push_back(t1);
                iter_time(t1, this->NA(e) - 1, permut_time, permut);
            }
        }
    };
}