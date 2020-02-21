#include "MoveComponent.h"
#include "CollisionComponent.h"
enum class MoveState
{
    OnGround,
    Jump,
    Falling,
    WallClimb,
    WallRun
};


class PlayerMove : public MoveComponent
{
public:
    PlayerMove(class Actor* inOwner);
    ~PlayerMove();
    void Update(float deltaTime);
    void ProcessInput(const Uint8* keyState);
    void OnLapChange(int newLap);
    void ChangeState(MoveState inMoveState){mCurrentState=inMoveState;}
    void PhysicsUpdate(float deltaTime);
    void AddForce(const Vector3& force);
    void FixXYVelocity();
    
    bool CanWallClimb(CollSide inState);
    bool CanWallRun(CollSide inState);
    MoveState GetCurrentState(){return mCurrentState;}
    CollSide GetCollidingSide(){return collidingSide;}
    Vector3 offsetRecorder;
    void SetVelocityZero(){mVelocity=Vector3::Zero;}
    void SetPendingForceZero(){mPendingForces=Vector3::Zero;}
protected:
    void UpdateOnGround(float deltaTime);
    void UpdateJump(float deltaTime);
    void UpdateFalling(float deltaTime);
    void UpdateWallClimb(float deltaTime);
    void UpdateWallRun(float deltaTime);
    CollSide FixCollision(class CollisionComponent* self, class CollisionComponent* block);
private:
    MoveState mCurrentState;
    bool lastSpace=false;
    Vector3 mVelocity;
    Vector3 mAcceleration;
    Vector3 mPendingForces;
    float mMass=1.0f;
    Vector3 mGravity;
    Vector3 mJumpForce;
    Vector3 mWallClimbForce;
    Vector3 mWallRunForce;
    float mWallRunTimer=0;
    float mWallClimbTimer;
    CollSide collidingSide;
    
    int mRunningSFX;
    
};

