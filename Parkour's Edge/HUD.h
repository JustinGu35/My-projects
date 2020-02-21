#include "UIComponent.h"

class HUD : public UIComponent
{
public:
    HUD(class Actor* owner);
    ~HUD();
    void Update(float deltaTime);
    void Draw(class Shader* shader);
    
    void addCoin();
    void ChangeTextTexture();
private:
    class Font* mFont;
    class Texture* mTimerText;
    
    bool coinAdded=false;
    class Texture* mCoinText;
    
    class Texture* mDisplayText;
    bool DoDisplay=false;
    
    class Texture* arrow;
    class Texture* background;
    class Texture* blip;
    Vector2 RadarPosition;
};
