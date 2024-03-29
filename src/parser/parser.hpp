#ifndef __parse__
#define __parse__


#include <string> 
#include <iostream> 
#include <vector> 
#include <cstddef>
#include "SchedSpec.hpp"

SchedSpec* parse(std::string& numbers_str) {
    std::vector<std::vector<int>* >* data = new std::vector<std::vector<int> *>();
    std::vector<int>* row;
    std::string  temp;
    std::string  subtemp;

    while (numbers_str.find(";", 0) != std::string::npos)
    { //does the string a comma in it?
        size_t  pos = numbers_str.find(";", 0); //store the position of the delimiter
        temp = numbers_str.substr(0, pos);      //get the token
        numbers_str.erase(0, pos + 1);          //erase it from the source
        row = new std::vector<int>();
        if (! (temp.find(",", 0) != std::string::npos)){
            row->push_back(std::stoi(temp));
        }
        else {
            while (temp.find(",", 0) != std::string::npos){
                size_t  pos = temp.find(",", 0); //store the position of the delimiter
                subtemp = temp.substr(0, pos);      //get the token
                temp.erase(0, pos + 1);          //erase it from the source
                row->push_back(std::stoi(subtemp));                //and put it into the array
            }
            size_t  pos = temp.find(";", 0); //store the position of the delimiter
            subtemp = temp.substr(0, pos);      //get the token
            temp.erase(0, pos + 1);          //erase it from the source
            row->push_back(std::stoi(subtemp));                //and put it into the array
        }
        data->push_back(row);                //and put it into the array
    }
    SchedSpec *schedule = new SchedSpec(data);
    // for (int i = 0; i < data->size(); ++i) {
    //     if (data->at(i) != nullptr)
    //         delete data->at(i);
    // }
    delete data;
    return schedule;
}

#endif