#include "parser.hpp"


/*
 * In this projet for test purpose only
 *
 */

int main(void)
{
  std::string numbers_str = "4 ;3 ;10 ;30 ;100 ;100 ;2 ;4 ;1; 1; 1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;1 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;2 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;3,4 ;1,3 ;2,4;";
  SchedSpec* specs = parse(numbers_str);
  delete specs;
  return(0);
}