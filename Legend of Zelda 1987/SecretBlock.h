#include "Actor.h"
#include <string>
#include "Math.h"


class SecretBlock : public Actor
{
public:
    SecretBlock(class Game* inGame);
    ~SecretBlock();
    void setDirection(std::string input){direction=input;}
    std::string getDirection(){return direction;}
    void setOriginalPosition(Vector2 input){originalPosition=input;}
    Vector2 const getOriginalPosition(){return originalPosition;}
private:
    class CollisionComponent* mCC;
    class SpriteComponent* mSC;
    std::string direction;
    Vector2 originalPosition;
};
