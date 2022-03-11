#include <iostream>
#include <random>
#include <time.h>
#include <cmath>
#include <fstream>

double a(){
  return double(rand()) / RAND_MAX;
}

int main(){
  srand(time(NULL));
  double timeElapsed = 0, serviceTime = 0, avgServiceTime = 0, avgArrivalRate = 0;
  double arrivalTime = 0;

  std::ofstream fout;
  fout.open("problem1.txt");

  //adapt to be processes per second, not seconds per process
  for(int i = 1; i <= 1000; i++){
    timeElapsed += -(1.0/2.0) * log(a());
    serviceTime = -(1.0/1.0) * log(1 - a());
    avgServiceTime += serviceTime;
    fout << "< " << i << "\t" << timeElapsed << "\t" << serviceTime << " >" << std::endl;
  }
  // Calculate averages
  avgServiceTime /= 1000;
  double avgArrival = timeElapsed / 1000;
  fout << "Average service time: " << avgServiceTime << std::endl;
  fout << "Average arrival rate: " << 1/avgArrival << std::endl;
 
  //close output file
  fout.close();


  //writing to output 2 file
  fout.open("problem2.txt");

  int yearInHours = 8760;
  int MTBF = 500;
  double serverFailureA = 0.0;
  double serverFailureB = 0.0;

  fout << "Server A Failure Times\t" <<  "Restoration Time\t";
  fout << "Server B Failure Times\t" <<  "Restoration Time\t" << std::endl;
  fout << "--------------------------------------------------";
  fout << "--------------------------------------------------" << std::endl;

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
      fout << serverATimes[i] << "\t\t\t";
      fout << serverATimes[i] + 10 << "\t\t\t";
    }
    else{
      fout << "\t\t\t\t\t\t";
    }
    if(j < serverBTimes.size()){
      fout << serverBTimes[j] << "\t\t\t";
      fout << serverBTimes[j] + 10 << "\t\t\t";
    }
    i++;
    j++;
    fout << std::endl;
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
    fout << "There is no total system failure within 20 years for this iteration of the simulation." << std::endl;
  }
  else{
  //TODO: consider moving this into the above while and if conditions so you may state which server fails second
    fout << "Total system failure occurs at " << failureTime << " hours." << std::endl;
  }
  //closing second output file
  fout.close();

  return 0;
}
