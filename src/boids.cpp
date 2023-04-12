#include "boids.hpp"
#include <stdlib.h>
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "p6/p6.h"




static constexpr glm::vec2 speedMax= glm::vec2(0.02f, 0.02f);
static constexpr float maxForce =0.01f;
static constexpr float cohesionWeight = 0.5f;

Boid::Boid():
m_pos(glm::vec2(0., 0.)),
m_color(glm::vec3(1., 1., 1.)),
m_size(0.02),
m_speed(0.02)
{
}

Boid::Boid(glm::vec2 pos, glm::vec3 color, float size, glm::vec2 speed):
m_pos(pos),
m_color(color),
m_size(size),
m_speed(speed)
{
}


Boid::Boid(float aspectRatio)
    : 
    m_pos(glm::vec2{p6::random::number(-aspectRatio, aspectRatio), p6::random::number(-1, 1)}), 
    m_color(glm::vec3{p6::random::number(0, 1), p6::random::number(0, 1), p6::random::number(0, 1)}), 
    // m_color(glm::vec3{0., 0., 1.}), 
    m_size(0.02), 
    m_speed(p6::random::number(0., 0.02), p6::random::number(0., 0.02))
{
}

void Boid::drawBoid(p6::Context& ctx) const
{
    ctx.fill = {this->m_color.x, this->m_color.y, this->m_color.z};
    ctx.circle(p6::Center{this->m_pos.x, this->m_pos.y}, p6::Radius(this->m_size));
    ctx.use_stroke = false;
}

void Boid::updateBoid(p6::Context& ctx, std::vector<Boid>& boidsTab, float sRadius, float cRadius, float aRadius)
{

    for (auto& elem : boidsTab)
    {
        elem.alignmentBoids(boidsTab, aRadius); 
        elem.separationBoids(boidsTab, sRadius);
        elem.cohesionBoids(boidsTab, cRadius);
    }
    m_pos += m_speed;
    this->stayInWindows(ctx);

}

void Boid::stayInWindows(p6::Context& ctx){
    if(m_pos.x < -ctx.aspect_ratio()+m_size){
        m_speed.x += 0.05;
    }
    if(m_pos.x >ctx.aspect_ratio()-m_size){
        m_speed.x -= 0.05;
    }
    if(m_pos.y < -1+m_size){
        m_speed.y += 0.05;
    }
    if(m_pos.y > 1-m_size){
        m_speed.y -=0.05;
    }
}




void Boid::separationBoids(std::vector<Boid>& boidsTab, float sRadius)
{
    glm::vec2 newDisplacement{0.0f, 0.0f};
    int count = 0;
    for (auto& elem : boidsTab)
    {
        if (&elem == this)
            continue;

        float distance = glm::length(elem.m_pos - this->m_pos);

        if (distance < sRadius)
        {
                glm::vec2 difference = glm::normalize(this->m_pos-elem.m_pos);
                difference /= distance;
                newDisplacement += difference;
                count++;
        }
    }
    if (count > 0)
    {
        newDisplacement /= count;
        if (length(newDisplacement)>maxForce){
            newDisplacement = glm::normalize(newDisplacement)*maxForce;
        }
        m_speed = newDisplacement;
    }
}

void Boid::cohesionBoids(std::vector<Boid>& boidsTab, float cRadius)
{
    glm::vec2 newPosition{0.0f, 0.0f};
    int count = 0;

    for (auto& elem : boidsTab)
    {
        if (&elem == this)
            continue;
        float distance = glm::length(elem.m_pos - this->m_pos);
        if (distance < cRadius)
        {
            newPosition += (elem.m_pos -m_pos)* cohesionWeight;
            count++;
        }
    }

    if (count > 0)
    {
        newPosition /= count;

        if (length(newPosition)>maxForce){
            newPosition = glm::normalize(newPosition)*maxForce;
        }

        m_speed += (newPosition)*maxForce;
    }
}

void Boid::alignmentBoids(std::vector<Boid>& boidsTab, float aRadius)
{
    glm::vec2 newVelocity{0.0f, 0.0f};
    int count = 0;

    for (auto& elem : boidsTab)
     {
       const float distance = glm::length(elem.m_pos - this->m_pos);
        if (distance < aRadius)
        {
            newVelocity += elem.m_speed;
            count++;
        }
    }

    if (count > 0)
    {
        newVelocity /= count;
        if(length(newVelocity)>maxForce){
            newVelocity = glm::normalize(newVelocity);
            m_speed            = newVelocity * speedMax;
        }
    }
}

Boid randomBoids(float aspectRatio){
    Boid T = Boid();
    T.randomPos(aspectRatio);
    T.randomColor();
    T.randomSpeed();
    return T;
}


void Boid::randomPos(float aspectRatio){
    this->m_pos = glm::vec2({p6::random::number(-aspectRatio, aspectRatio), p6::random::number(-1, 1)});
} 
    
void Boid::randomColor(){
    this->m_color = glm::vec3({p6::random::number(0, 1), p6::random::number(0, 1), p6::random::number(0, 1)});
}


void Boid::randomSpeed(){
    this->m_speed = glm::vec2(p6::random::number(0., 0.02), p6::random::number(0., 0.02));
}