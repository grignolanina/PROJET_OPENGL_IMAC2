#include "camera.hpp"

#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/trigonometric.hpp"
#include "player.hpp"
#include <p6/p6.h>
#include <cmath>



Camera::Camera(Player& player):m_player(player),m_horizontal(0.0f),m_vertical(0.0f),m_distance(1.f){}

Camera::Camera(Player& player, GLfloat horizontal, GLfloat vertical, GLfloat distance):m_player(player), m_horizontal(horizontal), m_vertical(vertical), m_distance(distance) {
	
};

void Camera::setDistance(GLfloat distance){
    m_distance=distance;
}

GLfloat Camera::getDistance()const{
    return m_distance;
}

void Camera::setHorizontal(float angle){
    m_horizontal=angle;
}
void Camera::setVertical(float angle){
    m_vertical=angle;
}

GLfloat Camera::getHorizontal()const{
    return m_horizontal;
}
GLfloat Camera::getVertical()const{
    return m_vertical;
}

void Camera::moveRight(float amount){
    // glm::vec3 position = {amount * sin((m_horizontal + 90.0f) * M_PI / 180.0f), 0.0f, -amount * cos((m_horizontal + 90.0f) * M_PI / 180.0f)};
    glm::vec3 position = {amount * glm::sin((m_horizontal + 90.0f) * p6::PI / 180.0f), 0.0f, -amount * cos((m_horizontal + 90.0f) * p6::PI / 180.0f)};
	m_player.move(position);
}

void Camera::moveFront(float amount){
    glm::vec3 position ={amount * sin(m_horizontal * p6::PI / 180.0f), 0.0f, -amount * cos(m_horizontal * p6::PI / 180.0f)};
    m_player.move(position);
}


void Camera::rotateHorizontal(float angle){
	m_horizontal += angle;
	
}
void Camera::rotateVertical(float angle){
	m_vertical += glm::radians(angle);
    if (m_vertical>p6::PI/2.0f){
        m_vertical=p6::PI/2.0f;
    }
	
}

glm::mat4 Camera::update(){
    
    glm::vec3 position;
    position.x = m_player.getPosition().x + m_distance * sin(m_horizontal * p6::PI / 180.0f) * cos(m_vertical * p6::PI / 180.0f);
    position.y = m_player.getPosition().y + m_distance * sin(m_vertical * p6::PI / 180.0f);
    position.z = m_player.getPosition().z + m_distance * cos(m_horizontal * p6::PI / 180.0f) * cos(m_vertical * p6::PI / 180.0f);
    

    return glm::lookAt(position, m_player.getPosition(),glm::vec3(0.0f, 1.0f, 0.f));
}


void cameraOption(Camera &camera, bool &left, bool &right, bool &up, bool &down, p6::Context& ctx)	{
        if(right){
            camera.moveRight(0.05f);
        }
        if(left){
            camera.moveRight(-0.05f);
        }
        if(up){
            camera.moveFront(0.05f);
        }
        if(down){
            camera.moveFront(-0.05f);
        }

        ctx.key_pressed = [&right, &up, &left, &down](const p6::Key& key){
            if(key.logical == "d"){
                right = true;
            }
            if(key.logical == "q"){
                left = true;
            }
            if(key.logical == "z"){
                up = true;
            }
            if(key.logical == "s"){
                down = true;
            }

        };

        ctx.key_released = [&right, &up, &left, &down](const p6::Key& key){
            if(key.logical == "d"){
                right = false;
            }
            if(key.logical == "q"){
                left = false;
            }
            if(key.logical == "z"){
                up = false;
            }
            if(key.logical == "s"){
                down = false;
            }
        };

        ctx.mouse_dragged = [&camera](const p6::MouseDrag& button) {
            camera.rotateHorizontal(button.delta.x * 5);
            camera.rotateVertical(-button.delta.y * 5);
        };

        ctx.mouse_scrolled = [&](p6::MouseScroll scroll){

            camera.moveFront(-scroll.dy);
        };

		
	
	
        

}