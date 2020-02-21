#include "HUD.h"
#include "Actor.h"
#include "Font.h"
#include "Shader.h"
#include "Texture.h"
#include <cmath>
#include <string>
#include "Game.h"
#include "Renderer.h"
#include "SecurityCamera.h"
#include "Player.h"

HUD::HUD(Actor* mOwner)
:UIComponent(mOwner)
{
    mFont=new Font();
    mFont->Load("Assets/Inconsolata-Regular.ttf");
    Game* mGame=mOwner->GetGame();
    mTimerText = mFont->RenderText("00:00.00");
    
    std::string coinNumber;
    if(mGame->Getcoins()<10)
    {
        coinNumber="0"+std::to_string(mGame->Getcoins());
    }
    else
    {
        coinNumber=std::to_string(mGame->Getcoins());
    }
    mCoinText=mFont->RenderText(coinNumber+"/55");
    mDisplayText=mFont->RenderText(mGame->GetDisplayText());
    
    arrow=mGame->GetRenderer()->GetTexture("Assets/RadarArrow.png");
    background=mGame->GetRenderer()->GetTexture("Assets/Radar.png");
    blip=mGame->GetRenderer()->GetTexture("Assets/Blip.png");\
    RadarPosition.Set(400.0f, -280.0f);
}

HUD::~HUD()
{
    mFont->Unload();
    delete mFont;
}

void HUD::Draw(class Shader* shader)
{
    DrawTexture(shader, mTimerText, Vector2(-420.0f, -325.0f));
    DrawTexture(shader, mCoinText, Vector2(-450.0f, -300.0f));
    if(DoDisplay)
    {
        DrawTexture(shader, mDisplayText, Vector2(0.0f, 0.0f));
    }
    DrawTexture(shader, background, RadarPosition);
    DrawTexture(shader, arrow, RadarPosition);
    
    Vector3 foward=mOwner->GetForward();
    Vector2 foward2D(foward.x,foward.y);
    float angle=Math::Atan2(foward2D.y,foward2D.x);
    Matrix3 rotation=Matrix3::CreateRotation(angle);
    Vector3 playerPos=(dynamic_cast<Player*>(mOwner))->GetPosition();
    Vector2 playerPos2D(playerPos.y,playerPos.x);
    
    std::vector<SecurityCamera*> SecurityCameras=mOwner->GetGame()->GetSecurityCameras();
    
    for(auto theSC : SecurityCameras)
    {
        Vector3 scPos=theSC->GetPosition();
        Vector2 scPos2D(scPos.y,scPos.x);
        Vector2 distanceVector=scPos2D-playerPos2D;
        float distance=distanceVector.Length();
        if(distance<=1500.0f)//radar range
        {
            distanceVector*=(1/1500.0f);
            distanceVector*=92.0f;//radius of radar
            distanceVector=Vector2::Transform(distanceVector,rotation);
            
            Vector3 scFoward=theSC->GetWorldForward();
            Vector2 scFoward2D(scFoward.y,scFoward.x);
            scFoward2D=Vector2::Transform(scFoward2D,rotation);
            float scAngle=Math::Atan2(scFoward2D.y,scFoward2D.x);
            
            DrawTexture(shader, blip, RadarPosition+distanceVector,1.0f,scAngle);
        }
    }
}

void HUD::Update(float deltaTime)
{
    Game* mGame=mOwner->GetGame();
    mGame->AddTime(deltaTime);
    mTimerText->Unload();
    delete mTimerText;
    int newtime= (int)round(mGame->GetTime()*100);
    int FF=newtime%100;
    int SS=(newtime/100)%60;
    int MM=(newtime/100)/60;
    
    std::string ff;
    std::string ss;
    std::string mm;
    
    if(FF==0)
    {
        ff="00";
    }
    else if(FF<10)
    {
        ff="0"+std::to_string(FF);
    }
    else
    {
        ff=std::to_string(FF);
    }
    
    if(SS==0)
    {
        ss="00";
    }
    else if(SS<10)
    {
        ss="0"+std::to_string(SS);
    }
    else
    {
        ss=std::to_string(SS);
    }
    
    if(MM==0)
    {
        mm="00";
    }
    else if(MM<10)
    {
        mm="0"+std::to_string(MM);
    }
    else
    {
        mm=std::to_string(MM);
    }
    
    std::string display=mm+"::"+ss+"."+ff;
    mTimerText = mFont->RenderText(display);
    
    if(coinAdded==true)
    {
        coinAdded=false;
        std::string coinNumber;
        if(mGame->Getcoins()<10)
        {
            coinNumber="0"+std::to_string(mGame->Getcoins());
        }
        else
        {
            coinNumber=std::to_string(mGame->Getcoins());
        }
        mCoinText->Unload();
        delete mCoinText;
        mCoinText=mFont->RenderText(coinNumber+"/55");
    }
    
    float displayTimer=mGame->GetTextTimer();
    displayTimer+=deltaTime;
    mGame->SetTextTimer(displayTimer);
    
    if(displayTimer<=5.0f && !mGame->GetDisplayText().empty())
    {
        DoDisplay=true;
    }
    else
    {
        DoDisplay=false;
    }
    
    
}

void HUD::addCoin()
{
    mOwner->GetGame()->Addcoins();
    coinAdded=true;
}

void HUD::ChangeTextTexture()
{
    mDisplayText=mFont->RenderText(mOwner->GetGame()->GetDisplayText());
}
