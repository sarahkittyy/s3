#pragma once

#include <vector>

#include <s3/camera.hpp>
#include <s3/material.hpp>
#include <s3/shader.hpp>
#include <s3/transform.hpp>

#include <s3/light/dir.hpp>
#include <s3/light/point.hpp>
#include <s3/light/spot.hpp>

namespace s3 {

class shader;
class camera;

/// stores the state of a render (shader, texture, etc)
class drawstate {
public:
	drawstate();

	/// transform to be used as the model matrix in the defualt shader
	s3::transform transform;
	/// shader to render this object with
	s3::shader* shader;
	/// camera to use
	s3::camera* camera;
	/// material to use
	const s3::material* material;

	/// add a pointlight to the scene
	void add_pointlight(light::point& pl);
	/// retrieve all pointlights
	std::vector<light::point*>& get_pointlights();
	/// retrieve a specific pointlight
	light::point* get_pointlight(int i);
	/// returns how many pointlights there are
	size_t pointlight_count() const;
	/// clear pointlights
	void clear_pointlights();

	/// add a dirlight to the scene
	void add_dirlight(light::dir& pl);
	/// retrieve all dirlights
	std::vector<light::dir*>& get_dirlights();
	/// retrieve a specific dirlight
	light::dir* get_dirlight(int i);
	/// returns how many dirlights there are
	size_t dirlight_count() const;
	/// clear dirlights
	void clear_dirlights();

	/// add a spotlight to the scene
	void add_spotlight(light::spot& pl);
	/// retrieve all spotlights
	std::vector<light::spot*>& get_spotlights();
	/// retrieve a specific spotlight
	light::spot* get_spotlight(int i);
	/// returns how many spotlights there are
	size_t spotlight_count() const;
	/// clear spotlights
	void clear_spotlights();

	/// clear all lights
	void clear_lights();

private:
	/// point lights
	std::vector<light::point*> m_pointlights;
	/// directional lights
	std::vector<light::dir*> m_dirlights;
	/// spotlights
	std::vector<light::spot*> m_spotlights;
};

}
