//
//  Writer.cpp
//  InfoFond
//
//  Created by Nicolas Omer on 20/05/14.
//  Copyright (c) 2014 Nicolas Omer. All rights reserved.
//

#include "Writer.hpp"

void writeInFile(std::string filename, std::string data){
    
    std::ofstream fichier(filename, std::ios::out | std::ios::app);
    
    if(fichier)
    {
        fichier << data;
        
        fichier.close();
    }
    else
        std::cerr << "Impossible d'ouvrir le fichier" << std::endl;
}

void writeInFile(std::string filename, int number){
    
    std::ofstream fichier(filename, std::ios::out | std::ios::app);
    
    if(fichier)
    {
        fichier << number;
        
        fichier.close();
    }
    else
        std::cerr << "Impossible d'ouvrir le fichier" << std::endl;
}