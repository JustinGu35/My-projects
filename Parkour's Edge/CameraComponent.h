#include "Component.h"
#include "Math.h"

class CameraComponent : public Component
{
public:
    CameraComponent(class Actor* mOwner);
    void Update(float deltaTime);
    void SetPitchSpeed(float speed){mPitchSpeed=speed;}
    float GetPitchSpeed(){return mPitchSpeed;}
private:
    Vector3 idealPosition();
    
    const float HDIST=60;
    const float VDIST=70;
    const float TARGETDIST=50;
    Vector3 velocity=Vector3::Zero;
    float mPitchAngle=0.0f;
    float mPitchSpeed=0.0f;
    
    float mRollAngle=0.0f;
};
