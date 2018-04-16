#include "PTT_Types.hpp"

#include <cstdint>
#include <cassert>

namespace Pointata {
   
uint8_t points[][2] = {
   { 0, 0 },
   { 1, 0 },
   { 2, 0 },
   
   { 0, 1 },
   { 1, 1 },
   { 2, 1 },
   
   { 0, 2 },
   { 1, 2 },
   { 2, 2 }
};

namespace Motion {
   constexpr uint8_t Stay = 0;
   constexpr uint8_t Jump = 1;
   constexpr uint8_t Move = 2;
};

class MotionCommand
{
   public:
      
      explicit constexpr MotionCommand(MotionCommandType data = 0) : data_(data) {}
      explicit constexpr MotionCommand(MotionCommandType pointId, 
                                       MotionCommandType motion,
                                       MotionCommandType scale)
         :  data_(pointIdBits(pointId) | motionBits(motion) | scaleBits(scale))
      {
      }
      
      static constexpr MotionCommandType allBitsSet = 0xFF;
      
      static constexpr MotionCommandType pointIdBitmask = 0x0F;
      static constexpr MotionCommandType pointIdShift = 0;
      
      static constexpr MotionCommandType motionShift = 4;
      static constexpr MotionCommandType motionBitmask = 0x30;
      
      static constexpr MotionCommandType scaleShift = 6;
      static constexpr MotionCommandType scaleBitmask = 0xC0;
      
      void setPointId(MotionCommandType pointId) {
         data_ = (data_ & (~pointIdBitmask)) | pointIdBits(pointId);
      }
      
      constexpr MotionCommandType getPointId() const { return data_ & pointIdBitmask; }
      
      void setMotion(MotionCommandType motion) {
         data_ = (data_ & (~motionBitmask)) | motionBits(motion);
      }
      
      constexpr MotionCommandType getMotion() const {
         return (data_ & motionBitmask) >> motionShift;
      }
      
      void setScale(MotionCommandType scale) {
         data_ = (data_ & (~scaleBitmask)) | scaleBits(scale);
      }
      
      constexpr MotionCommandType getScale() const {
         return (data_ & scaleBitmask) >> scaleShift;
      }
      
      constexpr MotionCommandType getData() const { return data_; }
      
   private:
      
      static constexpr MotionCommandType pointIdBits(MotionCommandType pointId) {
         return ((pointId << pointIdShift) & pointIdBitmask);
      }
      
      static constexpr MotionCommandType motionBits(MotionCommandType motion) {
         return ((motion << motionShift) & motionBitmask);
      }
      
      static constexpr MotionCommandType scaleBits(MotionCommandType scale) {
         return ((scale << scaleShift) & scaleBitmask);
      }
      
   private:
   
      MotionCommandType data_;
};

// Gestures
//
namespace Gestures {
   
inline
constexpr MotionCommandType st(uint8_t pointId) 
{
   return MotionCommand(pointId, Motion::Stay, 0).getData();
}

inline
constexpr MotionCommandType jp(uint8_t pointId)
{
   return MotionCommand(pointId, Motion::Jump, 0).getData();
}

inline
constexpr MotionCommandType mv(uint8_t pointId, uint8_t scale = 1) 
{
   return MotionCommand(pointId, Motion::Move, scale).getData();
}

} // namespace Gestures
} // namespace Pointata

#define GESTURE_IMPLEMENTATION
#include "PTT_Gestures.hpp"

namespace Pointata {

   Gesture
      ::Gesture(const MotionCommandType *cmd)
   :  cmd_(cmd),
      curMotion_(0),
      hSegSize_(100),
      vSegSize_(200),
      hInc_(1),
      vInc_(1),
      segDiv_(16),
      nSteps_(segDiv_),
      curStep_(0),
      xPos_(0),
      yPos_(0)
{
   if(cmd_) {
      nMotions_ = cmd_[0];
      curMotion_ = 1;
   }
}
      
