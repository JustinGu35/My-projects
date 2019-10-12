
#include "Actor.h"


class Collider : public Actor
{
public:
    Collider(class Game* inGame);
    ~Collider();
    void SetDimension(int inWidth,int inHeight);
    class CollisionComponent* mCC;
};
