#include "PTT_Gestures.hpp"

#include <cstdint>
#include <iostream>
#include <fstream>

int main() {
   
   Pointata::GestureString gs;
   
   gs.queueGesture(Pointata::Gestures::A);
   gs.queueGesture(Pointata::Gestures::_8);
   
   std::ofstream out("graph.txt");
   
   long step = 0;
   
//    for(int i = 0; i < 20; ++i) {
   while(!gs.isComplete()) {
      
      gs.step();
      
      auto x = gs.getXPos();
      auto y = gs.getYPos();
      
      out << step << ", " << (int)x << ", " << (int)y << std::endl;
      
      std::cout << "Step " << step << std::endl;
      
      ++step;
   }
}
