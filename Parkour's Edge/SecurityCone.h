#include "Actor.h"


class SecurityCone : public Actor
{
public:
    const float CONE_HEIGHT =100;
    const float CONE_ANGLE = Math::Pi/6;
    SecurityCone(class Game* inGame, Actor* parent);
    void OnUpdate(float deltaTime);
    int GetColor(){return color;}
private:
    class MeshComponent* mMC;
    int color=0;
    float insideTimer=0;
    bool isInside;
    int SecurityDetected=-1;
};
