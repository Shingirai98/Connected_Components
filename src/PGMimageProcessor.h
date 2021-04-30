#ifndef _PGMIMP
#define _PGMIMP
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <memory>
#include <queue>
#include <utility>

#include "ConnectedComponent.h"

namespace MBRSHI002{
  class PGMimageProcessor{
  private:
      

      
  public:

     
    char*imageP;
    std::string inFile;
    unsigned char** imSeq;
    bool** visited;
    int rows; // y dim
    int cols;
    int max;
    int min;
    std::vector<unsigned>comps;
    //Default Constructor
    PGMimageProcessor(void);
    //Constructor
    PGMimageProcessor(std::string inputFile, std::string out);
    
    //Copy Constructor
    PGMimageProcessor(const PGMimageProcessor &p1);
    
    //Move Constructor
    PGMimageProcessor(PGMimageProcessor&& source);

    //Copy Assignment Operator
    PGMimageProcessor& operator = (const PGMimageProcessor &t);

    //Move Assignment Operator
    PGMimageProcessor& operator = (PGMimageProcessor&& other);
    
    //Destructor
    ~PGMimageProcessor();

    //methods
    bool BFS(int row, int col, int thres,int min);
    bool isValid(int row, int col, int thres);
    int extractComponents(unsigned char threshold, int minValidSize);
    int filterComponentsBySize(int minSize, int maxSize);
    bool writeComponents(const std::string &outFileName);
    int getComponentCount(void) const;
    int getLargestSize(void) ;
    int getSmallestSize(void) ;
    void printComponentData();
      
  };
}
#endif
