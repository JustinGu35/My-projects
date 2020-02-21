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
    
    void SetText(std::string inT){mText=inT;}
    std::string GetText(){return mText;}
private:
    class MeshComponent* mMC;
    class CollisionComponent* mCC;
    bool isActive=false;
    std::string mLevelString;
    std::string mText;
};
