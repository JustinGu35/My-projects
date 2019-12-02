#include "Actor.h"

enum class CameraState
{
    StartToEnd,
    EndToStart,
    PausedAtStart,
    PausedAtEnd,
    Disrupted
};


class SecurityCamera : public Actor
{
public:
    SecurityCamera(class Game* inGame, Actor* parent);
    ~SecurityCamera();
    void SetQs(Quaternion start,Quaternion end){startQ=start;endQ=end;}
    void SetTs(float interp,float pause){interpT=interp;pauseT=pause;}
    void OnUpdate(float deltaTime);
private:
    class MeshComponent* mMC;
    class SecurityCone* mSC;
    Quaternion startQ;
    Quaternion endQ;
    float interpT;
    float pauseT;
    
    CameraState mCameraState=CameraState::StartToEnd;
    CameraState mLastState;
    float interpTimer=0.0;
    float pauseTimer=0.0;
    SecurityCone* mChild;
    int CameraRotate=-1;
    
    float DistanceToPlayer();
    void SetVolume(int channel);
};
