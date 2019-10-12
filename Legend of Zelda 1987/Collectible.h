#include <functional>
#include "Component.h"

class Collectible : public Component
{
public:
    Collectible(class Actor* owner);
    void SetOnCollect(std::function<void()> onCollect);
    void Update(float deltaTime);
private:
    std::function<void()> mOnCollect;
};
