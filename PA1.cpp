#include <iostream>
#include <random>
#include <time.h>
#include <cmath>
#include <fstream>

void problem1(){
  double timeElapsed = 0, serviceTime = 0, avgServiceTime = 0, avgArrivalRate = 0;
  double arrivalTime = 0;

  std::ofstream fout;
  fout.open("problem1.txt");

  fout << "Event\t Arrival\t Service" << std::endl
       << "     \t  Time\t    Time" << std::endl << std::endl;
  fout << "--------------------------" << std::endl;
  for(int i = 1; i <= 1000; i++){
    timeElapsed += -(1.0/2.0) * log(double(rand()) / RAND_MAX);
    serviceTime = -(1.0/1.0) * log(1 - double(rand()) / RAND_MAX);
    avgServiceTime += serviceTime;
    fout << "< " << i << "\t" << timeElapsed << "\t" << serviceTime << " >" << std::endl << std::endl;
  }
  // Calculate averages
  avgServiceTime /= 1000;
  double avgArrival = timeElapsed / 1000;
  fout << "Average service time: " << avgServiceTime << std::endl;
  fout << "Average arrival rate: " << 1/avgArrival << std::endl;
  
  std::cout << "Average service time: " << avgServiceTime << std::endl;
  std::cout << "Average arrival rate: " << 1/avgArrival << std::endl;
 
  //close output file
  fout.close();
}

void generateEvents(std::vector<double>& serverAEvents, std::vector<double>& serverBEvents){
  //generates + appends 20 years worth of server failure events to the end of the file
  
  std::ofstream fout;
  //writing to output 2 file
  fout.open("problem2.txt", std::ios::app);

  int twentyYearsInHours= 24 * 365 * 20;
  double serverFailureA = 0.0;
  double serverFailureB = 0.0;

  while(serverFailureA <= twentyYearsInHours || serverFailureB <= twentyYearsInHours){
    serverFailureA += -(500) * log(1 - double(rand()) / RAND_MAX);
    serverFailureB += -(500) * log(1 - double(rand()) / RAND_MAX);

    if(serverFailureA <= twentyYearsInHours){
      serverAEvents.push_back(serverFailureA);
    }
    if(serverFailureB <= twentyYearsInHours){
      serverBEvents.push_back(serverFailureB);
    }
  }

  int i = 0, j = 0;
  
  //TODO: put in separate print function?
  while(i < serverAEvents.size() || j < serverBEvents.size()){
    if(i < serverAEvents.size()){
      fout << serverAEvents[i] << "\t\t\t";
      fout << serverAEvents[i] + 10 << "\t\t\t";
    }
    else{
      fout << "\t\t\t\t\t\t";
    }
    if(j < serverBEvents.size()){
      fout << serverBEvents[j] << "\t\t\t";
      fout << serverBEvents[j] + 10 << "\t\t\t";
    }
    i++;
    j++;
    fout << std::endl;
  } 
  //fout.close();
}

double totalSystemFailure(std::vector<double>& serverAEvents, std::vector<double>& serverBEvents, int i = 0, int j = 0){
  //finding the total system failure
  double failureTime = -1;

  //find overlapping restoration times
  while(i < serverBEvents.size() && j < serverBEvents.size()){
    if(serverAEvents[i] <= serverBEvents[j]){
      if(abs(serverAEvents[i] - serverBEvents[j]) < 10.0){
        failureTime = serverBEvents[j];
        break;
      }
      i++;
      continue;
    }
    else if(serverBEvents[j] <= serverAEvents[i]){
      if(abs(serverBEvents[j] - serverAEvents[i]) < 10.0){
        failureTime = serverAEvents[i];
        break;
      }
      j++;
      continue;
    }
  }
  
  return failureTime;
}

void problem2(){
  std::ofstream fout;
  //writing to output 2 file
  fout.open("problem2.txt");

  int twentyYearsInHours= 24 * 365 * 20;
  double serverFailureA = 0.0;
  double serverFailureB = 0.0;

  fout << "Server A Failure Times\t" <<  "Restoration Time\t";
  fout << "Server B Failure Times\t" <<  "Restoration Time\t" << std::endl;
  fout << "--------------------------------------------------";
  fout << "--------------------------------------------------" << std::endl;

  std::vector<double> serverAEvents;
  std::vector<double> serverBEvents;
  double systemFailure = -1;
  double averageFailure = 0;

  int k = 1; //sets of 20 years
  while(systemFailure == -1){
    int sizeA = serverAEvents.size(), sizeB = serverBEvents.size();
    generateEvents(serverAEvents, serverBEvents);
    systemFailure = totalSystemFailure(serverAEvents, serverBEvents, sizeA, sizeB);
    k++;
  }
    
  fout << "\n\nTotal system failure occurs at " << systemFailure << " hours." << std::endl;
  std::cout << "\n\nTotal system failure occurs at " << systemFailure << " hours." << std::endl;
  
  //close output file
  fout.close();
}

int main(int argc, char* argv[]){
  srand(time(NULL));
  std::ofstream file1;
  std::ofstream file2;

  file2.open("problem2.txt");

  if(argc > 1){
    for(int i = 0; i < std::atoi(argv[1]); i++){
      //Run a simulation of 1000 processes, and print the average of the arrival rates and service times.
      problem1();
  
      //Run a simulation of 20 years, printing events (failures) and their restoration times
      //to a 'problem2.txt'. If no total system failure by 20 years, repeat.
      problem2();
    }
  }

  //Run a simulation of 1000 processes, and print the average of the arrival rates and service times.
  problem1();
  
  //Run a simulation of 20 years, printing events (failures) and their restoration times
  //to a 'problem2.txt'. If no total system failure by 20 years, repeat.
  problem2();

  file2.close();
  return 0;
}
