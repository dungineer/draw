#include <game.h>


Game::Game(int screen_w, int screen_h) :
        context_("Breakout", screen_w, screen_h),
        levelGenerator_(0.0F, static_cast<float>(screen_w), static_cast<float>(screen_h), 0.0F) {

    using RM = ResourceManager;
    RM::loadTexture(Texture2D("resources/textures/block.png"), "block");
    RM::loadTexture(Texture2D("resources/textures/solid_block.png"), "solid_block");
    RM::loadTexture(Texture2D("resources/textures/ball.jpg"), "ball");
    RM::loadTexture(Texture2D("resources/textures/platform.jpg"), "platform");

    RM::loadShader(Shader("resources/shaders/vertex.glsl", "resources/shaders/fragment.glsl"), "sprite");

    RM::loadShape(std::make_shared<QuadShape>(), "quad");

    RM::buildSprite("quad", "solid_block", "solid_block");
    RM::buildSprite("quad", "block", "block");
    RM::buildSprite("quad", "platform", "platform");
    RM::buildSprite("quad", "ball", "ball");

    levelGenerator_.loadLevel("resources/levels/level0.txt");
    levelGenerator_.loadLevel("resources/levels/level1.txt");
    levelGenerator_.loadLevel("resources/levels/level2.txt");
}

int Game::exec() {
    ResourceManager::getShader("sprite")->use();

//     FIXME Hide this
    glm::mat4 projection = glm::ortho(0.0F, static_cast<float>(1024),
                                      static_cast<float>(768), 0.0F,
                                      -1.0F, 1.0F);
    int curr_program = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &curr_program);
    glUniformMatrix4fv(glGetUniformLocation(curr_program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//

    Engine engine;
    engine.addObjects(levelGenerator_.generateObjects(2));

    auto ball = std::make_unique<Ball>(glm::vec2(500.0F, 500.0F), glm::vec2{40.0F, 40.0F});
    ball->setVel({1.5F, -1.56F});
    engine.addDynamicObject(std::move(ball));

    auto platform = std::make_unique<Platform>(glm::vec2(context_.getWidth() / 2.0F, context_.getHeight() - 15.0F),
                                               glm::vec2{30.0F, 30.0F});
    engine.addDynamicObject(std::move(platform));

    while (context_.isOk()) {
        glClearColor(1.2F, 1.3F, 1.3F, 1.0F);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        engine.regInput(context_);
        engine.poll();

        context_.update();
    }

    return 0;
}
