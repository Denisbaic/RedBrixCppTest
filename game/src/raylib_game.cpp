#include "Implementation/ArcherGame.h"
#include "Implementation/EngineECS.h"

int main(void)
{
    ArcherGame game;
    EngineECS engine;
    engine.PreInit(EngineECS_Config{ 800,600,"HelloRedBrix","" , {{"RedArcher","resources\\RedArcher.png"},{"BlueArcher","resources\\BlueArcher.png"}}, &game});
    game.PreInit({});

    engine.GameLoop();

    return 0;
}