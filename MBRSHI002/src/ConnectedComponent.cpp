#include "ConnectedComponent.h"

MBRSHI002::ConnectedComponent::ConnectedComponent(void){

  pixels = 0;
  compId = 0;

}

MBRSHI002::ConnectedComponent::ConnectedComponent(std::vector<std::pair<int, int> > comp){
  pixels = comp.size();
  compId = ++compId;
  comp = compPos;
}


int MBRSHI002::ConnectedComponent::getPixels(){
  return pixels;
}

int MBRSHI002::ConnectedComponent::getcompID(){
  return compId;
}

MBRSHI002::ConnectedComponent::~ConnectedComponent(){}


void MBRSHI002::ConnectedComponent::removeComponent(int position){
  
}


void MBRSHI002::ConnectedComponent::addComponent(std::vector<std::pair<int, int> > comp){

}
//     int compId;
//     std::vector< std::pair<int, int>> compPos;
    
// public:
//     //Setters
//     void setPixels(int pixels);
//     void setcompID();
//     void setCompPos(std::pair(int x, int y)); 

//     //Getters
//     int getPixels();
//     int getcompID();
//     std::vector<std::pair<int, int>> getcompPos();

