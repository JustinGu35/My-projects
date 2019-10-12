#include "Component.h"
#include <string>
#include <functional>

class EnemyComponent : public Component
{
public:
    EnemyComponent(class Actor* owner);
    ~EnemyComponent();
    void TakeDamage(int amount);
    void SetOnDeath(std::function<void()> onDeath);
    void SetOnTakeDamage(std::function<void()> onTakeDamage);
    int getDamage(){return damage;}
    void Update(float deltaTime);
    int GetHP(){return HitPoint;}
    void SetHP(int amount){HitPoint=amount;}
    void SetDamage(int amount){damage=amount;}
private:
    std::string existRoom;
    int HitPoint;
    int damage;
    std::function<void()> mOnDeath;
    std::function<void()> mOnTakeDamage;
    float invulnerabilityTimer;
};
