#include "Actor.h"
#include <string>

class Checkpoint :public Actor
{
public:
    Checkpoint(class Game* inGame,Actor* parent);
    void SetActive(bool inA);
    bool GetActive(){return isActive;}
    void SetLevel(std::string inS){mLevelString=inS;}
    std::string GetLevel(){return mLevelString;}
private:
    class MeshComponent* mMC;
    class CollisionComponent* mCC;
    bool isActive=false;
    std::string mLevelString;
};
