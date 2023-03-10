#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"

using namespace std;
using namespace m1;


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);
	// valori pentru dimensiunea ratei
	beakSide = 20;
	headSide = 40;
	bodySide = 60;
	wingSide = 70;
	// variabila care imi pastreaza timpul pana la starea de eliberare
	time = 0;
	// valori cu care se deplaseaza rata pe x si y
	valueX = 130 + rand() % 141;
	valueY = 130 + rand() % 141;
	moveX = rand() % (1280 + 1);
	moveY = 0;
	hypotenuse = sqrt(valueY * valueY + valueX * valueX);
	// unghiul cu care trebuie rotita rata calculat in functie de valorile anterioare
	angularStep = (float)asin((float)valueY / hypotenuse);
	// punctul in jurul caruia se rotesc aripile
	wingX = corner.x + wingSide * sqrt(3) / 2;
	wingY = corner.y + wingSide / 2;
	// numarul de gloante
	bullets = 3;
	// numarul de vieti
	lives = 3;
	// valori setate pe 0 sau 1 care verifica daca rata a ajuns la una din margini
	maximumX = rand() % 2;
	maximumY = 0;
	// in functie de maximumX, ales aleator, se alege prima ruta pentru rata(dreapta sau stanga)
	if (maximumX == 1)
		angularStep = angularStep + 1.57f;
	// variabile necesare miscarii aripilor
	movementTimeWing1 = 0;
	currentSideWing1 = 0;
	movementTimeWing2 = 0;
	currentSideWing2 = 0;
	// verifica daca rata a fost impuscata sau nu
	shot = 0;
	// scorul curent ca dimensiune
	currentScoreScale = 0;
	// numarul de rate
	ducks = 0;
	// pozitionarea tintei
	targetX = 0;
	targetY = 0;
	// variabile daca determina daca jocul a fost castigat sau nu
	win = 0;
	lose = 0;
	// variabila necesara pentru miscarea zapezii pe ecran
	moveSnow = 0;
	// pastreaza nivelul curent
	level = 1;
	// variabila ce verifica daca nivelul a fost schimbat
	nextLevel = 1;
	// pastreaza durata aparitiei nivelului curent pe ecran
	nextLevelTransition = 100;
	// culoarea ratei compusa din valori alese random
	red = (float)(rand() % 11) / 10;
	green = (float)(rand() % 11) / 10;
	blue = (float)(rand() % 11) / 10;
	// vieti extra
	if (red == 1) {
		lives++;
	}
	// gloante extra
	if (green == 1) {
		bullets++;
	}


	Mesh* beak = object2D::CreateTriangle("beak", corner, beakSide, glm::vec3(1, 1, 0.16), true);
	AddMeshToList(beak);

	Mesh* head = object2D::CreateCircle("head", corner, headSide, glm::vec3(0.31, 0.16, 0), true);
	AddMeshToList(head);

	Mesh* body = object2D::CreateBody("body", corner, bodySide, glm::vec3(red, green, blue), true);
	AddMeshToList(body);

	Mesh* wing = object2D::CreateTriangle("wing", corner, wingSide, glm::vec3(0.31, 0.16, 0), true);
	AddMeshToList(wing);

	Mesh* hat = object2D::CreateTriangle("hat", corner, 80, glm::vec3(red, green, blue), true);
	AddMeshToList(hat);

	Mesh* accessory = object2D::CreateCircle("accessory", corner, 15, glm::vec3(1, 1, 1), true);
	AddMeshToList(accessory);

	Mesh* floor = object2D::CreateFloor("floor", corner, 15, glm::vec3(0, 0.3, 0), true);
	AddMeshToList(floor);

	Mesh* sky = object2D::CreateSky("sky", corner, 15, glm::vec3(0.5, 0.5, 0.5), true);
	AddMeshToList(sky);

	Mesh* life = object2D::CreateCircle("life", corner, 12, glm::vec3(1, 0, 0), true);
	AddMeshToList(life);

	Mesh* bullet = object2D::CreateSquare("bullet", corner, 12, glm::vec3(0, 1, 0), true);
	AddMeshToList(bullet);

	Mesh* maxScore = object2D::CreateScore("maxScore", corner, 25, glm::vec3(0, 0, 1), false);
	AddMeshToList(maxScore);

	Mesh* currentScore = object2D::CreateCurrentScore("currentScore", corner, 25, glm::vec3(0, 0, 1), true);
	AddMeshToList(currentScore);

	Mesh* target = object2D::CreateTarget("target", corner, 12, glm::vec3(0, 0, 0), true);
	AddMeshToList(target);

	Mesh* targetBorder = object2D::CreateTarget("targetBorder", corner, 24, glm::vec3(0, 0, 0), false);
	AddMeshToList(targetBorder);

	Mesh* tree = object2D::CreateTree("tree", corner, 100, glm::vec3(0, 0.102, 0), true);
	AddMeshToList(tree);

	Mesh* tree2 = object2D::CreateTree("tree2", corner, 140, glm::vec3(0, 0.102, 0), true);
	AddMeshToList(tree2);

	Mesh* tree3 = object2D::CreateTree("tree3", corner, 180, glm::vec3(0, 0.102, 0), true);
	AddMeshToList(tree3);

	Mesh* trunk = object2D::CreateTrunk("trunk", corner, 40, glm::vec3(0.25, 0.15, 0.12), true);
	AddMeshToList(trunk);

	Mesh* treeStar = object2D::CreateCircle("treeStar", corner, 12, glm::vec3(1, 1, 0.16), true);
	AddMeshToList(treeStar);

	Mesh* win = object2D::CreateCircle("win", corner, 300, glm::vec3(0, 1, 0), true);
	AddMeshToList(win);

	Mesh* lose = object2D::CreateCircle("lose", corner, 300, glm::vec3(1, 0, 0), true);
	AddMeshToList(lose);

	Mesh* snow = object2D::CreateCircle("snow", corner, 4, glm::vec3(1, 1, 1), true);
	AddMeshToList(snow);

	Mesh* nextLevelPart = object2D::CreateRectangle("nextLevelPart", corner, 60, 10, glm::vec3(0, 0, 0), true);
	AddMeshToList(nextLevelPart);

	Mesh* nextLevelPart2 = object2D::CreateRectangle("nextLevelPart2", corner, 30, 10, glm::vec3(0, 0, 0), true);
	AddMeshToList(nextLevelPart2);

	Mesh* draw = object2D::CreateRectangle("draw", corner, 300, 30, glm::vec3(1, 1, 1), true);
	AddMeshToList(draw);

	Mesh* draw2 = object2D::CreateRectangle("draw2", corner, 200, 30, glm::vec3(1, 1, 1), true);
	AddMeshToList(draw2);

	window->HidePointer();
}


