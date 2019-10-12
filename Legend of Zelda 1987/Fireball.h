#include "Actor.h"

class Fireball :public Actor
{
public:
    Fireball(class Game* inGame);
    void OnUpdate(float deltaTime);
    void ChangeTexture(std::string inTexture);
private:
    class SpriteComponent* mSC;
    class CollisionComponent* mCC;
    class MoveComponent* mMC;
    float timeElapsed;
};
