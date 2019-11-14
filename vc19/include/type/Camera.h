#pragma once
#pragma message ("type/Camera Type is defined")

#include "core/SType.h"

#include <iostream>

#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>

class Camera : public SType
{
public:

	//Constructor and Destructor
	Camera();
	Camera(glm::vec3 position, glm::vec3 target);
	~Camera();

	//To String, Print and Set With String
	std::string toString(std::string options) const override;
	std::string print(std::string options) const override;
	void setWithString(std::string str) override;

	//Static Functions : Cast and New
	static Camera* cast(SType* obj);
	static SType* newType(std::vector<std::string> args);

	//Position and Target
	void setPosition(glm::vec3 pos);
	void setTarget(glm::vec3 target);
	glm::vec3 getPosition() const;
	glm::vec3 getTarget() const;

	//Perspective and Orthographic
	void setPerspective(float width, float height, float radius, float near, float far);
	void setOrthographicBox(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);
	void setOrthographic(float width, float height, float near, float far);

	//Get ProjView
	glm::mat4 getProjViewMatrix();
private:
	glm::vec3 m_position;
	glm::vec3 m_target;
	glm::mat4 m_projView;
};

