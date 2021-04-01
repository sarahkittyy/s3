#pragma once

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
	 * @brief Create a color given the non-normalized 0-255 rgba channels.
	 *
	 * @param r red
	 * @param g green
	 * @param b blue
	 * @param a alpha
	 * @return the color object
	 */
	static color from_ints(int r, int g, int b, int a = 255);

	float r;
	float g;
	float b;
	float a;

private:
	/**
	 * @brief initialize with rgb values
	 *
	 */
	color(float r, float g, float b, float a = 1);
};

}
