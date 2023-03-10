#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
	const std::string& name,
	glm::vec3 leftBottomCorner,
	float length,
	glm::vec3 color,
	bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(2 * length, 0, 0), color),
		VertexFormat(corner + glm::vec3(2 * length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned int> indices = { 0, 1, 2, 3 };

	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* object2D::CreateTriangle(
	const std::string& name,
	glm::vec3 leftBottomCorner,
	float length,
	glm::vec3 color,
	bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner + glm::vec3(0, length, 0), color),
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, length / 2, 0), color)
	};

	Mesh* triangle = new Mesh(name);
	std::vector<unsigned int> indices = { 0, 1, 2 };

	triangle->InitFromData(vertices, indices);
	return triangle;
}

Mesh* object2D::CreateCircle(
	const std::string& name,
	glm::vec3 leftBottomCorner,
	float length,
	glm::vec3 color,
	bool fill)
{
	glm::vec3 corner = leftBottomCorner;
	float corner2 = 0;
	float corner3 = 0;


	std::vector<VertexFormat> vertices;
	VertexFormat v = { glm::vec3(0, 0, 0), color };
	vertices.push_back(v);
	for (float i = 0; i <= 6.28; i += 0.0002) {
		VertexFormat v = { glm::vec3(cos(i) * length, sin(i) * length, 0), color };
		vertices.push_back(v);
	}

	Mesh* circle = new Mesh(name);
	std::vector<unsigned int> indices;
	for (int i = 0; i < 6.28 / 0.0002 - 1; i++) {
		indices.push_back(i + 1);
		indices.push_back(i + 2);
		indices.push_back(0);
	}
	indices.push_back(6.28 / 0.0002);
	indices.push_back(1);
	indices.push_back(0);

	circle->InitFromData(vertices, indices);
	return circle;
}

Mesh* object2D::CreateBody(
	const std::string& name,
	glm::vec3 leftBottomCorner,
	float length,
	glm::vec3 color,
	bool fill)
{
	glm::vec3 corner = leftBottomCorner;
	float corner2 = 0;
	float corner3 = 0;


	std::vector<VertexFormat> vertices = {
		VertexFormat(corner + glm::vec3(0, length, 0), color),
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(2 * length, length / 2, 0), color)
	};

	Mesh* body = new Mesh(name);
	std::vector<unsigned int> indices = { 0, 1, 2 };

	body->InitFromData(vertices, indices);
	return body;
}

Mesh* object2D::CreateFloor(
	const std::string& name,
	glm::vec3 leftBottomCorner,
	float length,
	glm::vec3 color,
	bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(1280, 0, 0), color),
		VertexFormat(corner + glm::vec3(1280, 200, 0), color),
		VertexFormat(corner + glm::vec3(0, 200, 0), color)
	};

	Mesh* floor = new Mesh(name);
	std::vector<unsigned int> indices = { 0, 1, 2, 3 };

	if (!fill) {
		floor->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		indices.push_back(0);
		indices.push_back(2);
	}

	floor->InitFromData(vertices, indices);
	return floor;
}

Mesh* object2D::CreateSky(
	const std::string& name,
	glm::vec3 leftBottomCorner,
	float length,
	glm::vec3 color,
	bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(1280, 0, 0), color),
		VertexFormat(corner + glm::vec3(1280, 550, 0), color),
		VertexFormat(corner + glm::vec3(0, 550, 0), color)
	};

	Mesh* sky = new Mesh(name);
	std::vector<unsigned int> indices = { 0, 1, 2, 3 };

	if (!fill) {
		sky->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		indices.push_back(0);
		indices.push_back(2);
	}

	sky->InitFromData(vertices, indices);
	return sky;
}

Mesh* object2D::CreateScore(
	const std::string& name,
	glm::vec3 leftBottomCorner,
	float length,
	glm::vec3 color,
	bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(10 * length, 0, 0), color),
		VertexFormat(corner + glm::vec3(10 * length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* score = new Mesh(name);
	std::vector<unsigned int> indices = { 0, 1, 2, 3 };

	if (!fill) {
		score->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		indices.push_back(0);
		indices.push_back(2);
	}

	score->InitFromData(vertices, indices);
	return score;
}

Mesh* object2D::CreateCurrentScore(
	const std::string& name,
	glm::vec3 leftBottomCorner,
	float length,
	glm::vec3 color,
	bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* currentScore = new Mesh(name);
	std::vector<unsigned int> indices = { 0, 1, 2, 3 };

	if (!fill) {
		currentScore->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		indices.push_back(0);
		indices.push_back(2);
	}

	currentScore->InitFromData(vertices, indices);
	return currentScore;
}

Mesh* object2D::CreateTarget(
	const std::string& name,
	glm::vec3 leftBottomCorner,
	float length,
	glm::vec3 color,
	bool fill)
{
	glm::vec3 corner = leftBottomCorner;
	float corner2 = 0;
	float corner3 = 0;


	std::vector<VertexFormat> vertices;
	Mesh* target = new Mesh(name);
	std::vector<unsigned int> indices;
	if (!fill) {
	VertexFormat v = { glm::vec3(0, 0, 0) };
	vertices.push_back(v);
	for (float i = 0; i <= 6.28; i += 0.0002) {
		VertexFormat v = { glm::vec3(cos(i) * length, sin(i) * length, 0), color };
		vertices.push_back(v);
	}

	for (int i = 0; i < 6.28 / 0.0002 - 1; i++) {
		indices.push_back(i + 1);
		indices.push_back(i + 2);
	}

	indices.push_back(6.28 / 0.0002);
	indices.push_back(1);
		target->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		VertexFormat v = { glm::vec3(0, 0, 0) };
		vertices.push_back(v);
		for (float i = 0; i <= 6.28; i += 0.0002) {
			VertexFormat v = { glm::vec3(cos(i) * length, sin(i) * length, 0), color };
			vertices.push_back(v);
		}

		for (int i = 0; i < 6.28 / 0.0002 - 1; i++) {
			indices.push_back(i + 1);
			indices.push_back(i + 2);
			indices.push_back(0);
		}

		indices.push_back(6.28 / 0.0002);
		indices.push_back(1);
		indices.push_back(0);
	}


	target->InitFromData(vertices, indices);
	return target;
}

Mesh* object2D::CreateTree(
	const std::string& name,
	glm::vec3 leftBottomCorner,
	float length,
	glm::vec3 color,
	bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length / 2, length / 2, 0), color)
	};

	Mesh* triangle = new Mesh(name);
	std::vector<unsigned int> indices = { 0, 1, 2 };

	if (!fill) {
		triangle->SetDrawMode(GL_LINE_LOOP);
	}

	triangle->InitFromData(vertices, indices);
	return triangle;
}

Mesh* object2D::CreateTrunk(
	const std::string& name,
	glm::vec3 leftBottomCorner,
	float length,
	glm::vec3 color,
	bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(0, 2*length, 0), color),
		VertexFormat(corner + glm::vec3(length, 2*length, 0), color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned int> indices = { 0, 1, 2, 3 };

	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* object2D::CreateRectangle(
	const std::string& name,
	glm::vec3 leftBottomCorner,
	float length,
	float length2,
	glm::vec3 color,
	bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length2, 0), color),
		VertexFormat(corner + glm::vec3(0, length2, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned int> indices = { 0, 1, 2, 3 };

	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}



