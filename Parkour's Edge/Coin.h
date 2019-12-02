#include "Actor.h"

class Coin : public Actor
{
public:
    Coin(class Game* inGame, Actor* parent);
    void OnUpdate(float deltaTime);
private:
    class MeshComponent* mMC;
    class CollisionComponent* mCC;
};
