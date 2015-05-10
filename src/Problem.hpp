//
//  Problem.h
//  InfoFond
//
//  Created by Nicolas Omer on 14/05/14.
//  Copyright (c) 2014 Nicolas Omer. All rights reserved.
//

#ifndef __InfoFond__Problem__
#define __InfoFond__Problem__

#include "Solver.hpp"
#include "Writer.h"
#include <vector>
#include <algorithm>
#include <iostream>

int propP1(int, int, int);
int mainP1(std::vector<std::vector<int> > , std::string);
void displayP1(std::string);
bool canPlayP1(int, int);
void setConstraintP1();

#endif /* defined(__InfoFond__Problem__) */
