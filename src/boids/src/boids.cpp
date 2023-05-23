#include "../src/boids/include/boids.hpp"
#include <cstdlib>
// #include <cstdlib.h>
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "p6/p6.h"

static constexpr glm::vec3 speedMax       = glm::vec3(0.02f, 0.02f, 0.02f);
static constexpr float     maxForce       = 0.01f;
static constexpr float     cohesionWeight = 0.5f;

Boid::Boid()
    : m_pos(glm::vec3(0., 0., 0.)), m_color(glm::vec3(1., 1., 1.)), m_size(0.2), m_speed(glm::vec3(0.02, 0.02, 0.02))
{
}

Boid::Boid(glm::vec3 pos, glm::vec3 color, float size, glm::vec3 speed)
    : m_pos(pos), m_color(color), m_size(size), m_speed(speed)
{
}

Boid::Boid(float aspectRatio)
    : m_pos(glm::vec3{p6::random::number(-aspectRatio, aspectRatio), p6::random::number(-1, 1), p6::random::number(-2, 2)}), m_color(glm::vec3{p6::random::number(0, 1), p6::random::number(0, 1), p6::random::number(0, 1)}),
    // m_color(glm::vec3{0., 0., 1.}),
    m_size(0.2)
    , m_speed(p6::random::number(0., 0.02), p6::random::number(0., 0.02), p6::random::number(0., 0.02))
{
}

void Boid::drawBoid(p6::Context& ctx) const
{
    ctx.fill = {this->m_color.x, this->m_color.y, this->m_color.z};
    ctx.circle(p6::Center{this->m_pos.x, this->m_pos.y}, p6::Radius(this->m_size));
    ctx.use_stroke = false;
}

// void Boid::drawBoid3D(Model &model, glm::mat4 ProjMatrix, glm::mat4 NormalMatrix, GLint uMVPMatrix, GLint uMVMatrix, GLint uNormalMatrix, glm::mat4 viewMatrix){

//     glm::mat4 MVMatrixBoids = glm::translate(glm::mat4{1.f}, {0.f, 0.f, -3.f}); // Translation
//     // // MVMatrixBoids = glm::rotate(MVMatrixBoids, ctx.time(), glm::normalize(this->m_speed)); // Translation * Rotation
//     MVMatrixBoids = glm::translate(MVMatrixBoids, this->m_pos); // Translation * Rotation * Translation

//     //glm::mat4 MVMatrixBoids = glm::translate(glm::mat4{1.f}, this->m_pos); // Translation

//     MVMatrixBoids = glm::scale(MVMatrixBoids, glm::vec3{this->m_size}); // Translation * Rotation * Translation * Scale
//     MVMatrixBoids = viewMatrix*MVMatrixBoids;
//     glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrixBoids));
//     glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrixBoids));
//     glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

//     model.draw();

// }

void Boid::drawBoid3D(Model& model, glm::mat4 ProjMatrix, glm::mat4 NormalMatrix, glm::mat4 viewMatrix, Program& program, GLuint textName)
{
    glm::mat4 MVMatrixBoids = glm::translate(glm::mat4{1.f}, {0.f, 0.f, -3.f});                        // Translation
    MVMatrixBoids           = glm::rotate(MVMatrixBoids, glm::radians(180.0f), glm::vec3(0., 1., 0.)); // Translation * Rotation
    MVMatrixBoids           = glm::translate(MVMatrixBoids, this->m_pos);                              // Translation * Rotation * Translation

    // glm::mat4 MVMatrixBoids = glm::translate(glm::mat4{1.f}, this->m_pos); // Translation

    MVMatrixBoids = glm::scale(MVMatrixBoids, glm::vec3{this->m_size}); // Translation * Rotation * Translation * Scale
    MVMatrixBoids = viewMatrix * MVMatrixBoids;

    program.uniform1i("uText", 0);
    program.uniformMatrix4fv("uMVPMatrix", ProjMatrix * MVMatrixBoids);
    program.uniformMatrix4fv("uMVMatrix", MVMatrixBoids);
    program.uniformMatrix4fv("uNormalMatrix", NormalMatrix);
    // glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrixBoids));
    // glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrixBoids));
    // glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

    model.drawArray(textName);
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

void Boid::stayInWindows(p6::Context& ctx)
{
    if (m_pos.x < -ctx.aspect_ratio() + m_size)
    {
        m_speed.x += 0.05;
    }
    if (m_pos.x > ctx.aspect_ratio() - m_size)
    {
        m_speed.x -= 0.05;
    }
    if (m_pos.y < m_size)
    {
        m_speed.y += 0.05;
    }
    if (m_pos.y > 2 - m_size)
    {
        m_speed.y -= 0.05;
    }
    if (m_pos.z < -1 + m_size)
    {
        m_speed.z += 0.05;
    }
    if (m_pos.z > 1 - m_size)
    {
        m_speed.z -= 0.05;
    }
}

void Boid::separationBoids(std::vector<Boid>& boidsTab, float sRadius)
{
    glm::vec3 newDisplacement{0.0f, 0.0f, 0.0f};
    int       count = 0;
    for (auto& elem : boidsTab)
    {
        if (&elem == this)
            continue;

        float distance = glm::length(elem.m_pos - this->m_pos);

        if (distance < sRadius)
        {
            glm::vec3 difference = glm::normalize(this->m_pos - elem.m_pos);
            difference /= distance;
            newDisplacement += difference;
            count++;
        }
    }
    if (count > 0)
    {
        newDisplacement /= count;
        if (length(newDisplacement) > maxForce)
        {
            newDisplacement = glm::normalize(newDisplacement) * maxForce;
        }
        m_speed = newDisplacement;
    }
}

void Boid::cohesionBoids(std::vector<Boid>& boidsTab, float cRadius)
{
    glm::vec3 newPosition{0.0f, 0.0f, 0.0f};
    int       count = 0;

    for (auto& elem : boidsTab)
    {
        if (&elem == this)
            continue;
        float distance = glm::length(elem.m_pos - this->m_pos);
        if (distance < cRadius)
        {
            newPosition += (elem.m_pos - m_pos) * cohesionWeight;
            count++;
        }
    }

    if (count > 0)
    {
        newPosition /= count;

        if (length(newPosition) > maxForce)
        {
            newPosition = glm::normalize(newPosition) * maxForce;
        }

        m_speed += (newPosition)*maxForce;
    }
}

void Boid::alignmentBoids(std::vector<Boid>& boidsTab, float aRadius)
{
    glm::vec3 newVelocity{0.0f, 0.0f, 0.0f};
    int       count = 0;

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
        if (length(newVelocity) > maxForce)
        {
            newVelocity = glm::normalize(newVelocity);
            m_speed     = newVelocity * speedMax;
        }
    }
}

Boid randomBoids(float aspectRatio)
{
    Boid T = Boid();
    T.randomPos(aspectRatio);
    T.randomColor();
    T.randomSpeed();
    return T;
}

void Boid::randomPos(float aspectRatio)
{
    this->m_pos = glm::vec3({p6::random::number(-aspectRatio, aspectRatio), p6::random::number(-1, 1), p6::random::number(-2, 2)});
}

void Boid::randomColor()
{
    this->m_color = glm::vec3({p6::random::number(0, 1), p6::random::number(0, 1), p6::random::number(0, 1)});
}

void Boid::randomSpeed()
{
    this->m_speed = glm::vec3(p6::random::number(0., 0.02), p6::random::number(0., 0.02), p6::random::number(0., 0.02));
}
