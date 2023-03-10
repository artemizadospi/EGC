#pragma once

#include "components/simple_scene.h"
#include "lab_m1/Tema2/lab_camera.h"


namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
     public:
        struct ViewportArea
        {
            ViewportArea() : x(0), y(0), width(1), height(1) {}
            ViewportArea(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        Tema2();
        ~Tema2();

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

        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, int viewPort);
        float TringleArea(glm::vec3 a, glm::vec3 b, glm::vec3 c);
        bool InsideTriangle(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c);
        void RenderScene(float deltaTimeSeconds, int viewPort);
        void RenderCars(int rivals, float colorR, float colorG, float colorB, int indexRival, int direction, int viewPort, std::vector<glm::vec3> indices);
        glm::mat4 RenderTreesIn(float scaleX, float scaleY, float scaleZ, int pointIndex, glm::vec3 p, int trunk);
        glm::mat4 RenderTreesOut(float scaleX, float scaleY, float scaleZ, int pointIndex, glm::vec3 p, int trunk);
        bool CheckCarOnTrack(glm::vec3 targetPosition);
        bool CheckCarCollision();

    protected:
        ViewportArea miniViewportArea;
        float raport;
        implemented::CameraTema2* camera;
        implemented::CameraTema2* cameraMiniviewPort;
        glm::mat4 projectionMatrixPerspective, projectionMatrixOrtho;
        bool renderCameraTarget;
        float fov, left, right, up, down, zNear, zFar;
        float angle;
        glm::vec3 targetPosition;
        int rivals1, rivals2, rivals3, rivals4, rivals5;
        glm::ivec2 resolution;
        float carColorR1, carColorG1, carColorB1, carColorR2, carColorG2, carColorB2, carColorR3, carColorG3, carColorB3,
            carColorR4, carColorG4, carColorB4, carColorR5, carColorG5, carColorB5;
        int direction1, direction2, direction3, direction4, direction5;
        std::vector<glm::vec3> upIndices;
        std::vector<glm::vec3> downIndices;
        std::vector<VertexFormat> verticesTrack;
        std::vector<glm::vec3> trackPoints;
        std::vector<glm::vec3> evenCarIndices;
        std::vector<glm::vec3> oddCarIndices;
        std::vector<glm::vec4> cars;
        std::vector<float> translateX, translateZ;
        std::vector<float> step;
    };
}   // namespace m1

