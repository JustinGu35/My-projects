#include "LaserMine.h"
#include "Game.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "LaserComponent.h"

LaserMine::LaserMine(Game* inGame,Actor* parent)
:Actor(inGame,parent)
{
    mMC= new MeshComponent(this);
    mMC->SetMesh(mGame->GetRenderer()->GetMesh("Assets/LaserMine.gpmesh"));
    mLC=new LaserComponent(this);
}
