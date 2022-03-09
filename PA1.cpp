#include <iostream>
#include <random>
#include <time.h>
#include <cmath>

double a(){
  return double(rand()) / RAND_MAX;
}

int main(){
  srand(time(NULL));
  double timeElapsed = 0, serviceTime = 0, avgServiceTime = 0, avgArrivalRate = 0;
  double arrivalTime = 0;

  for(int i = 1; i <= 1000; i++){
    timeElapsed += -(1.0/2.0) * log(a());
    serviceTime = -(1.0/2.0) * log(1 - a());
    avgServiceTime += serviceTime;
    std::cout << "< " << i << "\t" << timeElapsed << "\t" << serviceTime << " >" << std::endl;
  }

  // Calculate averages
  avgServiceTime /= 1000;

  std::cout << "Average service time: " << avgServiceTime << std::endl;
  std::cout << "Average arrival rate: " << timeElapsed / 1000 << std::endl;
  
  int yearInHours = 8760;
  int MTBF = 500;
  double serverFailureA = 0.0;
  double serverFailureB = 0.0;

  std::cout << "Server A Failure Times\t" <<  "Restoration Time\t";
  std::cout << "Server B Failure Times\t" <<  "Restoration Time\t" << std::endl;
  std::cout << "--------------------------------------------------";
  std::cout << "--------------------------------------------------" << std::endl;

  std::vector<double> serverATimes;
  std::vector<double> serverBTimes;

  while(serverFailureA <= 20 * yearInHours || serverFailureB <= 20 * yearInHours){
    serverFailureA += -(500) * log(1-a());
    serverFailureB += -(500) * log(1-a());

    if(serverFailureA <= 20 * yearInHours){
      serverATimes.push_back(serverFailureA);
    }
    if(serverFailureB <= 20 * yearInHours){
      serverBTimes.push_back(serverFailureB);
    }
  }
  
  int i = 0, j = 0;
  while(i < serverATimes.size() || j < serverBTimes.size()){
    if(i < serverATimes.size()){
      std::cout << serverATimes[i] << "\t\t\t";
      std::cout << serverATimes[i] + 10 << "\t\t\t";
    }
    else{
      std::cout << "\t\t\t\t\t\t";
    }
    if(j < serverBTimes.size()){
      std::cout << serverBTimes[j] << "\t\t\t";
      std::cout << serverBTimes[j] + 10 << "\t\t\t";
    }
    i++;
    j++;
    std::cout << std::endl;
  }

  //finding the total system failure
  i = j = 0;
  double failureTime = -1;
  while(i < serverATimes.size() && j < serverBTimes.size()){
    if(serverATimes[i] <= serverBTimes[j]){
      if(abs(serverATimes[i] - serverBTimes[j]) < 10.0){
        failureTime = serverBTimes[j];
        break;
      }
      i++;
      continue;
    }
    else if(serverBTimes[j] <= serverATimes[i]){
      if(abs(serverBTimes[j] - serverATimes[i]) < 10.0){
        failureTime = serverATimes[i];
        break;
      }
      j++;
      continue;
    }
  }


  if(failureTime == -1){
    std::cout << "There is no total system failure for this iteration of the simulation." << std::endl;
  }
  else{
  //TODO: consider moving this into the above while and if conditions so you may state which server fails second
    std::cout << "Total system failure occurs at " << failureTime << " hours." << std::endl;
  }

  return 0;
}
