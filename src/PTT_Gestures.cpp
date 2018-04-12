namespace Pointata {

uint8_t points[][] = {
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

namespace MotionType {
   constexpr uint8_t Stay = 0;
   constexpr uint8_t Jump = 1;
   constexpr uint8_t Move = 2;
};

// Gestures
//
namespace Gestures {
   
inline
constexpr MotionCommand st(uint8_t pointId) 
{
   MotionCommand c;
   
   c.pointId_ = pointId;
   c.motionType_ = MotionType::Stay;
   c.scale_ = 0;
   
   return c;
}

inline
constexpr MotionCommand jp(uint8_t pointId) 
{
   MotionCommand c;
   
   c.pointId_ = pointId;
   c.motionType_ = MotionType::Jump;
   c.scale_ = 0;
   
   return c;
}

inline
constexpr MotionCommand mv(uint8_t pointId, uint8_t scale = 1) 
{
   MotionCommand c;
   
   c.pointId_ = pointId;
   c.motionType_ = MotionType::Move;
   c.scale_ = scale;
   
   return c;
}
   
MotionCommand A[] = { jp(6), mv(0, 2), mv(2, 2), mv(8, 2), jp(3), mv(5, 2) };
MotionCommand B[] = { jp(0), mv(6, 2), jp(0), mv(2, 2), mv(4), mv(3), mv(5, 2), mv(8), mv(6, 2) };
MotionCommand C[] = { jp(2), mv(0, 2), mv(6, 2), mv(8, 2) };
MotionCommand D[] = { jp(2), mv(7, 2), jp(0), mv(2, 2), mv(8, 2), mv(6, 2) };
MotionCommand E[] = { jp(2), mv(0, 2), mv(3), mv(5, 2), mv(3, 2), mv(6), mv(8, 2) };
MotionCommand F[] = { jp(2), mv(0, 2), mv(6, 2), jp(3), mv(5, 2) };
MotionCommand G[] = { jp(2), mv(0, 2), mv(6, 2), mv(8, 2), mv(5), mv(4) };
MotionCommand H[] = { jp(0), mv(6, 2), jp(3), mv(5, 2), jp(2), mv(8, 2) };
MotionCommand I[] = { jp(1), mv(7, 2), jp(0), mv(2, 2), jp(6), mv(8, 2) };
MotionCommand J[] = { jp(2), mv(8, 2), mv(6, 2), mv(3) };
MotionCommand K[] = { jp(0), mv(6, 2), jp(3), mv(4), jp(2), mv(4), mv(8) };
MotionCommand L[] = { jp(0), mv(6, 2), mv(8, 2) };
MotionCommand M[] = { jp(0), mv(6, 2), mv(0, 2), mv(4), mv(7), jp(4), mv(2), mv(8, 2) };
MotionCommand N[] = { jp(0), mv(6, 2), jp(0), mv(8, 2), mv(2, 2) };
MotionCommand O[] = { jp(1), mv(0), mv(6, 2), mv(8, 2), mv(2, 2), mv(1) };
MotionCommand P[] = { jp(0), mv(6, 2), jp(0), mv(2, 2), mv(5), mv(3, 2) };
MotionCommand Q[] = { jp(1), mv(0), mv(6, 2), mv(8, 2), mv(2, 2), mv(1), jp(4), mv(8) };
MotionCommand R[] = { jp(0), mv(6, 2), jp(0), mv(2, 2), mv(5), mv(3, 2), jp(4), mv(8) };
MotionCommand S[] = { jp(2), mv(0, 2), mv(4), mv(5), mv(8), mv(6, 2) };
MotionCommand T[] = { jp(1), mv(7, 2), jp(0), mv(2, 2) };
MotionCommand U[] = { jp(0), mv(6, 2), mv(8, 2), mv(2, 2) };
MotionCommand V[] = { jp(0), mv(6, 2), mv(2, 2) };
MotionCommand W[] = { jp(0), mv(6, 2), mv(4), mv(1), mv(4), mv(8), mv(2, 2) };
MotionCommand X[] = { jp(0), mv(8, 2), jp(6), mv(2, 2) };
MotionCommand Y[] = { jp(0), mv(4), jp(2), mv(4), mv(7) };
MotionCommand Z[] = { jp(0), mv(2, 2), mv(6, 2), mv(8, 2) };

MotionCommand _1[] = { jp(2), mv(8, 2) };
MotionCommand _2[] = { jp(0), mv(2, 2), mv(5), mv(3, 2), mv(6), mv(8, 2) };
MotionCommand _3[] = { jp(0), mv(2, 2), mv(5), mv(3, 2), mv(5, 2), mv(8), mv(6, 2) };
MotionCommand _4[] = { jp(0), mv(3), mv(5, 2), jp(2), mv(8, 2) };
MotionCommand _5[] = { jp(0), mv(3), mv(5, 2), mv(8), mv(6, 2), jp(0), mv(2, 2) };
MotionCommand _6[] = { jp(2), mv(0, 2), mv(6, 2), mv(8, 2), mv(5), mv(3, 2) };
MotionCommand _7[] = { jp(3), mv(0), mv(2, 2), mv(8, 2) };
MotionCommand _8[] = { jp(1), mv(0), mv(3), mv(5, 2), mv(8), mv(6, 2), mv(3), mv(5, 2), mv(2), mv(1) };
MotionCommand _9[] = { jp(2), mv(0, 2), mv(3), mv(5, 2), jp(2), mv(8, 2), mv(6, 2) };
MotionCommand _0[] = { jp(1), mv(0), mv(6, 2), mv(8, 2), mv(2, 2), mv(1), jp(2), mv(6, 2) };

MotionCommand minus[] = { jp(3), mv(5, 2) };
MotionCommand plus[] = { jp(1), mv(7, 2), jp(3), mv(5, 2) };
MotionCommand comma[] = { jp(5), mv(7) };
MotionCommand slash[] = { jp(2), mv(6, 2) };
MotionCommand asterisk[] = { jp(0), mv(8, 2), jp(6), mv(2, 2), jp(1), mv(7, 2), jp(3), mv(5, 2) };

struct MotionCommandList {
   const MotionCommand *cmd_;
   uint8_t nMotions_;
} // namespace Gestures

#define PTT_MCL(NAME) MotionCommandList{ NAME, sizeof(NAME) }

class Gesture 
{
   public:
      
      MotionGesture(MotionCommandList mcl)
         :  mcl_(mcl),
            curMotion_(0)
            hSegSize_(100),
            vSegSize_(200),
            hInc_(1),
            vInc_(1),
            segDiv_(16),
            curStep_(0)
            xPos_(0),
            yPos_(0)
      {}
      
      MotionGesture()
         :  MotionGesture(MotionCommandList{nullptr, 0})
      {}
      
      void init() {
         curMotion_ = 0;
         curStep_ = 0;
         xPos_ = 0;
         yPos_ = 0;
      }
      
      void setMotionCommandList(MotionCommandList mcl) {
         this->init();
         mcl_ = mcl;
      }
      
      bool isComplete() const { return curMotion_ >= mcl_.nMotions_; }
      
      void setHorizontalSize(uint8_t hSize) { hSegSize_ = hSize/2; }
      void setVerticalSize(uint8_t vSize) { vSegSize_ = vSize/2; }
      
      void setSegmentDivision(uint8_t segDiv) { segDiv_ = segDiv; }
      
      uint16_t getXPos() const { return xPos_; }
      uint16_t getYPos() const { return yPos_; }
      
      void step() {
         
         while(!this->isComplete()) {
            
            assert(mcl_.cmd_);
            
            const auto &motionCommand = mcl_.cmd_[curMotion_];
            
            switch(motionCommand.motionType_) {
               
               case MotionType::Stay:
                  if(curStep_ < segDiv_) {
                     ++curStep_;
                     goto stepDone;
                  }
                  break;
                  
               case MotionType::Jump:
                  xPos_ = points[motionCommand.point_][0]*hSegSize_;
                  yPos_ = points[motionCommand.point_][1]*vSegSize_;
                  break;
                  
               case MotionType::Move:
                  
                  if(curStep_ == 0) {
                     uint8_t xTargetPos = points[motionCommand.point_][0]*hSegSize_;
                     uint8_t yTargetPos = points[motionCommand.point_][1]*hSegSize_;
                     
                     int16_t xDist = xTargetPos - xPos_;
                     int16_t yDist = yTargetPos - yPos_;
                     
                     hInc_ = motionCommand.scale_*xDist/segDiv_;
                     vInc_ = motionCommand.scale_*yDist/segDiv_;
                  }
                  
                  if(curStep_ >= segDiv_) {
                     
                     // If the segment is not perfectly finished, we jump
                     // to the exact end point
                     //
                     xPos_ = points[motionCommand.point_][0]*hSegSize_;
                     yPos_ = points[motionCommand.point_][1]*hSegSize_;
                  }
                  else {
                     xPos_ += hInc_;
                     yPos_ += vInc_;
                     goto stepDone;
                  }
                  break;
            }
            
            ++curMotion_;
            curStep_ = 0;
         }
            
         stepDone:
      }
      
   private:
      
      MotionCommandList mcl_;
      uint8_t curMotion_;
      uint8_t hSegSize_, vSegSize_;
      int8_t hInc_, vInc_;
      uint8_t segDiv_;
      uint8_t curStep_;
      uint16_t xPos_, yPos_;
};

class GestureString
{
   public:
      
      static constexpr uint8_t maxNGestures = 16;
      
      GestureString(uint16_t x0, uint16_t y0) 
         :  startGestureId_(0),
            curGestureId_(0),
            bufferEnd_(0),
            x0_(x0),
            y0_(y0),
            loop_(false)
      {}
      
      GestureString() : GestureString(0, 0) {}
      
      void setLoop(bool state) { loop_ = state; }
      
      void queueGesture(MotionCommandList gesture) {
         
         if(bufferEnd_ >= maxNGestures) {
            // wrap around
            //
            bufferEnd_ = 1;
            gestureBuffer_[0] = gesture;
         }
         else {
            
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
                  maxNGestures = 0;
               }
               gesture_->setGesture(gestureBuffer_[curGestureId_]);
            }
            
            gestureBuffer_[bufferEnd_] = gesture;
            
            ++bufferEnd_;
         }
      }
      
      void isComplete() const {
         
         if(gesture_->isComplete()) {
            if(!loop_) {
               if(curGestureId_ + 1 == bufferEnd_)) { return true; }
            }
         }
         
         if(curGestureId_ != bufferEnd_) { return false; }
         
         return true;
      }
      
      void step() {
         
         if(this->isComplete()) { return; }
         
         if(gesture_->isComplete()) {
            this->loadNextGesture();
         }
         
         gesture_->step();
      }
            
      uint8_t getXPos() const { return x0_ + gesture_.getXPos(); }
      uint8_t getYPos() const { return y0_ + gesture_.getYPos(); }
      
   private:
      
      void loadNextGesture() {
         
         ++curGestureId_;
         
         if(curGestureId_ >= bufferEnd_) {
            
            // Wrap in case of loop
            //
            curGestureId_ = startGestureId_;
         }
         gesture_.setMotionCommandList(gestureBuffer_[curGestureId_]);
      }
      
   private:
      
      Gesture gesture_;
      
      MotionCommandList gestureBuffer_[maxNGestures];
      
      uint8_t startGestureId_;
      uint8_t curGestureId_;
      uint8_t bufferEnd_;
      
      uint16_t x0_;
      uint16_t y0_;
      
      bool loop_;
};


} // namespace Pointata
