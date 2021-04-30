
#include "PGMimageProcessor.h"




MBRSHI002::PGMimageProcessor::PGMimageProcessor(std::string InputFile std::string out){
    //intialize input file
    std::ifstream imageFile(InputFile, std::ios::binary);
    
    //  if file is not read evoke an error
    //std::cout<< InputFile;
    if(!imageFile){
        std::cerr << "Could not open file" << std::endl;
    }
    
    //else read the file in a pgm format
    else{
        std::string format;// first line in PGM file
        std::string comment;// comment in file
        std::string c; // the dimensions
        std::string bins;
         // x dim
        std::getline(imageFile , format); //ignore format
        while(std::getline(imageFile , c)){
          if (comment[0] != '#'){
            break;
          }
        }
       // std::getline(imageFile,c); // store dimensions in c
        std::getline(imageFile, bins); // store range of BnW value
        std::istringstream ss(c); // store the two values as a string
        std::string X;
        std::string Y;
         // assign x dimension
        ss >> X; // assign the x dimension of the image
        ss >> Y;// assign the y dimension of the image
        // convert to integers
        cols = stoi(X);
        rows = stoi(Y);
        
        // read the file and point to it using the buffer pointer
        
        //assign the length of the array
        //char * buffer = new char [rows*cols];
        
        //equate it to a global pointer
        imageP = new char [rows*cols];

        //delete space initialized by buffer
        //delete[] buffer;

        // read image and store in an array pointed to by imageP
        imageFile.read(imageP, (rows*cols));

        //allocate memory for 2D array pointer
        //assign number of rows
        imSeq = new unsigned char*[rows];
        for(int i=0; i < rows; i++){
          // assign number of columns
          imSeq[i] = new unsigned char[cols];
        }

        visited = new bool*[rows];
        for(int i=0; i < rows; i++){
          // assign number of columns
          visited[i] = new bool[cols];
        }

        //initialize output file
        std::ofstream outputFile("out.pgm", std::ios::binary);

        //print the header of pgm files
        outputFile << "P5\n" << cols << " " << rows <<  "\n"<< 255 << std::endl;
        
        // add each pixel from pointer to 2D array pointer
        for (int i = 0; i < rows; i++  ){
            for(int j = 0; j < cols; j++){
                //add pixel to 2D array
                
                imSeq[i][j] =*(imageP+((i*cols)+j));
                //add the pixels to the output image
                outputFile<< imSeq[i][j];
                //start++;
            }
        }

        

    }
}


//Destructor
MBRSHI002::PGMimageProcessor::PGMimageProcessor::~PGMimageProcessor(){
    if (imageP!=nullptr){
      delete[] imageP;
      std::cout << "Pointer destroyed"<< std::endl;
    }

    for(int i = 0; i < rows; ++i) {
        delete[] imSeq[i];   
    }
    //Free the array of pointers
    delete[] imSeq;

    for(int i = 0; i < 5; ++i) {
        delete[] visited[i];   
    }
    //Free the array of pointers
    delete[] visited;
}

//Copy Constructor
MBRSHI002::PGMimageProcessor::PGMimageProcessor(const PGMimageProcessor &p1){

}

//Move Constructor
MBRSHI002::PGMimageProcessor::PGMimageProcessor(PGMimageProcessor&& source){

}

//Copy Assignment Operator
// PGMimageProcessor::PGMimageProcessor& PGMimageProcessor::operator = (const PGMimageProcessor &t){

// }

//Move Assignment Operator
// MBRSHI002::PGMimageProcessor::PGMimageProcessor& PGMimageProcessor::operator = (PGMimageProcessor&& other){

// }
bool MBRSHI002::PGMimageProcessor::BFS(int row, int col, int thres, int min){
  // Queue Stores indices of the matrix cells
  std::queue<std::pair<int, int> > q;
  std::vector<std::pair<int,int > > component;

  // directions for traversal in grid
  int dRow[] = { -1, 0, 1, 0 };
  int dCol[] = { 0, 1, 0, -1 };

  // Mark the starting cell as visited and push it into the queue
  q.push(std::make_pair(row, col ));
  component.push_back(std::make_pair(row, col ));
  // make the coordinate white
  imSeq[row][col] = 255;

  //make the coordinate visited
  visited[row][col] = true;

  // Iterate while the queue is not empty
  
  while (!q.empty()) {

    //initialize an empty pair cell
    std::pair<int, int> cell = q.front();
    // assign x as the first cell
    int x = cell.first;

    // assign y as the second cell
    int y = cell.second;



    // remove the first added cell in queue
    q.pop();

    // Go to the adjacent cells
    for (int i = 0; i < 4; i++) {

      //move to the left, then top, then right, then bottom
      int adjx = x + dRow[i];
      int adjy = y + dCol[i];

      // if the cooridinate is valid --
      if (isValid( adjx, adjy, thres)) {

        // make coordinate white
        imSeq[adjx][adjy] = 0;
        //add it to queue
        q.push(std::make_pair( adjx, adjy ));
        //add to component vector
        component.push_back(std::make_pair(adjx, adjy ));
        //assign it as visited
        visited[adjx][adjy] = true;
      }
      else{
        // if coordinate is not valid, make it white 
        imSeq[adjx][adjy] = 255;
        visited[adjx][adjy] = true;
      }
    }
  }
  if (component.size() >= min){
    ConnectedComponent c =  ConnectedComponent(component);
    comps.push_back(c);
    //std::cout << "Component number: " << c.getcompID() <<std::endl;
    //std::cout << "Number of pixels: " << component.size() <<std::endl;
    return true;
  }
  else{
    return false;
  }
  
}
bool MBRSHI002::PGMimageProcessor::isValid(int row, int col, int thres)
  {
    // If cell lies out of bounds 
    if (row < 0 || col < 0|| row >= rows || col >= cols ){

    
      return false;
    }
    // If cell is already visited
    if (visited[row][col] || (imSeq[row][col] < thres)){
      return false;
    }
    // Otherwise

    return true;
  }

