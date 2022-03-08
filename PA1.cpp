#include <iostream>
#include <random>
#include <time.h>
#include <cmath>

double a(){
  return double(rand()) / RAND_MAX;
}
double b(){
  
  return ((double(rand()) / RAND_MAX) / 4 ) + 0.25;
}
double c(){
  // {{1, 0.5}, {2, 0.2},{x, 0.3}}
  // on intervals {1, 0.0 < x <= 0.5}, {2, {0.5 > x <= 0.7}},
  // {3.0-4.0, 0.7 <= x <= 1.0}
  double result = double(rand()) / RAND_MAX;
  
  if(result < 0.5){
    return 1.0;
  }
  else if(result >= 0.5 && result <= 0.7){
    return 2.0;
  }
  else{
    return ((double(rand()) / RAND_MAX)) + 3; //is there a precision for this?
  }
}

int main(){
  srand(time(NULL));
  double timeElapsed = 0, serviceTime = 0;
  
  for(int i = 1; i <= 1000; i++){
    timeElapsed += -(1.0/2.0) * log(a()); 
    std::cout << "< " << i << "\t" << timeElapsed << "\t" << std::endl;
  }
  

  return 0;
}
