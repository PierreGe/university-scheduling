#include <string> 
#include <iostream> 
#include <vector> 
#include <cstddef>

int main(void)
{


  std::string numbers_str = "2 ;3 ;1 ;10 ;50 ;2 ;2 ;2 ;1,2 ;1 ;1 ;2 ;";
  std::vector<std::vector<int> > data;
  std::vector<int> tempData;
  std::string  temp;
  std::string  subtemp;

  while (numbers_str.find(";", 0) != std::string::npos)
  { //does the string a comma in it?
    size_t  pos = numbers_str.find(";", 0); //store the position of the delimiter
    temp = numbers_str.substr(0, pos);      //get the token
    numbers_str.erase(0, pos + 1);          //erase it from the source 
    tempData.clear();
    if (! (temp.find(",", 0) != std::string::npos)){
      tempData.push_back(std::stoi(temp));
    }
    else {
      while (temp.find(",", 0) != std::string::npos){
          size_t  pos = temp.find(",", 0); //store the position of the delimiter
          subtemp = temp.substr(0, pos);      //get the token
          temp.erase(0, pos + 1);          //erase it from the source 
          tempData.push_back(std::stoi(subtemp));                //and put it into the array
        }
    }
    data.push_back(tempData);                //and put it into the array
  }

        for (int i = 0; i < data->size(); ++i) {
          for (int j = 0; j < data->at(i)->size(); ++j) {
            std::cout << data->at(i)->at(j) << ",";
          }
          std::cout << std::endl;
        }
  return(0);
}