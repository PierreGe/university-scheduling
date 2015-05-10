//
//  Problem.cpp
//  InfoFond
//
//  Created by Nicolas Omer on 14/05/14.
//  Copyright (c) 2014 Nicolas Omer. All rights reserved.
//

#include "Problem.h"

#define FOR(k, lb, ub) for (int k = (lb) ; (k) <= (ub) ; (k)++)

int I1, K1, M1, G1;
Solver S1;
std::vector<std::vector<int> > matrix1;

int propP1(int a, int b, int c){
    return ( ( (a - 1) * G1 + (b - 1) ) * G1 + c);
}

int mainP1(std::vector<std::vector<int> > mat, std::string filename){
    
    matrix1 = mat;
    M1 = matrix1[0][0];
    I1 = matrix1[0][1];
    K1 = matrix1[0][2];
    G1 = max(I1, max(K1, M1));
    FOR(j, 1, (propP1(M1, I1, K1) + 1)){
        S1.newVar();}
    setConstraintP1();
    S1.solve();
    displayP1(filename);
    
    return 0;
}

void displayP1(std::string filename){
    if (S1.okay()){
        FOR (c, 1, K1){
            //std::cout << "Groupe " << c << ": ";
            writeInFile(filename, "groupe ");
            writeInFile(filename, c);
            writeInFile(filename, ": ");
            FOR (b, 1, I1){
                FOR (a, 1, M1){
                    if (S1.model[propP1(a, b, c)] == l_True){
                        //std::cout << a << " ";
                        writeInFile(filename, a);
                        writeInFile(filename, " ");
                    }
                }
            }
            //std::cout << std::endl;
            writeInFile(filename, "\n");
        }
    }
    else{
        //std::cout << "Non Satifaisable";
        writeInFile(filename, "impossible");
    }
}

bool canPlayP1(int a, int b){
    FOR(i, 1, matrix1[a].size() - 1){
        if (matrix1[a][i] == b){
            return true;
        }
    }
    return false;
}

void setConstraintP1(){
    
    vec<Lit> lits;
    // Contrainte d'existence
    FOR(a, 1, M1){
        lits.clear();
        FOR(b, 1, matrix1[a].size() - 1){
            FOR(c, 1, K1){
                lits.push(Lit(propP1(a, matrix1[a][b], c)));
            }
        }
        S1.addClause(lits);
    }
    FOR(a, 1, M1){
        FOR(b1, 1, matrix1[a].size() - 1){
            FOR(b2, 1, matrix1[a].size() - 1){
                FOR(c1, 1, K1){
                    FOR(c2, c1 + 1, K1){
                        // Contrainte 1 joueur dans un seul groupe
                        S1.addBinary(~Lit(propP1(a, matrix1[a][b1], c1)), ~Lit(propP1(a, matrix1[a][b2], c2)));
                    }
                }
            }
        }
    }
    
    FOR(a, 1, M1){
        FOR(c, 1, K1){
            FOR(b1, 1, matrix1[a].size()-1){
                FOR(b2, b1 + 1, matrix1[a].size()-1){
                    // Contrainte ¬ 2 instruments dans le même groupe
                    S1.addBinary(~Lit(propP1(a, matrix1[a][b1], c)), ~Lit(propP1(a, matrix1[a][b2], c)));
                }
            }
        }
    }
    
    FOR(c, 1, K1){
        FOR(a1, 1, M1){
            FOR(b1, 1, matrix1[a1].size() - 1){
                FOR(b2, 1, I1){
                    if (matrix1[a1][b1] != b2){
                        lits.clear();
                        lits.push(~Lit(propP1(a1, matrix1[a1][b1], c)));
                        FOR(a2, 1, M1){
                            // Contrainte tout instrument ou aucun dans chaque groupe
                            if(a1 != a2 && canPlayP1(a2, b2)){
                                lits.push(Lit(propP1(a2, b2, c)));
                            }
                        }
                        S1.addClause(lits);
                    }
                }
            }
        }
    }
    
    FOR(c, 1, K1){
        FOR(a1, 1, M1){
            FOR(a2, a1 + 1, M1){
                FOR(b, 1, matrix1[a1].size() - 1){
                    // Contrainte pas deux musiciens qui jouent d'un même instrument dans un même groupe
                    if (canPlayP1(a2, matrix1[a1][b]))
                    {
                        S1.addBinary(~Lit(propP1(a1, matrix1[a1][b], c)), ~Lit(propP1(a2, matrix1[a1][b], c)));
                    }
                }
            }
        }
    }
}