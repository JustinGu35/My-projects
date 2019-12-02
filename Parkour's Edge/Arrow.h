#include "Actor.h"

class Arrow : public Actor
{
public:
    Arrow(class Game* inGame, Actor* parent);
    void OnUpdate(float deltaTime);
private:
    class MeshComponent* mMC;
};
