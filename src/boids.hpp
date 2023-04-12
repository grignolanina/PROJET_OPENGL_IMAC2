#pragma once

#include "glm/fwd.hpp"
#include "p6/p6.h"

class Boid{
	private:
	glm::vec2 m_pos;
	glm::vec3 m_color;
	float m_size;
	glm::vec2 m_speed;	

	public :
	/// \brief default constructor
	Boid();

	/// \brief constructor with param
	/// \param pos position of boid
	/// \param color color of boid
	/// \param size size of boid
	/// \param speed speed of boid
	Boid(glm::vec2 pos, glm::vec3 color, float size, glm::vec2 speed);

	/// \brief constructor random
	/// \param aspectRatio window ratio
	explicit Boid(float aspecRatio);

	/// \brief destructor
	// ~Boid();


	//constructeur classique et fonction libre qui met random
	//add par defaut
	//destructeur

	/// \brief draw boid in p6 window
	/// \param ctx the p6 context of creation
	void drawBoid(p6::Context& ctx) const;

	/// \brief update behavior and position of all boids in the tab
	/// \param ctx the p6 context of creation
	/// \param boidsTab tab of boids
	/// \param sRadius radius of separation
	/// \param cRadius radius of cohesion
	/// \param aRadius radius of alignement
	void updateBoid(p6::Context& ctx, std::vector<Boid>& boidsTab, float sRadius, float cRadius, float aRadius);

	/// \brief verify if the boids stay in the windows
	/// \param ctx the p6 context of creation
	void stayInWindows(p6::Context& ctx);

	/// \brief update behavior and position of all boids in the tab
	/// \param boidsTab tab of boids
	/// \param sRadius radius of separation
	void separationBoids(std::vector<Boid>& boidsTab, float sRadius);

	/// \brief update behavior and position of all boids in the tab
	/// \param boidsTab tab of boids
	/// \param cRadius radius of cohesion
	void cohesionBoids(std::vector<Boid>& boidsTab, float cRadius);

	/// \brief update behavior and position of all boids in the tab
	/// \param boidsTab tab of boids
	/// \param aRadius radius of alignement
	void alignmentBoids(std::vector<Boid>& boidsTab, float aRadius);

	/// \brief change pos of one boid randomly
	/// \param aspectRatio windows ratio
	void randomPos(float aspectRatio);

	///\brief change color of one boid randomly
	void randomColor();

	///\brief change speed of one boid randomly
	void randomSpeed();

};

/// \brief return one boid with random caracteristic
/// \param aspectRatio windows ratio
Boid randomBoids(float aspectRatio);


