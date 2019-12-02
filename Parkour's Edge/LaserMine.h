#include "Actor.h"

class LaserMine : public Actor
{
public:
    LaserMine(class Game* inGame,Actor* parent);
private:
    class MeshComponent* mMC;
    class LaserComponent* mLC;
};
