#pragma once

#include "PTT_Types.hpp"

#include <cstdint>

#define PTT_LOG_ENABLED
#ifdef PTT_LOG_ENABLED
#  include <iostream>
#  define PTT_LOG(...) std::cout << __VA_ARGS__ << std::endl;
#else
#  define PTT_LOG(...)
#endif

namespace Pointata {
   
typedef uint8_t MotionCommandType;

namespace Gestures {
   
#define ARG_N(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,N,...) N
#define NARG_(...) ARG_N(__VA_ARGS__)
#define NARG(...) NARG_(__VA_ARGS__,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)
   
#ifdef GESTURE_IMPLEMENTATION
#  define GESTURE(NAME, ...) \
      MotionCommandType NAME[NARG(__VA_ARGS__) + 1] = { NARG(__VA_ARGS__), __VA_ARGS__ };
#else
#  define GESTURE(NAME, ...) \
      extern MotionCommandType NAME[NARG(__VA_ARGS__) + 1];
#endif
   
GESTURE(A,  jp(6), mv(0, 2), mv(2, 2), mv(8, 2), jp(3), mv(5, 2) )
GESTURE(B,  jp(0), mv(6, 2), jp(0), mv(2, 2), mv(4), mv(3), mv(5, 2), mv(8), mv(6, 2) )
GESTURE(C,  jp(2), mv(0, 2), mv(6, 2), mv(8, 2) )
GESTURE(D,  jp(2), mv(7, 2), jp(0), mv(2, 2), mv(8, 2), mv(6, 2) )
GESTURE(E,  jp(2), mv(0, 2), mv(3), mv(5, 2), mv(3, 2), mv(6), mv(8, 2) )
GESTURE(F,  jp(2), mv(0, 2), mv(6, 2), jp(3), mv(5, 2) )
GESTURE(G,  jp(2), mv(0, 2), mv(6, 2), mv(8, 2), mv(5), mv(4) )
GESTURE(H,  jp(0), mv(6, 2), jp(3), mv(5, 2), jp(2), mv(8, 2) )
GESTURE(I,  jp(1), mv(7, 2), jp(0), mv(2, 2), jp(6), mv(8, 2) )
GESTURE(J,  jp(2), mv(8, 2), mv(6, 2), mv(3) )
GESTURE(K,  jp(0), mv(6, 2), jp(3), mv(4), jp(2), mv(4), mv(8) )
GESTURE(L,  jp(0), mv(6, 2), mv(8, 2) )
GESTURE(M,  jp(0), mv(6, 2), mv(0, 2), mv(4), mv(7), jp(4), mv(2), mv(8, 2) )
GESTURE(N,  jp(0), mv(6, 2), jp(0), mv(8, 2), mv(2, 2) )
GESTURE(O,  jp(1), mv(0), mv(6, 2), mv(8, 2), mv(2, 2), mv(1) )
GESTURE(P,  jp(0), mv(6, 2), jp(0), mv(2, 2), mv(5), mv(3, 2) )
GESTURE(Q,  jp(1), mv(0), mv(6, 2), mv(8, 2), mv(2, 2), mv(1), jp(4), mv(8) )
GESTURE(R,  jp(0), mv(6, 2), jp(0), mv(2, 2), mv(5), mv(3, 2), jp(4), mv(8) )
GESTURE(S,  jp(2), mv(0, 2), mv(4), mv(5), mv(8), mv(6, 2) )
GESTURE(T,  jp(1), mv(7, 2), jp(0), mv(2, 2) )
GESTURE(U,  jp(0), mv(6, 2), mv(8, 2), mv(2, 2) )
GESTURE(V,  jp(0), mv(6, 2), mv(2, 2) )
GESTURE(W,  jp(0), mv(6, 2), mv(4), mv(1), mv(4), mv(8), mv(2, 2) )
GESTURE(X,  jp(0), mv(8, 2), jp(6), mv(2, 2) )
GESTURE(Y,  jp(0), mv(4), jp(2), mv(4), mv(7) )
GESTURE(Z,  jp(0), mv(2, 2), mv(6, 2), mv(8, 2) )

GESTURE(_1,  jp(2), mv(8, 2) )
GESTURE(_2,  jp(0), mv(2, 2), mv(5), mv(3, 2), mv(6), mv(8, 2) )
GESTURE(_3,  jp(0), mv(2, 2), mv(5), mv(3, 2), mv(5, 2), mv(8), mv(6, 2) )
GESTURE(_4,  jp(0), mv(3), mv(5, 2), jp(2), mv(8, 2) )
GESTURE(_5,  jp(0), mv(3), mv(5, 2), mv(8), mv(6, 2), jp(0), mv(2, 2) )
GESTURE(_6,  jp(2), mv(0, 2), mv(6, 2), mv(8, 2), mv(5), mv(3, 2) )
GESTURE(_7,  jp(3), mv(0), mv(2, 2), mv(8, 2) )
GESTURE(_8,  jp(1), mv(0), mv(3), mv(5, 2), mv(8), mv(6, 2), mv(3), mv(5, 2), mv(2), mv(1) )
GESTURE(_9,  jp(2), mv(0, 2), mv(3), mv(5, 2), jp(2), mv(8, 2), mv(6, 2) )
GESTURE(_0,  jp(1), mv(0), mv(6, 2), mv(8, 2), mv(2, 2), mv(1), jp(2), mv(6, 2) )

GESTURE(minus,  jp(3), mv(5, 2) )
GESTURE(plus,  jp(1), mv(7, 2), jp(3), mv(5, 2) )
GESTURE(comma,  jp(5), mv(7) )
GESTURE(slash,  jp(2), mv(6, 2) )
GESTURE(asterisk,  jp(0), mv(8, 2), jp(6), mv(2, 2), jp(1), mv(7, 2), jp(3), mv(5, 2) )

} // namespace Gestures

class Gesture 
{
   public:
      
