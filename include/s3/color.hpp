#pragma once

#include <glm/glm.hpp>

namespace s3 {

/**
 * @brief stores a color
 */
class color {
public:
	/**
	 * @brief initialize with black
	 *
	 */
	color();

	/**
	 * @brief Create a color with a greyscale value normalized from 0-1
	 *
	 * @param c the color to set r, g, and b to
	 * @param a alpha channel
	 */
	static color grey_norm(float c, float a = 1);

	/**
	 * @brief Create a color with a greyscale value non-normalized from 0-255
	 *
	 * @param c the color to set r, g, and b to
	 * @param a alpha channel
	 */
	static color grey_int(int c, int a = 255);

	/**
	 * @brief Create a color given the normalized 0-1 rgba channels.
	 *
	 * @param r red
	 * @param g green
	 * @param b blue
	 * @param a alpha
	 * @return the color object
	 */
	static color from_norm(float r, float g, float b, float a = 1);

	/**
	 * @brief Create a color given the normalized 0-1 rgba channels.
	 *
	 * @param v the rgba vector
	 * @return the color object
	 */
	static color from_norm(glm::vec4 v);

	/**
	 * @brief Create a color given the normalized 0-1 rgba channels.
	 *
	 * @param v the rgb vector
	 * @remarks a = 1.0
	 * @return the color object
	 */
	static color from_norm(glm::vec3 v);

	/**
	 * @brief Create a color given the non-normalized 0-255 rgba channels.
	 *
	 * @param r red
	 * @param g green
	 * @param b blue
	 * @param a alpha
	 * @return the color object
	 */
	static color from_ints(int r, int g, int b, int a = 255);

	/**
	 * @brief Create a color given the non-noramlized 0-255 rgba channels.
	 *
	 * @param v the rgba vector
	 * @return the color object
	 */
	static color from_ints(glm::vec4 v);

	/**
	 * @brief Create a color given the non-noramlized 0-255 rgba channels.
	 *
	 * @param v the rgb vector
	 * @remarks a = 255
	 * @return the color object
	 */
	static color from_ints(glm::vec3 v);

	/// cast to a vec4 (normalized from 0-1)
	operator glm::vec4() const;
	/// cast to a vec3 (normalized from 0-1)
	operator glm::vec3() const;

	float r;
	float g;
	float b;
	float a;

private:
	/**
	 * @brief initialize with normalized rgb values
	 *
	 */
	color(float r, float g, float b, float a = 1);
};

}
