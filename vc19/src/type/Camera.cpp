#include "type/Camera.h"

//Camera by Default
Camera::Camera() : SType()
{
	m_position = glm::vec3(0, 0, 0);
	m_target = glm::vec3(0, 0, 1);
	m_projView = glm::mat4(0);
}

//Camera with position and target
Camera::Camera(glm::vec3 position, glm::vec3 target)
{
	m_position = position;
	m_target = target;
	m_projView = glm::mat4(0);
}

//Destructor
Camera::~Camera()
{

}

//To String
std::string Camera::toString(std::string options) const
{
	return "";
}

//Print
std::string Camera::print(std::string options) const
{
	return "";
}

//Set With String
void Camera::setWithString(std::string str)
{

}

//Cast
Camera* Camera::cast(SType* obj)
{
	return nullptr;
}

//New Shader
SType* Camera::newType(std::vector<std::string> args)
{
	return nullptr;
}

//Set Position
void Camera::setPosition(glm::vec3 pos)
{
	m_position = pos;
}

//Set Target
void Camera::setTarget(glm::vec3 target)
{
	m_target = target;
}

//Get Position
glm::vec3 Camera::getPosition() const
{
	return m_position;
}

//Get Target
glm::vec3 Camera::getTarget() const
{
	return m_target;
}

//Set Perspective
void Camera::setPerspective(float width, float height, float radius, float near, float far)
{
	//Projection
	glm::mat4 projection = glm::perspective(glm::radians(radius), width / height, near, far);

	//View
	glm::mat4 view = glm::lookAt(m_position, m_target, glm::vec3(0, 1, 0));
	//view = glm::rotate(view, 3.14159265359f, glm::vec3(0.0f, 0.0f, 1.0f));

	//Set
	m_projView = projection * view;
}

//Set Orthographic
void Camera::setOrthographicBox(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
{
	glm::mat4 projection = glm::ortho(xMin, xMax, yMin, yMax, zMin, zMax);
	glm::mat4 view = glm::lookAt(m_position, m_target, glm::vec3(0, 1, 0));

	m_projView = projection * view;
}

//Set Orthographic
void Camera::setOrthographic(float width, float height, float near, float far)
{
	m_projView = glm::ortho(0.0f, width, height, 0.0f, near, far);
}

//Get Projection View Matrix
glm::mat4 Camera::getProjViewMatrix()
{
	return m_projView;
}
