#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
     public:
        Tema1();
        ~Tema1();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void ResetDuck();

     protected:
        float wingX, wingY;
        glm::mat3 modelMatrix;
        float angularStep;
        int maximumX, maximumY;
        int currentSideWing1, currentSideWing2, movementTimeWing1, movementTimeWing2;
        int bullets, lives;
        int moveX, moveY;
        float bodySide, headSide, beakSide, wingSide;
        float angle;
        float time;
        int valueY, valueX;
        float hypotenuse;
        int rectangleAX, rectangleAY, rectangleBX, rectangleBY, rectangleCX, rectangleCY;
        int rectangleDX, rectangleDY;
        int rectangleAXNew, rectangleAYNew, rectangleBXNew, rectangleBYNew;
        int rectangleCXNew, rectangleCYNew, rectangleDXNew, rectangleDYNew;
        int shot;
        int currentScoreScale;
        int ducks;
        int targetX, targetY;
        float red, green, blue;
        int win, lose;
        int moveSnow;
        int nextLevel;
        int nextLevelTransition;
        int level;

    };
}   // namespace m1
