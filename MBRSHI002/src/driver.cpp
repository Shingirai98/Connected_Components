#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <cstdlib>
#include <queue>
#include "ConnectedComponent.h"
#include "PGMimageProcessor.h"


// #define CATCH_CONFIG_MAIN // This tells catch to provide a main() function.
// #include "catch.hpp"

int main(int argc, char* argv[]){
    //int operations = 0;
    int threshold = 0;
    int max = 0;
    int min = 0;
    //if user doesnt put the parameters evoke an error
    if (argc==1){
        std::cerr << "Please specify the parameters ie....." << std::endl;
    }
    //else assign the values to variables
    else{
      std::string inFile = argv[argc-1];
      std::string out = argv[argc-2];
      MBRSHI002::PGMimageProcessor pgm = MBRSHI002::PGMimageProcessor(inFile);
       
      int arguments = 1;
      
      if ((std::string)argv[arguments] == "-s"){
        
        min = atoi(argv[++arguments]);
        
        max = atoi(argv[++arguments]);
        
        arguments++;
        //std::cout<<arguments++;
      }
      
      
      if ((std::string)argv[arguments] == "-t"){
      // -t -> 4 threshold and call extracted components
        
        threshold = atoi(argv[++arguments]);
        pgm.extractComponents(threshold, min);
        
        arguments++;
      }

      if ((std::string)argv[arguments] == "-p"){
        // -p print components data
        
        pgm.printComponentData();

        arguments++;
        
      }
      

      if ((std::string)argv[arguments] == "-w"){
      // -w ->7 write to image the components data
        
        std::string outFile = argv[++arguments];
        pgm.writeComponents(outFile);

      }
      
      
    
  
  
      
      
    }

    return 0;
}

