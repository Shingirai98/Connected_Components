#ifndef _CC
#define _CC
#include "PGMimageProcessor.h"

namespace MBRSHI002{
  
  class ConnectedComponent{
  private:
  
      int pixels;
      int compId;
      std::vector< std::pair<int, int> > compPos;
      
  public:
    
    ConnectedComponent(void);
  
    ConnectedComponent(std::vector<std::pair<int, int> > comp);

    ~ConnectedComponent();
    
    //Getters
    int getPixels();
    int getcompID();
    void removeComponent(int position);
    void addComponent(std::vector<std::pair<int, int> > comp);
    

  };
}

#endif