   Gesture
      ::Gesture()
   :  Gesture(nullptr)
{}
      
void
   Gesture
      ::init() 
{
   curMotion_ = 1;
   curStep_ = 0;
   xPos_ = 0;
   yPos_ = 0;
}

void 
   Gesture
      ::setMotion(const MotionCommandType * cmd)
{   
   cmd_ = cmd;
   
   if(cmd_) {
      nMotions_ = cmd_[0];
   }
   this->init();
}
      
void 
   Gesture
      ::step()
{   
   PTT_LOG("Gesture::step()")
   
   while(!this->isComplete()) {
      
      assert(cmd_);
      
      MotionCommand motionCommand(cmd_[curMotion_]);
      
      PTT_LOG("motionCommand: pointId = " << (int)motionCommand.getPointId()
         << ", motion = " << (int)motionCommand.getMotion() 
         << ", scale = " << (int)motionCommand.getScale())
      
      PTT_LOG("curStep: " << (int)curStep_ << ", nSteps: " << (int)nSteps_)
            
      switch(motionCommand.getMotion()) {
         
         case Motion::Stay:
            if(curStep_ < nSteps_) {
               ++curStep_;
               goto stepDone;
            }
            break;
            
         case Motion::Jump:
            
            // After a jump, we wait some cycles
            //
            if(curStep_ == 0) {
               xPos_ = points[motionCommand.getPointId()][0]*hSegSize_;
               yPos_ = points[motionCommand.getPointId()][1]*vSegSize_;
               
               PTT_LOG("Jumping to position " << (int)xPos_
                  << ", " << (int)yPos_)
            }
            
            if(curMotion_ > 1) {
               if(curStep_ < nSteps_) {
                  ++curStep_;
                  goto stepDone;
               }
            }
            else {
               // Skip wait on first jump of new motion
               //
               ++curMotion_;
               curStep_ = 0;
               goto stepDone;
            }
            break;
            
         case Motion::Move:
            
            if(curStep_ == 0) {
               uint8_t xTargetPos = points[motionCommand.getPointId()][0]*hSegSize_;
               uint8_t yTargetPos = points[motionCommand.getPointId()][1]*vSegSize_;
               
               int16_t xDist = xTargetPos - xPos_;
               int16_t yDist = yTargetPos - yPos_;
               
               nSteps_ = segDiv_*motionCommand.getScale();
               
               hInc_ = xDist/nSteps_;
               vInc_ = yDist/nSteps_;
            }
            
            if(curStep_ >= nSteps_) {
               
               // If the segment is not perfectly finished, we jump
               // to the exact end point
               //
               xPos_ = points[motionCommand.getPointId()][0]*hSegSize_;
               yPos_ = points[motionCommand.getPointId()][1]*vSegSize_;
            }
            else {
               xPos_ += hInc_;
               yPos_ += vInc_;
               ++curStep_;
               goto stepDone;
            }
            
            break;
      }
      
      ++curMotion_;
      curStep_ = 0;
   }
      
   stepDone:
      return;
}

   GestureString
      ::GestureString(uint16_t x0, uint16_t y0) 
   :  startGestureId_(-1),
      curGestureId_(-1),
      bufferEnd_(0),
      x0_(x0),
      y0_(y0),
      loop_(false)
{}
   
   GestureString
      ::GestureString() 
   : GestureString(0, 0)
{}
      
void 
   GestureString
      ::queueGesture(const MotionCommandType *cmd)
{
   if(bufferEnd_ >= maxNGestures) {
      // wrap around
      //
      bufferEnd_ = 0;
   }
   else {
      
      // Check if we already overwrite registered gestures
      //
      if(bufferEnd_ == startGestureId_) {
         
         ++startGestureId_;
         if(startGestureId_ >= maxNGestures) {
            startGestureId_ = 0;
         }
      }
      
      // If we overwrite the gesture that is currently 
      // processed, we go to the next gesture and replace 
      // the current one
      //
      if(bufferEnd_ == curGestureId_) {
         ++curGestureId_;
         if(curGestureId_ >= maxNGestures) {
            curGestureId_ = 0;
         }
         gesture_.setMotion(motionCommandBuffer_[curGestureId_]);
      }
   }
   
   if(startGestureId_ < 0) { startGestureId_ = 0; }
   
   motionCommandBuffer_[bufferEnd_] = cmd;
      
   PTT_LOG("Gesture registered at " << (int)bufferEnd_)
   
   ++bufferEnd_;
}

bool 
   GestureString
      ::isComplete() const
{   
   if(gesture_.isComplete()) {
      if(!loop_) {
         if(curGestureId_ + 1 == bufferEnd_) { return true; }
      }
   }
   
   if(curGestureId_ != bufferEnd_) { return false; }
   
   return true;
}

void 
   GestureString
      ::step()
{   
   PTT_LOG("GestureString::step()")
   
   if(!gesture_.getMotion()) {
      this->loadNextGesture();
      if(!gesture_.getMotion()) { 
         PTT_LOG("Unable to load gesture")
         return; 
      }
   }
   
   if(this->isComplete()) { 
      PTT_LOG("All gestures complete")
      return; 
   }
   
   if(gesture_.isComplete()) {
      this->loadNextGesture();
   }
   
   // Have a short wait between gestures
   //
   if(curWaitStep_ < 2*gesture_.getSegmentDivision()) {
      
      PTT_LOG("Waiting between gestures")
      ++curWaitStep_;
      return;
   }
   
   gesture_.step();
}
      
void 
   GestureString
      ::loadNextGesture()
{   
   bool firstUse = (curGestureId_ == -1);
   
   if(firstUse) {
      PTT_LOG("First use")
   }
   
   ++curGestureId_;
   
   if(curGestureId_ >= bufferEnd_) {
      
      // Wrap in case of loop
      //
      curGestureId_ = startGestureId_;
   }
   
   if(this->getNumQueuedGestures() == 0) { 
      PTT_LOG("No gestures queued");
      return; 
   } 
   
   PTT_LOG("Loading gesture " << curGestureId_)
   
   gesture_.setMotion(motionCommandBuffer_[curGestureId_]);
   
   // Prevent wait on first use
   //
   if(firstUse) {
      curWaitStep_ = (uint8_t)-1;
   }
   else {
      curWaitStep_ = 0;
   }
}

uint8_t  
   GestureString
      ::getNumQueuedGestures() const
{
   if(startGestureId_ == bufferEnd_) { return 0; }
   else if(startGestureId_ < bufferEnd_) { return bufferEnd_ - startGestureId_; }
   
   return (maxNGestures - startGestureId_) + bufferEnd_;
}

} // namespace Pointata
