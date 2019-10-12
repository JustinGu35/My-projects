
#include "Actor.h"
#include <string>


class Door : public Actor
{
public:
    Door(class Game* inGame);
    ~Door();
    void UpdateTexture(std::string inDirectionState,std::string inDoorState);
    void setupDoor(std::string inDirectionState,std::string inDoorState,std::string inDestination);
    std::string getDirection() {return directionState;}
    std::string getState(){return doorState;}
    std::string getDestination();
private:
    class CollisionComponent* mCC;
    class SpriteComponent* mSC;
    std::string directionState;
    std::string doorState;
    std::string destination;
};
