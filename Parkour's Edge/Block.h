#include "Actor.h"

class Block : public Actor
{
public:
    Block(class Game* inGame,Actor* parent);
    ~Block();
    void SetMirror(bool inM){isMirror=inM;}
    bool GetMirror(){return isMirror;}
    void SetRotate(bool inR){isRotate=inR;}
    bool GetRotate(){return isRotate;}
    void OnUpdate(float deltaTime);
private:
    class MeshComponent* mMC;
    class CollisionComponent* mCC;
    bool isMirror=false;
    bool isRotate=false;
};