void Tema1::FrameStart()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
	// timpul nu se modifica in perioada de asteptare intre nivele
	if (nextLevel != 1) {
		time += deltaTimeSeconds;
	}

	// daca nivelul s a schimbat si nu suntem in stare de castig sau pierdere
	// se afiseaza pe ecran mesjul corespunzator si se miscoreaza variabila de asteptare
	if (nextLevel == 1 && win != 1 && lose != 1) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(450, 400);
		modelMatrix *= transform2D::Rotate(1.57f);
		RenderMesh2D(meshes["nextLevelPart"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(450, 400);
		RenderMesh2D(meshes["nextLevelPart2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(500, 400);
		modelMatrix *= transform2D::Rotate(1.57f);
		RenderMesh2D(meshes["nextLevelPart"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(500, 450);
		RenderMesh2D(meshes["nextLevelPart2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(500, 425);
		RenderMesh2D(meshes["nextLevelPart2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(500, 400);
		RenderMesh2D(meshes["nextLevelPart2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(550, 455);
		modelMatrix *= transform2D::Rotate(-1.2f);
		RenderMesh2D(meshes["nextLevelPart"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(579, 399);
		modelMatrix *= transform2D::Rotate(1.2f);
		RenderMesh2D(meshes["nextLevelPart"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(630, 400);
		modelMatrix *= transform2D::Rotate(1.57f);
		RenderMesh2D(meshes["nextLevelPart"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(630, 450);
		RenderMesh2D(meshes["nextLevelPart2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(630, 425);
		RenderMesh2D(meshes["nextLevelPart2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(630, 400);
		RenderMesh2D(meshes["nextLevelPart2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(690, 400);
		modelMatrix *= transform2D::Rotate(1.57f);
		RenderMesh2D(meshes["nextLevelPart"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(690, 400);
		RenderMesh2D(meshes["nextLevelPart2"], shaders["VertexColor"], modelMatrix);
		for (int i = 0; i < level * 15; i += 15) {
			modelMatrix = glm::mat3(1);
			modelMatrix *= transform2D::Translate(760 + i, 400);
			modelMatrix *= transform2D::Rotate(1.57f);
			RenderMesh2D(meshes["nextLevelPart"], shaders["VertexColor"], modelMatrix);
		}
		nextLevelTransition--;
	}

	if (win == 1) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(530, 405);
		modelMatrix *= transform2D::Rotate(-1);
		RenderMesh2D(meshes["draw2"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(660, 230);
		modelMatrix *= transform2D::Rotate(1.2f);
		RenderMesh2D(meshes["draw"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(650, 350);
		RenderMesh2D(meshes["win"], shaders["VertexColor"], modelMatrix);
	}

	if (lose == 1) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(540, 460);
		modelMatrix *= transform2D::Rotate(-0.785f);
		RenderMesh2D(meshes["draw"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(560, 260);
		modelMatrix *= transform2D::Rotate(0.785f);
		RenderMesh2D(meshes["draw"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(650, 350);
		RenderMesh2D(meshes["lose"], shaders["VertexColor"], modelMatrix);
	}

	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(targetX, targetY);
	RenderMesh2D(meshes["target"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(targetX, targetY);
	RenderMesh2D(meshes["targetBorder"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(1150, 400);
	RenderMesh2D(meshes["treeStar"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(1100, 340);
	RenderMesh2D(meshes["tree"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(1080, 290);
	RenderMesh2D(meshes["tree2"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(1060, 230);
	RenderMesh2D(meshes["tree3"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(1130, 200);
	RenderMesh2D(meshes["trunk"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(120, 400);
	RenderMesh2D(meshes["treeStar"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(70, 340);
	RenderMesh2D(meshes["tree"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(50, 290);
	RenderMesh2D(meshes["tree2"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(30, 230);
	RenderMesh2D(meshes["tree3"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(100, 200);
	RenderMesh2D(meshes["trunk"], shaders["VertexColor"], modelMatrix);


	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(0, 0);
	RenderMesh2D(meshes["floor"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(30, 0);
	modelMatrix *= transform2D::Translate(moveX, moveY);
	modelMatrix *= transform2D::Translate(bodySide, 80);
	modelMatrix *= transform2D::Rotate(angularStep);
	modelMatrix *= transform2D::Translate(-bodySide, -80);
	// colturile dreptunghiului ce se gaseste in jurul ratei
	// colturile sunt denumite cu A, B, C, D incepand din coltul stanga jos
	// in ordinea inversa acelor de ceasornic
	rectangleAX = 30;
	rectangleAY = 0;
	rectangleBX = 250;
	rectangleBY = 0;
	rectangleCX = 250;
	rectangleCY = 160;
	rectangleDX = 30;
	rectangleDY = 160;
	rectangleAX -= bodySide;
	rectangleAY -= 80;
	rectangleAXNew = rectangleAX * cos(angularStep) - rectangleAY * sin(angularStep);
	rectangleAYNew = rectangleAY * cos(angularStep) + rectangleAX * sin(angularStep);
	rectangleAXNew += bodySide;
	rectangleAYNew += 80;
	rectangleBX -= bodySide;
	rectangleBY -= 80;
	rectangleBXNew = rectangleBX * cos(angularStep) - rectangleBY * sin(angularStep);
	rectangleBYNew = rectangleBY * cos(angularStep) + rectangleBX * sin(angularStep);
	rectangleBXNew += bodySide;
	rectangleBYNew += 80;
	rectangleCX -= bodySide;
	rectangleCY -= 80;
	rectangleCXNew = rectangleCX * cos(angularStep) - rectangleCY * sin(angularStep);
	rectangleCYNew = rectangleCY * cos(angularStep) + rectangleCX * sin(angularStep);
	rectangleCXNew += bodySide;
	rectangleCYNew += 80;
	rectangleDX -= bodySide;
	rectangleDY -= 80;
	rectangleDXNew = rectangleDX * cos(angularStep) - rectangleDY * sin(angularStep);
	rectangleDYNew = rectangleDY * cos(angularStep) + rectangleDX * sin(angularStep);
	rectangleDXNew += bodySide;
	rectangleDYNew += 80;

	//cioc
	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(30 + 2 * bodySide + 2 * headSide, 50 - beakSide / 2 + bodySide / 2);
	modelMatrix *= transform2D::Translate(moveX, moveY);
	modelMatrix *= transform2D::Translate(-bodySide - 2 * headSide, beakSide / 2);
	modelMatrix *= transform2D::Rotate(angularStep);
	modelMatrix *= transform2D::Translate(bodySide + 2 * headSide, -beakSide / 2);
	RenderMesh2D(meshes["beak"], shaders["VertexColor"], modelMatrix);

	// accesoriu
	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(30 + 2 * bodySide + headSide, 50 + bodySide / 2 + headSide + sqrt(80 * 80 - 40 * 40 / 4));
	modelMatrix *= transform2D::Translate(moveX, moveY);
	modelMatrix *= transform2D::Translate(-bodySide - headSide, -headSide - sqrt(80 * 80 - 40 * 40 / 4));
	modelMatrix *= transform2D::Rotate(angularStep);
	modelMatrix *= transform2D::Translate(bodySide + headSide, headSide + sqrt(80 * 80 - 40 * 40 / 4));
	if (cos(angularStep) < 0) {
		modelMatrix *= transform2D::Translate(0, -headSide - sqrt(80 * 80 - 40 * 40 / 4));
		modelMatrix *= transform2D::Rotate(3.14f);
		modelMatrix *= transform2D::Translate(0, headSide + sqrt(80 * 80 - 40 * 40 / 4));
	}
	RenderMesh2D(meshes["accessory"], shaders["VertexColor"], modelMatrix);

	// palarie
	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(30 + 2 * bodySide, 50 + bodySide / 2 + headSide);
	modelMatrix *= transform2D::Translate(moveX, moveY);
	modelMatrix *= transform2D::Translate(-bodySide, -headSide);
	modelMatrix *= transform2D::Rotate(angularStep);
	modelMatrix *= transform2D::Translate(bodySide, headSide);
	if (cos(angularStep) < 0) {
		modelMatrix *= transform2D::Translate(headSide, -headSide);
		modelMatrix *= transform2D::Rotate(3.14f);
		modelMatrix *= transform2D::Translate(-headSide, headSide);
	}
	modelMatrix *= transform2D::Rotate(-0.5);
	RenderMesh2D(meshes["hat"], modelMatrix, glm::vec3(red, green, blue));

	// cap
	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(30 + 2 * bodySide + headSide, 50 + bodySide / 2);
	modelMatrix *= transform2D::Translate(moveX, moveY);
	modelMatrix *= transform2D::Translate(-bodySide - headSide, 0);
	modelMatrix *= transform2D::Rotate(angularStep);
	modelMatrix *= transform2D::Translate(bodySide + headSide, 0);
	RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);

	// corp
	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(30, 50);
	modelMatrix *= transform2D::Translate(moveX, moveY);
	modelMatrix *= transform2D::Translate(bodySide, bodySide / 2);
	modelMatrix *= transform2D::Rotate(angularStep);
	modelMatrix *= transform2D::Translate(-bodySide, -bodySide / 2);
	RenderMesh2D(meshes["body"], modelMatrix, glm::vec3(red, green, blue));

	// aripa
	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(30, 125);
	modelMatrix *= transform2D::Translate(moveX, moveY);
	modelMatrix *= transform2D::Rotate(-0.9f);
	modelMatrix *= transform2D::Translate(wingX + bodySide / 8, wingY - bodySide / 8);
	modelMatrix *= transform2D::Rotate(angularStep);
	modelMatrix *= transform2D::Translate(-wingX - bodySide / 8, -wingY + bodySide / 8);
	// rotatia aripii
	if (movementTimeWing1 < 30 && currentSideWing1 == 0) {
		modelMatrix *= transform2D::Translate(wingX, wingY);
		modelMatrix *= transform2D::Rotate(0.285f);
		modelMatrix *= transform2D::Translate(-wingX, -wingY);
		movementTimeWing1++;
	}
	else {
		currentSideWing1 = 1;
	}
	if (currentSideWing1 == 1 && movementTimeWing1 > 0) {
		modelMatrix *= transform2D::Translate(wingX, wingY);
		modelMatrix *= transform2D::Rotate(-0.285f);
		modelMatrix *= transform2D::Translate(-wingX, -wingY);;
		movementTimeWing1--;
	}
	else {
		currentSideWing1 = 0;
	}
	RenderMesh2D(meshes["wing"], shaders["VertexColor"], modelMatrix);

	// aripa
	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(90, -5);
	modelMatrix *= transform2D::Translate(moveX, moveY);
	modelMatrix *= transform2D::Rotate(1);
	modelMatrix *= transform2D::Translate(wingX + bodySide / 4, wingY + bodySide / 4);
	modelMatrix *= transform2D::Rotate(angularStep);
	modelMatrix *= transform2D::Translate(-wingX - bodySide / 4, -wingY - bodySide / 4);
	// rotatia aripii
	if (movementTimeWing2 < 30 && currentSideWing2 == 0) {
		modelMatrix *= transform2D::Translate(wingX, wingY);
		modelMatrix *= transform2D::Rotate(-0.285f);
		modelMatrix *= transform2D::Translate(-wingX, -wingY);
		movementTimeWing2++;
	}
	else {
		currentSideWing2 = 1;
	}
	if (currentSideWing2 == 1 && movementTimeWing2 > 0) {
		modelMatrix *= transform2D::Translate(wingX, wingY);
		modelMatrix *= transform2D::Rotate(0.285f);
		modelMatrix *= transform2D::Translate(-wingX, -wingY);
		movementTimeWing2--;
	}
	else {
		currentSideWing2 = 0;
	}
	RenderMesh2D(meshes["wing"], shaders["VertexColor"], modelMatrix);

	// viata
	for (int i = 35; i <= lives * 40; i += 40) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(i, 700);
		RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);
	}

	// glont
	for (int i = 40; i <= 40 * bullets; i += 40) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(i, 650);
		modelMatrix *= transform2D::Rotate(1.57f);
		RenderMesh2D(meshes["bullet"], shaders["VertexColor"], modelMatrix);
	}

	// scor curent
	// am folosit translatie pentru a putea porni de la scorul 0
	for (int i = 0; i < 25 * currentScoreScale; i += 25) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= transform2D::Translate(1000 + i, 650);
		RenderMesh2D(meshes["currentScore"], shaders["VertexColor"], modelMatrix);
	}

	// scorul maxim de 10
	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(1000, 650);
	RenderMesh2D(meshes["maxScore"], shaders["VertexColor"], modelMatrix);

	// zapada
	// matrice de cercuri de dimensiunea ecranului care se misca in jos pe y
	// cand se ajunge la marginea de jos se reseteaza valoarea deplasarii
	for (int i = 8 * 90; i >= 0; i -= 90) {
		for (int j = 0; j <= 10 * 128; j += 128) {
			modelMatrix = glm::mat3(1);
			modelMatrix *= transform2D::Translate(j, i - moveSnow);
			RenderMesh2D(meshes["snow"], shaders["VertexColor"], modelMatrix);
			if (i - moveSnow == 0) {
				moveSnow = 0;
			}
		}
	}

	// cer
	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(0, 200);
	RenderMesh2D(meshes["sky"], shaders["VertexColor"], modelMatrix);

	// daca nu mai sunt gloante si rata nu a fost impuscata se ajunge in starea de eliberare
	if (bullets <= 0 && shot != 1) {
		time = 7;
	}
	// daca nu s a ajuns la timpul maxim de zbor pana in starea de eliberare si daca rata n a fost impuscata,
	// isi continua drumul normal
	if (time < 7 && shot != 1 && win != 1 && lose != 1 && nextLevel != 1) {
		if (moveX < 1120 && maximumX == 0) {
			moveX += valueX * deltaTimeSeconds;
		}
		else {
			if (maximumX == 0 && moveX >= 1120) {
				maximumX = 1;
				angularStep = 3.14 - angularStep;
			}
		}
		if (maximumX == 1 && moveX > 0) {
			moveX -= valueX * deltaTimeSeconds;
		}
		else {
			if (maximumX == 1) {
				angularStep = 3.14f - angularStep;
			}
			maximumX = 0;
		}

		if (moveY < 560 && maximumY == 0) {
			moveY += valueY * deltaTimeSeconds;
		}
		else {
			if (maximumY == 0 && moveY >= 560) {
				maximumY = 1;
				angularStep = -angularStep;
			}
		}
		if (maximumY == 1 && moveY > 0) {
			moveY -= valueY * deltaTimeSeconds;
		}
		else {
			if (maximumY == 1) {
				angularStep = -angularStep;
			}
			maximumY = 0;
		}
	}
	else {
		// daca rata n a fost impuscata inca, dar s a ajuns la timpul maxim pana la eliberare
		// se asteapta ca aceasta sa paraseasca ecranul si se reseteaza cu o noua rata
		if (shot != 1 && win != 1 && lose != 1 && nextLevel != 1) {
			moveY += valueY * deltaTimeSeconds;
			angularStep = 1.57f;
			if (moveY >= 720) {
				ResetDuck();
				lives--;
				if (lives == 0) {
					lose = 1;
				}
			}
		}
		// daca rata a fost impuscata
		if (shot == 1 && win != 1 && lose != 1 && nextLevel != 1) {
			moveY -= valueY * deltaTimeSeconds;
			angularStep = 3 * 1.57f;
			if (moveY <= 0) {
				ResetDuck();
				if (currentScoreScale < 10) {
					currentScoreScale += 1;
				}
				else {
					win = 1;
				}
			}
		}

	}
	if (nextLevelTransition <= 0) {
		nextLevel = 0;
	}
	if (currentScoreScale >= 10) {
		win = 1;
	}
	moveSnow++;
}

void Tema1::ResetDuck() {
	time = 0;
	ducks++;
	// daca s a ajuns la un numar multiplu de 5 de rate, se mareste valoarea
	if (ducks % 5 == 0) {
		nextLevel = 1;
		level++;
		moveX = rand() % (1280 + 1);
		moveY = 0;
		valueX += 70;
		valueY += 70;
	}
	else {
		moveX = rand() % (1280 + 1);
		moveY = 0;
		nextLevelTransition = 100;
	}
	// se calculeaza din nou unghiul
	hypotenuse = sqrt(valueY * valueY + valueX * valueX);
	angularStep = (float)asin((float)valueY / hypotenuse);
	maximumX = rand() % 2;
	if (maximumX == 1)
		angularStep = angularStep + 1.57;
	maximumY = 0;
	bullets = 3;
	shot = 0;
	red = (float)(rand() % 11) / 10;
	green = (float)(rand() % 11) / 10;
	blue = (float)(rand() % 11) / 10;
	// vieti extra
	if (red == 1) {
		lives++;
	}
	// gloante extra
	if (green == 1) {
		bullets++;
	}
}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
	// Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
	// Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	targetX = mouseX * 1280 / window->GetResolution().x;
	targetY = 720 - (mouseY * 720 / window->GetResolution().y);
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// daca rata n a fost inca impuscata si daca nu se afla in timpul pana la eliberare
	// atunci se mai pot trage gloante
	if (shot != 1 && time < 7 && win != 1 && lose != 1 && nextLevel != 1)
		bullets--;
	// rata poate fi impuscata doar daca exista un numar suficient de gloante, daca nu se afla in
	// perioada de timp pana la eliberare si daca nu a fost deja impuscata(starea de impuscat)
	if (mouseX * 1280 / window->GetResolution().x > std::min(std::min(rectangleAXNew, rectangleBXNew), std::min(rectangleCXNew, rectangleDXNew)) + moveX && mouseX * 1280 / window->GetResolution().x < std::max(std::max(rectangleAXNew, rectangleBXNew), std::max(rectangleCXNew, rectangleDXNew)) + moveX) {
		if (720 - (mouseY * 720 / window->GetResolution().y) > std::min(std::min(rectangleAYNew, rectangleBYNew), std::min(rectangleCYNew, rectangleDYNew)) + moveY && 720 - (mouseY * 720 / window->GetResolution().y) < std::max(std::max(rectangleAYNew, rectangleBYNew), std::max(rectangleCYNew, rectangleDYNew)) + moveY) {
			if (bullets > -1 && time < 7 && shot != 1 && nextLevel != 1) {
				shot = 1;
			}
		}
	}



}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
