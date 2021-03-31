#ifndef DRAW_GAME_H
#define DRAW_GAME_H


#include <resource_manager.h>
#include <context_handler.h>
#include <level_generator.h>
#include <colors.h>
#include <ball.h>
#include <platform.h>
#include <engine.h>


class Game {
public:
    Game(int screen_w, int screen_h);

    int exec();

private:
    ContextHandler context_;
    LevelGenerator levelGenerator_;
};


#endif //DRAW_GAME_H
