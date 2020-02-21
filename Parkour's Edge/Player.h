#include "Actor.h"

class Player : public Actor
{
public:
    Player(class Game* inGame,Actor* parent);
    void SetRespawnPos (Vector3 pos){mRespawn=pos;}
    Vector3 GetRespawnPos (){return mRespawn;}
private:
    class PlayerMove* mPM;
    class CameraComponent* mCaC;
    class CollisionComponent* mCC;
    Vector3 mRespawn;
    class HUD* mHUD;
};
