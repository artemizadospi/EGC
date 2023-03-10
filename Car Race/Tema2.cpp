#include "lab_m1/Tema2/Tema2.h"

#include <vector>
#include <string>
#include <iostream>
#include <math.h>

#include "lab_m1/Tema2/transform3D.h"

using namespace std;
using namespace m1;


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{

	camera = new implemented::CameraTema2();
	camera->Set(glm::vec3(0, 2.5f, 3), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	// camera este rotita la inceput pentru a sincroniza sensul de mers al masinii
	// cu cel din miniviewport
	camera->RotateThirdPerson_OY(3.14);
	cameraMiniviewPort = new implemented::CameraTema2();

	angle = 0;
	fov = 100.f;
	left = -30.0f;
	right = 30.0f;
	up = 20.0f;
	down = -20.0f;
	projectionMatrixOrtho = glm::ortho(left, right, down, up, 0.01f, 200.0f);
	projectionMatrixPerspective = glm::perspective(RADIANS(fov), window->props.aspectRatio, 0.01f, 200.0f);
	cars.resize(5);

	Mesh* mesh = new Mesh("box");
	mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
	meshes[mesh->GetMeshID()] = mesh;

	Mesh* mesh2 = new Mesh("plane");
	mesh2->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
	meshes[mesh2->GetMeshID()] = mesh2;

	Mesh* mesh3 = new Mesh("sphere");
	mesh3->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
	meshes[mesh3->GetMeshID()] = mesh3;

	{
		Shader* shader = new Shader("PositionShader");
		shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShaderPosition.glsl"), GL_VERTEX_SHADER);
		shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// initial sunt generate 90 de puncte intre care mai adaug 20 de puncte prin acel for
	for (float i = 0; i <= 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((72.9 + i * (72.71 - 72.9)), 0, (4.35 + i * (8.45 - 4.35))));
	}
	for (float i = 0; i <= 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((72.71 + i * (71.38 - 72.71)), 0, (8.45 + i * (12.02 - 8.45))));
	}
	for (float i = 0; i <= 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((71.38 + i * (69.64 - 71.38)), 0, (12.02 + i * (16.05 - 12.02))));
	}
	for (float i = 0; i <= 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((69.64 + i * (67.19 - 69.64)), 0, (16.05 + i * (19.72 - 16.05))));
	}
	for (float i = 0; i <= 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((67.19 + i * (64.81 - 67.19)), 0, (19.72 + i * (22.78 - 19.72))));
	}
	for (float i = 0; i <= 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((64.81 + i * (62.04 - 64.81)), 0, (22.78 + i * (25.31 - 22.78))));
	}
	for (float i = 0; i <= 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((62.04 + i * (59.04 - 62.04)), 0, (25.31 + i * (28.55 - 25.31))));
	}
	for (float i = 0; i <= 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((59.04 + i * (53.87 - 59.04)), 0, (28.55 + i * (31.56 - 28.55))));
	}
	for (float i = 0; i <= 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((53.87 + i * (47.98 - 53.87)), 0, (31.56 + i * (33.6 - 31.56))));
	}
	for (float i = 0; i <= 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((47.98 + i * (42.71 - 47.98)), 0, (33.6 + i * (33.88 - 33.6))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((42.71 + i * (38.69 - 42.71)), 0, (33.88 + i * (34.06 - 33.88))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((38.69 + i * (34.32 - 38.69)), 0, (34.06 + i * (33.18 - 34.06))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((34.32 + i * (30.64 - 34.32)), 0, (33.18 + i * (31.96 - 33.18))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((30.64 + i * (26.62 - 30.64)), 0, (31.96 + i * (30.91 - 31.96))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((26.62 + i * (23.3 - 26.62)), 0, (30.91 + i * (30.04 - 30.91))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((23.3 + i * (20.33 - 23.3)), 0, (30.04 + i * (28.29 - 30.04))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((20.33 + i * (17.35 - 20.33)), 0, (28.29 + i * (26.54 - 28.29))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((17.35 + i * (14.56 - 17.35)), 0, (26.54 + i * (24.27 - 26.54))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((14.56 + i * (11.41 - 14.56)), 0, (24.27 + i * (21.47 - 24.27))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((11.41 + i * (8.43 - 11.41)), 0, (21.47 + i * (19.04 - 21.47))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((8.43 + i * (5.29 - 8.43)), 0, (19.04 + i * (17.1 - 19.04))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((5.29 + i * (2.49 - 5.29)), 0, (17.1 + i * (15.17 - 17.1))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((2.49 + i * (0 - 2.49)), 0, (15.17 + i * (13.43 - 15.17))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((i * (-3.45)), 0, (13.43 + i * (10.98 - 13.43))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-3.45 + i * (-6.6 - (-3.45))), 0, (10.98 + i * (9.53 - 10.98))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-6.6 + i * (-10.72 - (-6.6))), 0, (9.53 + i * (9.68 - 9.53))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-10.72 + i * (-14.85 - (-10.72))), 0, (9.68 + i * (11.21 - 9.68))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-14.85 + i * (-19.28 - (-14.85))), 0, (11.21 + i * (13.2 - 11.21))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-19.28 + i * (-22.68 - (-19.28))), 0, (13.2 + i * (15.03 - 13.2))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-22.68 + i * (-26.4 - (-22.68))), 0, (15.03 + i * (17.25 - 15.03))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-26.4 + i * (-29.47 - (-26.4))), 0, (17.25 + i * (19.12 - 17.25))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-29.47 + i * (-32.29 - (-29.47))), 0, (19.12 + i * (21.29 - 19.12))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-32.29 + i * (-35.97 - (-32.29))), 0, (21.29 + i * (23.45 - 21.29))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-35.97 + i * (-39.15 - (-35.97))), 0, (23.45 + i * (24.2 - 23.45))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-39.15 + i * (-42.68 - (-39.15))), 0, (24.2 + i * (24.11 - 24.2))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-42.68 + i * (-46.21 - (-42.68))), 0, (24.11 + i * (23.05 - 24.11))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-46.21 + i * (-49.57 - (-46.21))), 0, (23.05 + i * (21.2 - 23.05))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-49.57 + i * (-52.51 - (-49.57))), 0, (21.2 + i * (18.76 - 21.2))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-52.51 + i * (-55.36 - (-52.51))), 0, (18.76 + i * (15.75 - 18.76))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-55.36 + i * (-57.18 - (-55.36))), 0, (15.75 + i * (12.9 - 15.75))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-57.18 + i * (-58.59 - (-57.18))), 0, (12.9 + i * (10.11 - 12.9))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-58.59 + i * (-59.68 - (-58.59))), 0, (10.11 + i * (6.72 - 10.11))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-59.68 + i * (-60.12 - (-59.68))), 0, (6.72 + i * (3 - 6.72))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-60.12 + i * (-59.68 - (-60.12))), 0, (3 + i * (-0.86 - 3))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-59.68 + i * (-59.07 - (-59.68))), 0, (-0.86 + i * (-3.98 - (-0.86)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-59.07 + i * (-58.25 - (-59.07))), 0, (-3.98 + i * (-6.53 - (-3.98)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-58.25 + i * (-57.08 - (-58.25))), 0, (-6.53 + i * (-9.12 - (-6.53)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-57.08 + i * (-55.74 - (-57.08))), 0, (-9.12 + i * (-11.46 - (-9.12)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-55.74 + i * (-53.99 - (-55.74))), 0, (-11.46 + i * (-13.81 - (-11.46)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-53.99 + i * (-51.75 - (-53.99))), 0, (-13.81 + i * (-15.75 - (-13.81)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-51.75 + i * (-48.84 - (-51.75))), 0, (-15.75 + i * (-18.31 - (-15.75)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-48.84 + i * (-44.86 - (-48.84))), 0, (-18.31 + i * (-20.74 - (-18.31)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-44.86 + i * (-40.47 - (-44.86))), 0, (-20.74 + i * (-22.26 - (-20.74)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-40.47 + i * (-36.25 - (-40.47))), 0, (-22.26 + i * (-23.36 - (-22.26)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-36.25 + i * (-31.7 - (-36.25))), 0, (-23.36 + i * (-24.05 - (-23.36)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-31.7 + i * (-27.07 - (-31.7))), 0, (-24.05 + i * (-24.61 - (-24.05)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-27.07 + i * (-22.73 - (-27.07))), 0, (-24.61 + i * (-24.57 - (-24.61)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-22.73 + i * (-18.68 - (-22.73))), 0, (-24.57 + i * (-24.61 - (-24.57)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-18.68 + i * (-14.03 - (-18.68))), 0, (-24.61 + i * (-24.5 - (-24.61)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-14.03 + i * (-9.82 - (-14.03))), 0, (-24.5 + i * (-24.28 - (-24.5)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-9.82 + i * (-6.1 - (-9.82))), 0, (-24.28 + i * (-23.17 - (-24.28)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-6.1 + i * (-2.26 - (-6.1))), 0, (-23.17 + i * (-21.6 - (-23.17)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((-2.26 + i * (1.41 - (-2.26))), 0, (-21.6 + i * (-19.5 - (-21.6)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((1.41 + i * (3.85 - 1.41)), 0, (-19.5 + i * (-17.05 - (-19.5)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((3.85 + i * (6.6 - 3.85)), 0, (-17.05 + i * (-14.7 - (-17.05)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((6.6 + i * (9.62 - 6.6)), 0, (-14.7 + i * (-12.08 - (-14.7)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((9.62 + i * (12.79 - 9.62)), 0, (-12.08 + i * (-9.17 - (-12.08)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((12.79 + i * (16.75 - 12.79)), 0, (-9.17 + i * (-6.53 - (-9.17)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((16.75 + i * (20.45 - 16.75)), 0, (-6.53 + i * (-4.68 - (-6.53)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((20.45 + i * (24.42 - 20.45)), 0, (-4.68 + i * (-3.89 - (-4.68)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((24.42 + i * (27.46 - 24.42)), 0, (-3.89 + i * (-3.81 - (-3.89)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((27.46 + i * (30.12 - 27.46)), 0, (-3.81 + i * (-4.58 - (-3.81)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((30.12 + i * (32.45 - 30.12)), 0, (-4.58 + i * (-6.25 - (-4.58)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((32.45 + i * (34.55 - 32.45)), 0, (-6.25 + i * (-8.46 - (-6.25)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((34.55 + i * (35.99 - 34.55)), 0, (-8.46 + i * (-10.89 - (-8.46)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((35.99 + i * (38.38 - 35.99)), 0, (-10.89 + i * (-13 - (-10.89)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((38.38 + i * (42.02 - 38.38)), 0, (-13 + i * (-14.82 - (-13)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((42.02 + i * (46.13 - 42.02)), 0, (-14.82 + i * (-16.06 - (-14.82)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((46.13 + i * (50.25 - 46.13)), 0, (-16.06 + i * (-16.63 - (-16.06)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((50.25 + i * (53.86 - 50.25)), 0, (-16.63 + i * (-17.04 - (-16.63)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((53.86 + i * (57.15 - 53.86)), 0, (-17.04 + i * (-16.32 - (-17.04)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((57.15 + i * (60.43 - 57.15)), 0, (-16.32 + i * (-15.04 - (-16.32)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((60.43 + i * (63.71 - 60.43)), 0, (-15.04 + i * (-13.19 - (-15.04)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((63.71 + i * (67.13 - 63.71)), 0, (-13.19 + i * (-11.47 - (-13.19)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((67.13 + i * (69.91 - 67.13)), 0, (-11.47 + i * (-9.62 - (-11.47)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((69.91 + i * (71.6 - 69.91)), 0, (-9.62 + i * (-7.66 - (-9.62)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((71.6 + i * (72.92 - 71.6)), 0, (-7.66 + i * (-5.03 - (-7.66)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((72.92 + i * (73.11 - 72.92)), 0, (-5.03 + i * (-1.79 - (-5.03)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((73.11 + i * (73.01 - 73.11)), 0, (-1.79 + i * (1.15 - (-1.79)))));
	}
	for (float i = 0; i < 1; i = i + 0.05) {
		trackPoints.push_back(glm::vec3((73.01 + i * (72.9 - 73.01)), 0, (1.15 + i * (4.35 - 1.15))));
	}

	// generarea punctelor interioare si exterioare si pastrarea lor in vectori corespunzatori
	glm::vec3 d;
	glm::vec3 up = glm::vec3(0, 1, 0);
	for (int i = 0; i < trackPoints.size() - 1; i++) {
		d.x = trackPoints[i + 1].x - trackPoints[i].x;
		d.z = trackPoints[i + 1].z - trackPoints[i].z;
		d.y = 0;
		glm::vec3 p = glm::normalize(glm::cross(d, up));
		upIndices.push_back(glm::vec3((trackPoints[i].x + 4 * p.x), 0, (trackPoints[i].z + 4 * p.z)));
		downIndices.push_back(glm::vec3((trackPoints[i].x - 4 * p.x), 0, (trackPoints[i].z - 4 * p.z)));
		// se pastreaza indicii pentru generarea traseelor masinilor inamice
		evenCarIndices.push_back(glm::vec3((trackPoints[i].x + 2 * p.x), 0, (trackPoints[i].z + 2 * p.z)));
		oddCarIndices.push_back(glm::vec3((trackPoints[i].x - 2 * p.x), 0, (trackPoints[i].z - 2 * p.z)));
	}
	// caz special pentru ultimul punct(se leaga de punctul 0)
	d.x = trackPoints[0].x - trackPoints[trackPoints.size() - 1].x;
	d.z = trackPoints[0].z - trackPoints[trackPoints.size() - 1].z;
	d.y = 0;
	glm::vec3 p = glm::normalize(glm::cross(d, up));
	upIndices.push_back(glm::vec3((trackPoints[trackPoints.size() - 1].x + 4 * p.x), 0, (trackPoints[trackPoints.size() - 1].z + 4 * p.z)));
	downIndices.push_back(glm::vec3((trackPoints[trackPoints.size() - 1].x - 4 * p.x), 0, (trackPoints[trackPoints.size() - 1].z - 4 * p.z)));
	// se pastreaza indicii pentru generarea traseelor masinilor inamice
	evenCarIndices.push_back(glm::vec3((trackPoints[trackPoints.size() - 1].x + 2 * p.x), 0, (trackPoints[trackPoints.size() - 1].z + 2 * p.z)));
	oddCarIndices.push_back(glm::vec3((trackPoints[trackPoints.size() - 1].x - 2 * p.x), 0, (trackPoints[trackPoints.size() - 1].z - 2 * p.z)));

	for (int i = 0; i < upIndices.size(); i++) {
		verticesTrack.push_back(VertexFormat(glm::vec3(upIndices[i].x, 0, upIndices[i].z), glm::vec3(0, 0, 0)));
		verticesTrack.push_back(VertexFormat(glm::vec3(downIndices[i].x, 0, downIndices[i].z), glm::vec3(0, 0, 0)));
	}

	std::vector<unsigned int> indicesTrack;
	// generarea indicilor pentru triunghiuri
	for (int i = 0; i < verticesTrack.size() - 2; i = i + 2) {
		indicesTrack.push_back(i);
		indicesTrack.push_back(i + 1);
		indicesTrack.push_back(i + 3);
		indicesTrack.push_back(i);
		indicesTrack.push_back(i + 3);
		indicesTrack.push_back(i + 2);
	}
	// caz special pentru ultimele doua triunghiuri
	indicesTrack.push_back(verticesTrack.size() - 2);
	indicesTrack.push_back(verticesTrack.size() - 2 + 1);
	indicesTrack.push_back(1);
	indicesTrack.push_back(verticesTrack.size() - 2);
	indicesTrack.push_back(1);
	indicesTrack.push_back(0);
	Mesh* track = new Mesh("track");
	track->SetDrawMode(GL_TRIANGLES);
	track->InitFromData(verticesTrack, indicesTrack);
	meshes[track->GetMeshID()] = track;

	// generare masini pe pozitii initiale date, dar cu directii si culori aleatorii
	srand(time(NULL));
	carColorR1 = (float)(rand() % 11) / 10;
	carColorG1 = (float)(rand() % 11) / 10;
	carColorB1 = (float)(rand() % 11) / 10;
	rivals1 = 10;
	direction1 = rand() % 2;

	carColorR2 = (float)(rand() % 11) / 10;
	carColorG2 = (float)(rand() % 11) / 10;
	carColorB2 = (float)(rand() % 11) / 10;
	rivals2 = 200;
	direction2 = rand() % 2;

	carColorR3 = (float)(rand() % 11) / 10;
	carColorG3 = (float)(rand() % 11) / 10;
	carColorB3 = (float)(rand() % 11) / 10;
	rivals3 = 400;
	direction3 = rand() % 2;

	carColorR4 = (float)(rand() % 11) / 10;
	carColorG4 = (float)(rand() % 11) / 10;
	carColorB4 = (float)(rand() % 11) / 10;
	rivals4 = 800;
	direction4 = rand() % 2;

	carColorR5 = (float)(rand() % 11) / 10;
	carColorG5 = (float)(rand() % 11) / 10;
	carColorB5 = (float)(rand() % 11) / 10;
	rivals5 = 1000;
	direction5 = rand() % 2;
}

void Tema2::FrameStart()
{
	glClearColor(0, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	resolution = window->GetResolution();
}

void Tema2::RenderScene(float deltaTimeSeconds, int viewPort) {
	glm::mat4 modelMatrix = glm::mat4(1);
	glm::vec3 d;
	glm::vec3 up = glm::vec3(0, 1, 0);

	// generarea pozitiilor copacilor s-a realizat dupa modelul generarii punctelor
	// interioare si exterioare, metoda fiind aplicata pe punctele exterioare si interioare
	for (int i = 0; i < upIndices.size() - 1; i = i + 50) {
		d.x = upIndices[i + 1].x - upIndices[i].x;
		d.z = upIndices[i + 1].z - upIndices[i].z;
		d.y = 0;
		glm::vec3 p = glm::cross(d, up);

		if (i % 7 != 0) {
			modelMatrix = RenderTreesIn(2, 2, 2, i, p, 2);
			RenderSimpleMesh(meshes["box"], shaders["PositionShader"], modelMatrix, glm::vec3(0, 1, 0), viewPort);
		}
		else {
			modelMatrix = RenderTreesIn(3, 3, 3, i, p, 2);
			RenderSimpleMesh(meshes["sphere"], shaders["PositionShader"], modelMatrix, glm::vec3(0, 0.5, 0), viewPort);
		}
		if (i % 3 != 0) {
			modelMatrix = RenderTreesOut(2, 2, 2, i, p, 2);
			RenderSimpleMesh(meshes["box"], shaders["PositionShader"], modelMatrix, glm::vec3(0, 1, 0), viewPort);
		}
		else {
			modelMatrix = RenderTreesOut(3, 3, 3, i, p, 2);
			RenderSimpleMesh(meshes["sphere"], shaders["PositionShader"], modelMatrix, glm::vec3(0, 0.5, 0), viewPort);
		}
		modelMatrix = RenderTreesIn(1, 3, 1, i, p, 0);
		RenderSimpleMesh(meshes["box"], shaders["PositionShader"], modelMatrix, glm::vec3(0.512, 0, 0), viewPort);

		modelMatrix = RenderTreesOut(1, 3, 1, i, p, 0);
		RenderSimpleMesh(meshes["box"], shaders["PositionShader"], modelMatrix, glm::vec3(0.512, 0, 0), viewPort);
	}

	modelMatrix = glm::mat4(1);
	modelMatrix *= transform3D::Translate(5, 0.2, -20);
	modelMatrix *= transform3D::RotateOY(-0.65);
	RenderSimpleMesh(meshes["track"], shaders["PositionShader"], modelMatrix, glm::vec3(0, 0, 0), viewPort);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::scale(modelMatrix, glm::vec3(5));
	RenderSimpleMesh(meshes["plane"], shaders["PositionShader"], modelMatrix, glm::vec3(0.25f, 0.7f, 0.54f), viewPort);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
	modelMatrix *= transform3D::Translate(0, -1, 0);
	modelMatrix *= transform3D::RotateOY(angle);
	modelMatrix *= transform3D::Scale(0.7f, 0.7f, 1.2f);
	RenderSimpleMesh(meshes["box"], shaders["PositionShader"], modelMatrix, glm::vec3(0, 0.8, 0.8), viewPort);
	//car1
	// valorile specifice masinilor, fiind variabile globale, se modifica doar daca
	// se fac modificari pe viewport ul princpal, pentru ca cele doua
	// viewporturi sa coincida ca imagine
	if (viewPort == 1) {
		if (direction1 == 0) {
			if (rivals1 >= trackPoints.size() - 1)
				rivals1 = 0;
		}
		else {
			if (rivals1 <= 0)
				rivals1 = trackPoints.size() - 1;
		}
	}
	RenderCars(rivals1, carColorR1, carColorG1, carColorB1, 0, direction1, viewPort, trackPoints);
	if (viewPort == 1) {
		if (direction1 == 1)
			rivals1--;
		else
			rivals1++;
	}

	//car2
	if (viewPort == 1) {
		if (direction2 == 0) {
			if (rivals2 >= trackPoints.size() - 1)
				rivals2 = 0;
		}
		else {
			if (rivals2 <= 0)
				rivals2 = trackPoints.size() - 1;
		}
	}
	RenderCars(rivals2, carColorR2, carColorG2, carColorB2, 1, direction2, viewPort, oddCarIndices);
	if (viewPort == 1) {
		if (direction2 == 1)
			rivals2--;
		else
			rivals2++;
	}
	//car3
	if (viewPort == 1) {
		if (direction3 == 0) {
			if (rivals3 >= trackPoints.size() - 1)
				rivals3 = 0;
		}
		else {
			if (rivals3 <= 0)
				rivals3 = trackPoints.size() - 1;
		}
	}
	RenderCars(rivals3, carColorR3, carColorG3, carColorB3, 2, direction3, viewPort, evenCarIndices);
	if (viewPort == 1) {
		if (direction3 == 1)
			rivals3--;
		else
			rivals3++;
	}
	//car4
	if (viewPort == 1) {
		if (direction4 == 0) {
			if (rivals4 >= trackPoints.size() - 1)
				rivals4 = 0;
		}
		else {
			if (rivals4 <= 0)
				rivals4 = trackPoints.size() - 1;
		}
	}
	RenderCars(rivals4, carColorR4, carColorG4, carColorB4, 3, direction4, viewPort, oddCarIndices);
	if (viewPort == 1) {
		if (direction4 == 1)
			rivals4--;
		else
			rivals4++;
	}
	//car5
	if (viewPort == 1) {
		if (direction5 == 0) {
			if (rivals5 >= trackPoints.size() - 1)
				rivals5 = 0;
		}
		else {
			if (rivals5 <= 0)
				rivals5 = trackPoints.size() - 1;
		}
	}
	RenderCars(rivals5, carColorR5, carColorG5, carColorB5, 4, direction5, viewPort, evenCarIndices);
	if (viewPort == 1) {
		if (direction5 == 1)
			rivals5--;
		else
			rivals5++;
	}
}

glm::mat4 Tema2::RenderTreesIn(float scaleX, float scaleY, float scaleZ, int pointIndex, glm::vec3 p, int trunk) {
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix *= transform3D::Translate(5, 0.2, -20);
	modelMatrix *= transform3D::RotateOY(-0.65);
	modelMatrix *= transform3D::Translate(upIndices[pointIndex].x + 8 * p.x, upIndices[pointIndex].y + trunk, upIndices[pointIndex].z + 8 * p.z);
	modelMatrix *= transform3D::Scale(scaleX, scaleY, scaleZ);
	return modelMatrix;
}

glm::mat4 Tema2::RenderTreesOut(float scaleX, float scaleY, float scaleZ, int pointIndex, glm::vec3 p, int trunk) {
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix *= transform3D::Translate(5, 0.2, -20);
	modelMatrix *= transform3D::RotateOY(-0.65);
	modelMatrix *= transform3D::Translate(downIndices[pointIndex].x - 8 * p.x, downIndices[pointIndex].y + trunk, downIndices[pointIndex].z - 8 * p.z);
	modelMatrix *= transform3D::Scale(scaleX, scaleY, scaleZ);
	return modelMatrix;
}

void Tema2::RenderCars(int rivals, float colorR, float colorG, float colorB, int indexRival, int direction, int viewPort, vector<glm::vec3> indices) {
	glm::vec4 currentPoint;
	glm::vec4 nextPoint;
	glm::mat4 trackMatrix = glm::mat4(1);
	trackMatrix *= transform3D::Translate(5, 0.2, -20);
	trackMatrix *= transform3D::RotateOY(-0.65);
	currentPoint = glm::vec4(indices[rivals], 1);
	currentPoint = trackMatrix * currentPoint;
	// masinile se randeaza pe punctele din indices, directia acestora
	// fiind data de vectorul directie dintre punctul curent si cel ce urmeaza
	if (direction == 0) {
		if (rivals < indices.size() - 1) {
			nextPoint = glm::vec4(indices[rivals + 1], 1);
			nextPoint = trackMatrix * nextPoint;
		}
		else {
			nextPoint = glm::vec4(indices[0], 1);
			nextPoint = trackMatrix * nextPoint;
		}
	}
	else {
		if (rivals > 0) {
			nextPoint = glm::vec4(indices[rivals - 1], 1);
			nextPoint = trackMatrix * nextPoint;
		}
		else {
			nextPoint = glm::vec4(indices[indices.size() - 1], 1);
			nextPoint = trackMatrix * nextPoint;
		}
	}
	cars[indexRival] = currentPoint;
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix *= transform3D::Translate(currentPoint.x, 0.5, currentPoint.z);
	if (direction == 1)
		modelMatrix *= transform3D::RotateOY(3.14);
	modelMatrix *= transform3D::RotateOY(atan((nextPoint.x - currentPoint.x) / (nextPoint.z - currentPoint.z)));
	modelMatrix *= transform3D::Scale(0.7f, 0.7f, 1.2f);
	RenderSimpleMesh(meshes["box"], shaders["PositionShader"], modelMatrix, glm::vec3(colorR, colorG, colorB), viewPort);
}

void Tema2::Update(float deltaTimeSeconds)
{
	cameraMiniviewPort->Set(glm::vec3(0, 150, 0), camera->GetTargetPosition(), glm::vec3(0, 0, 1));
	glViewport(0, 0, resolution.x, resolution.y);
	RenderScene(deltaTimeSeconds, 1);
	glClear(GL_DEPTH_BUFFER_BIT);
	miniViewportArea = ViewportArea(900, 25, resolution.x / 4.0f, resolution.y / 4.0f);
	glViewport(miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height);
	RenderScene(deltaTimeSeconds, 0);
}

void Tema2::FrameEnd()
{
}

void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, int viewPort)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// Render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Get shader location for uniform mat4 "Model"
	int location_model = glGetUniformLocation(shader->program, "Model");

	// Set shader uniform "Model" to modelMatrix
	glUniformMatrix4fv(location_model, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Get shader location for uniform mat4 "View"
	int location_view = glGetUniformLocation(shader->program, "View");

	// Set shader uniform "View" to viewMatrix
	// verificare viewport curent
	if (viewPort == 1)
		glUniformMatrix4fv(location_view, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	else
		glUniformMatrix4fv(location_view, 1, GL_FALSE, glm::value_ptr(cameraMiniviewPort->GetViewMatrix()));

	// Get shader location for uniform mat4 "Projection"
	int location_projection = glGetUniformLocation(shader->program, "Projection");

	// Set shader uniform "Projection" to projectionMatrix
	// verificare viewport curent
	if (viewPort == 1)
		glUniformMatrix4fv(location_projection, 1, GL_FALSE, glm::value_ptr(projectionMatrixPerspective));
	else
		glUniformMatrix4fv(location_projection, 1, GL_FALSE, glm::value_ptr(projectionMatrixOrtho));
	glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(color));
	glUniform3fv(glGetUniformLocation(shader->program, "car_position"), 1, glm::value_ptr(camera->GetTargetPosition()));

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->m_VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

// functie ce calculeaza aria unui triunghi
float m1::Tema2::TringleArea(glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
	glm::vec3 ab = glm::vec3(b.x - a.x, 0, b.z - a.z);
	glm::vec3 ac = glm::vec3(c.x - a.x, 0, c.z - a.z);
	float cross_product = ab.x * ac.z - ab.z * ac.x;
	return abs(cross_product) / 2;
}

// functie ce verifica daca un punct se gaseste in interiorul unui triunghi
bool m1::Tema2::InsideTriangle(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
	float triangle_area = TringleArea(a, b, c);
	float area_sum = 0;
	area_sum += TringleArea(a, b, p);
	area_sum += TringleArea(a, c, p);
	area_sum += TringleArea(b, c, p);
	if (triangle_area <= area_sum + 0.001 && triangle_area >= area_sum - 0.001)
		return true;
	return false;
}

// verificare daca pozitia curenta se gaseste in vreun triunghi de pe pista
bool Tema2::CheckCarOnTrack(glm::vec3 targetPosition) {
	glm::vec4 triangleSide1, triangleSide2, triangleSide3;
	glm::mat4 trackMatrix = glm::mat4(1);
	trackMatrix *= transform3D::Translate(5, 0.2, -20);
	trackMatrix *= transform3D::RotateOY(-0.65);
	bool inside = false;
	for (int i = 0; i < verticesTrack.size() - 2; i = i + 2) {
		triangleSide1 = glm::vec4(verticesTrack[i].position, 1);
		triangleSide1 = trackMatrix * triangleSide1;
		triangleSide2 = glm::vec4(verticesTrack[i + 1].position, 1);
		triangleSide2 = trackMatrix * triangleSide2;
		triangleSide3 = glm::vec4(verticesTrack[i + 3].position, 1);
		triangleSide3 = trackMatrix * triangleSide3;
		inside = InsideTriangle(targetPosition, glm::vec3(triangleSide1.x, 0, triangleSide1.z), glm::vec3(triangleSide2.x, 0, triangleSide2.z), glm::vec3(triangleSide3.x, 0, triangleSide3.z));
		triangleSide1 = glm::vec4(verticesTrack[i].position, 1);
		triangleSide1 = trackMatrix * triangleSide1;
		triangleSide2 = glm::vec4(verticesTrack[i + 3].position, 1);
		triangleSide2 = trackMatrix * triangleSide2;
		triangleSide3 = glm::vec4(verticesTrack[i + 2].position, 1);
		triangleSide3 = trackMatrix * triangleSide3;
		if (inside == false)
			inside = InsideTriangle(targetPosition, glm::vec3(triangleSide1.x, 0, triangleSide1.z), glm::vec3(triangleSide2.x, 0, triangleSide2.z), glm::vec3(triangleSide3.x, 0, triangleSide3.z));
		if (inside == true)
			break;
	}
	triangleSide1 = glm::vec4(verticesTrack[verticesTrack.size() - 2].position, 1);
	triangleSide1 = trackMatrix * triangleSide1;
	triangleSide2 = glm::vec4(verticesTrack[verticesTrack.size() - 2 + 1].position, 1);
	triangleSide2 = trackMatrix * triangleSide2;
	triangleSide3 = glm::vec4(verticesTrack[1].position, 1);
	triangleSide3 = trackMatrix * triangleSide3;
	if (inside == false)
		inside = InsideTriangle(targetPosition, glm::vec3(triangleSide1.x, 0, triangleSide1.z), glm::vec3(triangleSide2.x, 0, triangleSide2.z), glm::vec3(triangleSide3.x, 0, triangleSide3.z));
	triangleSide1 = glm::vec4(verticesTrack[verticesTrack.size() - 2].position, 1);
	triangleSide1 = trackMatrix * triangleSide1;
	triangleSide2 = glm::vec4(verticesTrack[1].position, 1);
	triangleSide2 = trackMatrix * triangleSide2;
	triangleSide3 = glm::vec4(verticesTrack[0].position, 1);
	triangleSide3 = trackMatrix * triangleSide3;
	if (inside == false)
		inside = InsideTriangle(targetPosition, glm::vec3(triangleSide1.x, 0, triangleSide1.z), glm::vec3(triangleSide2.x, 0, triangleSide2.z), glm::vec3(triangleSide3.x, 0, triangleSide3.z));
	return inside;
}

// verificare coliziune cu celelalte masini
bool Tema2::CheckCarCollision() {
	bool collision = false;
	for (int i = 0; i < cars.size(); i++) {
		if (sqrt((camera->GetTargetPosition().x - cars[i].x) * (camera->GetTargetPosition().x - cars[i].x) +
			(camera->GetTargetPosition().y - 1 - cars[i].y) * (camera->GetTargetPosition().y - 1 - cars[i].y) +
			(camera->GetTargetPosition().z - cars[i].z) * (camera->GetTargetPosition().z - cars[i].z)) <= 1.2)
			collision = true;
	}
	return collision;
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	float cameraSpeed = 5;

	if (window->KeyHold(GLFW_KEY_W)) {
		camera->MoveForward(cameraSpeed * deltaTime);
		targetPosition = glm::vec3(camera->GetTargetPosition().x, 0, camera->GetTargetPosition().z);
		if (CheckCarOnTrack(targetPosition) == false || CheckCarCollision() == true)
			camera->MoveForward(-cameraSpeed * deltaTime);
	}

	if (window->KeyHold(GLFW_KEY_S)) {
		camera->MoveForward(-cameraSpeed * deltaTime);
		targetPosition = glm::vec3(camera->GetTargetPosition().x, 0, camera->GetTargetPosition().z);
		if (CheckCarOnTrack(targetPosition) == false || CheckCarCollision() == true)
			camera->MoveForward(cameraSpeed * deltaTime);

	}

	if (window->KeyHold(GLFW_KEY_A)) {
		camera->RotateThirdPerson_OY(cameraSpeed * 0.01);
		angle += cameraSpeed * 0.01;
		if (CheckCarCollision() == true) {
			camera->RotateThirdPerson_OY(-cameraSpeed * 0.01);
			angle -= cameraSpeed * 0.01;
		}
	}

	if (window->KeyHold(GLFW_KEY_D)) {
		camera->RotateThirdPerson_OY(-cameraSpeed * 0.01);
		angle -= cameraSpeed * 0.01;
		if (CheckCarCollision() == true) {
			camera->RotateThirdPerson_OY(cameraSpeed * 0.01);
			angle += cameraSpeed * 0.01;
		}
	}

}


void Tema2::OnKeyPress(int key, int mods)
{
}

void Tema2::OnKeyRelease(int key, int mods)
{
	// Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// Add mouse move event
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button press event
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