      Gesture(const MotionCommandType *cmd);
      Gesture();
      
      void init();
      
      void setMotion(const MotionCommandType *cmd);
      const MotionCommandType *getMotion() const { return cmd_; }
      
      bool isComplete() const { return cmd_ && (curMotion_ >= nMotions_); }
      
      void setHorizontalSize(uint8_t hSize) { hSegSize_ = hSize/2; }
      void setVerticalSize(uint8_t vSize) { vSegSize_ = vSize/2; }
      
      void setSegmentDivision(uint8_t segDiv) { segDiv_ = segDiv; }
      uint8_t getSegmentDivision() const { return segDiv_; }
      
      uint16_t getXPos() const { return xPos_; }
      uint16_t getYPos() const { return yPos_; }
      
      void step();
      
   private:
      
      const MotionCommandType *cmd_;
      uint8_t nMotions_;
      uint8_t curMotion_;
      uint8_t hSegSize_, vSegSize_;
      int8_t hInc_, vInc_;
      uint8_t segDiv_;
      uint8_t nSteps_;
      uint8_t curStep_;
      uint16_t xPos_, yPos_;
};

class GestureString
{
   public:
      
      static constexpr uint8_t maxNGestures = 16;
      
      GestureString(uint16_t x0, uint16_t y0);
      
      GestureString();
      
      void setLoop(bool state) { loop_ = state; }
      
      void queueGesture(const MotionCommandType *cmd);
      
      uint8_t getNumQueuedGestures() const;
      
      Gesture &getGesture() { return gesture_; }
      const Gesture &getGesture() const { return gesture_; }
      
      bool isComplete() const;
      
      void step();
            
      uint16_t getXPos() const { return x0_ + gesture_.getXPos(); }
      uint16_t getYPos() const { return y0_ + gesture_.getYPos(); }
      
   private:
      
      void loadNextGesture();
      
   private:
      
      Gesture gesture_;
      
      const MotionCommandType *motionCommandBuffer_[maxNGestures];
      
      int16_t startGestureId_;
      int16_t curGestureId_;
      uint8_t bufferEnd_;
      
      uint16_t x0_;
      uint16_t y0_;
      
      bool loop_;
      
      uint8_t curWaitStep_;
};

} // namespace Pointata