/* process the input image to extract all the connected components,
based on the supplied threshold (0...255) and excluding any components
of less than the minValidSize. The final number of components that
you store in your container (after discarding undersized one)
must be returned.
*/

int MBRSHI002::PGMimageProcessor::extractComponents(unsigned char threshold, int minValidSize){
  
  // #define ROW 4
  // #define COL 4
  int counter=0;
  for (int i = 0; i < rows; i++  ){
      for(int j = 0; j < cols; j++){
          //add pixel to 2D array
        if ((imSeq[i][j] > threshold) && (!visited[i][j])){
          if(BFS( i, j, threshold, minValidSize)){
            counter++;
          }
          //std::cout<< "Here lies a component"<<std::endl;
          
        }
        else if((imSeq[i][j] < threshold)){
          imSeq[i][j] = 0;
        }
       
      }
  }
  
  
  std::cout<< counter<<std::endl;
  std::cout<< comps.size() <<std::endl;



  //return the static number of components size or make a counter and return it 
  return counter;
}

/* iterate - with an iterator - though your container of connected
components and filter out (remove) all the components which do not
obey the size criteria pass as arguments. The number remaining
after this operation should be returned.
*/
int MBRSHI002::PGMimageProcessor::filterComponentsBySize(int minSize, int maxSize){
  //std::vector<ConnectedComponent>::iterator it;

  for (std::vector<ConnectedComponent>::iterator it = comps.begin(); it != comps.end(); it++){
    if ((((*it).getPixels()) < minSize) || (((*it).getPixels())> maxSize)){
      comps.erase(it);
    }
  }
        //std::cout << *it << " ";


}

/* create a new PGM file which contains all current components
(255=component pixel, 0 otherwise) and write this to outFileName as a
valid PGM. the return value indicates success of operation
*/
bool MBRSHI002::PGMimageProcessor::writeComponents(const std::string &outFileName){
  std::ofstream outputFile(outFileName, std::ios::binary);

  //print the header of pgm files
  outputFile << "P5\n" << cols << " " << rows <<  "\n"<< 255 << std::endl;
  
  // add each pixel from pointer to 2D array pointer
  for (int i = 0; i < rows; i++  ){
      for(int j = 0; j < cols; j++){
          //add pixel to 2D array
          
          
          
          outputFile<< imSeq[i][j];
          
      }
  }

}

// return number of components
int MBRSHI002::PGMimageProcessor::getComponentCount(void) const {
  return comps.size();
}

// return number of pixels in largest component
 int MBRSHI002::PGMimageProcessor::getLargestSize(void)  {

  max = (comps[0]).getPixels();
  

  for(int i=1; i < comps.size(); i++){
    if ((comps[i]).getPixels() > max){
      max = (comps[i]).getPixels();
    }
    
  }
  //std::cout<< "Max is: " << max << std::endl;
  

  return max;

}

// return number of pixels in smallest component
int MBRSHI002::PGMimageProcessor::getSmallestSize(void) {
  
  min = (comps[0]).getPixels();

  for(int i=1; i < comps.size(); i++){
    if ((comps[i]).getPixels() < min){
      min = (comps[i]).getPixels();
    }
  }
  return min;
  //std::cout<< "Min is: " << min << std::endl;
}

void MBRSHI002::PGMimageProcessor::printComponentData(){
  std::cout << "--------------------------------------------" <<std::endl;
  for(int i=1; i < comps.size(); i++){
    std::cout<<"|Component ID: " <<i<< " number of pixels: " << comps[i].getPixels() << std::endl;
  }
  std::cout<< "|Component with the largest size has: "<< getLargestSize() <<std::endl;
  std::cout<< "|Component with the smallest size has: "<< getSmallestSize() <<std::endl;
  std::cout<< "|Number of components: "<< getComponentCount() <<std::endl;
  std::cout << "--------------------------------------------" <<std::endl;

}

