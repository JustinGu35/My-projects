#include "MoveComponent.h"
#include "Math.h"

class PlayerMove : public MoveComponent
{
public:
    const int TILE_WIDTH=32;
    const int SPEED=130;
    PlayerMove(class Actor* owner);
    void Update(float deltaTime);
    void ProcessInput(const Uint8* keyState);
    void UpdateSword();
private:
    Vector2 direction;
    int facing;//0 is up, 1 is left, 2 is down, 3 is right
    class Sword* mSword;
    float attackTimer;
    bool attacking;
    bool isSpacePressed;
};
