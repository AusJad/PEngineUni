#pragma once

#include "ThirdParty/include/glm/glm.hpp"
#include "ThirdParty/include/glm/gtx/transform.hpp"
#include "ThirdParty/include/glm/ext.hpp"
#include "ThirdParty/include/glm/gtc/type_ptr.hpp"


class vec4{
private:
glm::vec4 vector;

public:
vec4::vec4()
{

}

vec4::vec4(float a, float b, float c, float d)
{
	vector[0] = a;
	vector[1] = b;
	vector[2] = c;
	vector[3] = d;
}

vec4::vec4(const vec4 & v)
{
	vector = v.getVec();
}

vec4::vec4(const glm::vec4 & v)
{
	vector = v;
}

glm::vec4 vec4::getVec() const
{
	return vector;
}

void vec4::setVec(glm::vec4 vec)
{
	vector = vec;
}

void vec4::add(vec4 vec)
{
	vector[0] = vector[0] + vec.getVec()[0];
	vector[1] = vector[1] + vec.getVec()[1];
	vector[2] = vector[2] + vec.getVec()[2];
	vector[3] = vector[3] + vec.getVec()[3];
}

float vec4::x() const
{
	return vector[0];
}

float vec4::y() const
{
	return vector[1];
}

float vec4::z() const
{
	return vector[2];
}

float vec4::w() const
{
	return vector[3];
}

float vec4::sx(float nx)
{
	vector[0] = nx;
	return vector[0];
}

float vec4::sy(float ny)
{
	vector[1] = ny;
	return vector[1];
}

float vec4::sz(float nz)
{
	vector[2] = nz;
	return vector[2];
}

float vec4::sw(float nw)
{
	vector[3] = nw;
	return vector[4];
}

vec4 vec4::normalise()
{
	return vec4(glm::normalize(vector));
}

void vec4::normailse()
{
	glm::normalize(vector);
}

float vec4::dot(const vec4 & v)
{
	return glm::dot(vector, v.getVec());
}

float vec4::angle(const vec4 & v)
{
	return glm::angle(vector, v.getVec());
}

float& vec4::operator[] (int x)
{
	return vector[x];
}

vec4 vec4::operator* (vec4 vec2)
{
	return vec4(vector * vec2.getVec());
}

vec4 vec4::operator += (const vec4 & v)
{
	vector += v.getVec();
	return *this;
}

vec4 vec4::operator *= (const vec4 & v)
{
	vector *= v.getVec();
	return *this;
}

vec4 vec4::operator /= (const vec4 & v)
{
	vector /= v.getVec();
	return *this;
}

vec4 vec4::operator -= (const vec4 & v)
{
	vector -= v.getVec();
	return *this;
}

vec4 vec4::operator + (const vec4 & v)
{
	return vec4(vector + v.getVec());
}

vec4 vec4::operator - (const vec4 & v)
{
	return vec4(vector - v.getVec());
}

vec4 vec4::operator * (const vec4 & v)
{
	return vec4(vector * v.getVec());
}

vec4 vec4::operator / (const vec4 & v)
{
	return vec4(vector / v.getVec());
}

vec4 vec4::operator += (const float f)
{
	vector += f;
	return *this;
}

vec4 vec4::operator *= (const float f)
{
	vector *= f;
	return *this;
}

vec4 vec4::operator /= (const float f)
{
	vector /= f;
	return *this;
}

vec4 vec4::operator -= (const float f)
{
	vector -= f;
	return *this;
}

vec4 vec4::operator + (const float f)
{
	return vec4(vector + f);
}

vec4 vec4::operator - (const float f)
{
	return vec4(vector - f);
}

vec4 vec4::operator * (const float f)
{
	return vec4(vector * f);
}

vec4 vec4::operator / (const float f)
{
	return vec4(vector / f);
}
	
};

class vec3 {

private:
	glm::vec3 vector; /// GLM type vec3.

public:
	vec3::vec3()
	{

	}


	vec3::vec3(const vec4 & v4)
	{
		vector = v4.getVec();
	}


	vec3::vec3(float x, float y, float z)
	{
		vector[0] = x;
		vector[1] = y;
		vector[2] = z;
	}

	vec3::vec3(const vec3 & v)
	{
		vector = v.getVec();
	}

	vec3::vec3(const glm::vec3 & v)
	{
		vector = v;
	}

	glm::vec3 vec3::getVec() const
	{
		return vector;
	}
	void vec3::setVec(glm::vec3 vec)
	{
		vector = vec;
	}

	float vec3::x() const
	{
		return vector[0];
	}

	float vec3::y() const
	{
		return vector[1];
	}

	float vec3::z() const
	{
		return vector[2];
	}

	float vec3::sx(float nx)
	{
		vector[0] = nx;
		return vector[0];
	}

	float vec3::sy(float ny)
	{
		vector[1] = ny;
		return vector[1];
	}

	float vec3::sz(float nz)
	{
		vector[2] = nz;
		return vector[2];
	}

	void vec3::add(vec3 vec)
	{
		vector[0] = vector[0] + vec.getVec()[0];
		vector[1] = vector[1] + vec.getVec()[1];
		vector[2] = vector[2] + vec.getVec()[2];
	}

	void vec3::subtract(vec3 vec)
	{
		vector[0] = vector[0] - vec.getVec()[0];
		vector[1] = vector[1] - vec.getVec()[1];
		vector[2] = vector[2] - vec.getVec()[2];
	}

	const vec3 & vec3::normailse()
	{
		this->vector = glm::normalize(this->vector);
		return *this;

	}

	float vec3::dot(const vec3 & v) const
	{
		return glm::dot(vector, v.getVec());
	}

	float vec3::angle(const vec3 & v)
	{
		return glm::angle(vector, v.getVec());
	}

	vec3 vec3::cross(const vec3 & v)
	{
		return vec3(glm::cross(vector, v.getVec()));
	}

	bool vec3::almostEqual(const vec3 & v, float threshold)
	{
		return(abs(v.getVec()[0] - vector[0]) < threshold && abs(v.getVec()[1] - vector[1]) < threshold && abs(v.getVec()[2] - vector[2]) < threshold);
	}

	void vec3::operator = (const vec3 & v)
	{
		vector = v.getVec();
	}

	vec3 vec3::operator *= (const vec3 & v)
	{
		vector *= v.getVec();
		return *this;
	}

	vec3 vec3::operator /= (const vec3 & v)
	{
		vector /= v.getVec();
		return *this;
	}

	vec3 vec3::operator -= (const vec3 & v)
	{
		vector -= v.getVec();
		return *this;
	}

	vec3 vec3::operator += (const vec3 & v)
	{
		vector += v.getVec();
		return *this;
	}

	vec3 vec3::operator + (const vec3 & v)
	{
		return vec3(vector + v.getVec());
	}

	vec3 vec3::operator - (const vec3 & v)
	{
		return vec3(vector - v.getVec());
	}

	vec3 vec3::operator * (const vec3 & v)
	{
		return vec3(vector * v.getVec());
	}

	vec3 vec3::operator / (const vec3 & v)
	{
		return vec3(vector / v.getVec());
	}

	vec3 vec3::operator += (const float f)
	{
		vector += f;
		return *this;
	}

	vec3 vec3::operator *= (const float f)
	{
		vector *= f;
		return *this;
	}

	vec3 vec3::operator /= (const float f)
	{
		vector /= f;
		return *this;
	}

	vec3 vec3::operator -= (const float f)
	{
		vector -= f;
		return *this;
	}

	vec3 vec3::operator + (const float f)
	{
		return vec3(vector + f);
	}

	vec3 vec3::operator - (const float f)
	{
		return vec3(vector - f);
	}

	vec3 vec3::operator * (const float f)
	{
		return vec3(vector * f);
	}

	vec3 vec3::operator / (const float f)
	{
		return vec3(vector / f);
	}

	vec3 vec3::operator- ()
	{
		return vec3(-vector);
	}

	float& vec3::operator[] (int x)
	{
		return vector[x];
	}

	float vec3::getLength() {
		return (float)vector.length();
	}

	float vec3::magnitude() const
	{
		return sqrt(vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2]);
	}
};

class mat4 {
private: glm::mat4 matrix;

public:
	mat4::mat4()
	{

	}

	mat4::mat4(float x_0, float y_0, float z_0, float w_0,
		float x_1, float y_1, float z_1, float w_1,
		float x_2, float y_2, float z_2, float w_2,
		float x_3, float y_3, float z_3, float w_3) {

		matrix = glm::mat4(x_0, y_0, z_0, w_0,
			x_1, y_1, z_1, w_1,
			x_2, y_2, z_2, w_2,
			x_3, y_3, z_3, w_3);
	}

	mat4::mat4(const mat4 & m)
	{
		matrix = m.getMat();
	}

	mat4::mat4(const glm::mat4 & m)
	{
		matrix = m;
	}

	glm::mat4 mat4::getMat() const
	{
		return matrix;
	}

	void mat4::setMat(glm::mat4 mat)
	{
		matrix = mat;
	}

	vec4 mat4::operator* (const vec4 & v)
	{
		return vec4(matrix * v.getVec());
	}

	void mat4::operator = (const mat4 & m)
	{
		matrix = m.getMat();
	}

	float & mat4::operator[] (int index)
	{
		int i = 1;

		if (index <= 3)
		{
			i = 1;
		}
		else if (index <= 7)
		{
			i = 2;
		}
		else if (i <= 11)
		{
			i = 3;
		}
		else
		{
			i = 4;
		}

		return matrix[i][index / i];
	}

	float mat4::operator[] (int index) const
	{
		int i = 1;

		if (index <= 3)
		{
			i = 1;
		}
		else if (index <= 7)
		{
			i = 2;
		}
		else if (i <= 11)
		{
			i = 3;
		}
		else
		{
			i = 4;
		}

		return matrix[i][index / i];
	}

	mat4 mat4::operator += (const mat4 & m)
	{
		matrix += m.getMat();
		return *this;
	}

	mat4 mat4::operator *= (const mat4 & m)
	{
		matrix *= m.getMat();
		return *this;
	}

	mat4 mat4::operator /= (const mat4 & m)
	{
		matrix /= m.getMat();
		return *this;
	}

	mat4 mat4::operator -= (const mat4 & m)
	{
		matrix -= m.getMat();
		return *this;
	}

	mat4 mat4::operator + (const mat4 & m)
	{
		return mat4(matrix + m.getMat());
	}

	mat4 mat4::operator - (const mat4 & m)
	{
		return mat4(matrix - m.getMat());
	}

	mat4 mat4::operator * (const mat4 & m)
	{
		return mat4(matrix * m.getMat());
	}

	mat4 mat4::operator / (const mat4 & m)
	{
		return mat4(matrix / m.getMat());
	}

	mat4 mat4::operator += (const float f)
	{
		matrix += f;
		return *this;
	}

	mat4 mat4::operator *= (const float f)
	{
		matrix *= f;
		return *this;
	}

	mat4 mat4::operator /= (const float f)
	{
		matrix /= f;
		return *this;
	}

	mat4 mat4::operator -= (const float f)
	{
		matrix -= f;
		return *this;
	}

	mat4 mat4::operator + (const float f)
	{
		return mat4(matrix + f);
	}

	mat4 mat4::operator - (const float f)
	{
		return mat4(matrix - f);
	}

	mat4 mat4::operator * (const float f)
	{
		return mat4(matrix * f);
	}

	mat4 mat4::operator / (const float f)
	{
		return mat4(matrix / f);
	}

};

/**
* @class Maths
* @brief Overall facade class for GLM maths providing vector and matrix functionality.
*
* @author Matthew MacLennan
* @version 1.3
* @date 10 / 04 / 2018
*/
class Maths
{
public:
	/**
	* @brief Set matrix to its identity.
	*
	* @param mat(mat4) - Matrix being set.
	* @param i(float) - The identity.
	*
	* @return mat4 - Set matrix.
	*/
	static mat4 setmat4(mat4 mat, float i);

	/**
	* @brief Set each individual value in matrix.
	*
	* @param a(float) - A value to be added to matrix.
	* @param b(float) - A value to be added to matrix.
	* @param c(float) - A value to be added to matrix.
	* @param d(float) - A value to be added to matrix.
	* @param e(float) - A value to be added to matrix.
	* @param f(float) - A value to be added to matrix.
	* @param g(float) - A value to be added to matrix.
	* @param h(float) - A value to be added to matrix.
	* @param i(float) - A value to be added to matrix.
	* @param j(float) - A value to be added to matrix.
	* @param k(float) - A value to be added to matrix.
	* @param l(float) - A value to be added to matrix.
	* @param m(float) - A value to be added to matrix.
	* @param n(float) - A value to be added to matrix.
	* @param o(float) - A value to be added to matrix.
	* @param p(float) - A value to be added to matrix.
	*
	* @return mat4 - Set matrix.
	*/
	static mat4 setmat4(mat4 mat, float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p);

	/**
	* @brief Set all values in vec4
	*
	* @param vec(vec4) - The vector being set.
	* @param a(float) - The value being added to the vector.
	* @param b(float) - The value being added to the vector.
	* @param c(float) - The value being added to the vector.
	* @param d(float) - The value being added to the vector.
	*
	* @return vec4 - Set vector.
	*/
	static vec4 setvec4(vec4 vec, float a, float b, float c, float d);

	/**
	* @brief Set all values in vec3
	*
	* @param vec(vec3) - The vector being set.
	* @param a(float) - The value being added to the vector.
	* @param b(float) - The value being added to the vector.
	* @param c(float) - The value being added to the vector.
	*
	* @return vec3 - Set vector.
	*/
	static vec3 setvec3(vec3 vec, float a, float b, float c);

	/**
	* @brief Mulitplying a mat4 and a vec4.
	*
	* @param mat(mat4) - Matrix being multiplied.
	* @param vec(vec3) - Vector being mulitplied.
	*
	* @return vec4 - Outcome vector of calculation.
	*/
	static vec4 mat4Xvec4(mat4 mat, vec4 vec);

	/**
	* @brief Translate a mat4 with a vec3.
	*
	* @param mat(mat4) - Matrix being translated.
	* @param vec(vec3) - Translating vector.
	*
	* @return mat4 - Translated matrix.
	*/
	static mat4 translate(mat4 mat, vec3 vec);

	/**
	* @brief Rotate a mat4 with a vec3.
	*
	* @param mat(mat4) - Matrix being rotated.
	* @param vec(vec3) - Rotating vector.
	*
	* @return mat4 - Rotated matrix.
	*/
	static mat4 rotate(mat4 mat, float angle, vec3 rotv);

	/**
	* @brief Scale a mat4 with a vec3.
	*
	* @param mat(mat4) - Matrix being scaled.
	* @param scalev(vec3) - scaling vector.
	*
	* @return mat4 - Scaled matrix.
	*/
	static mat4 scale(mat4 mat, vec3 scalev);

	/**
	* @brief Take inputs of fovy, width, height, near and far and return a perspective mat4.
	*
	* @param fovy(float)
	* @param width(float)
	* @param height(float)
	* @param near(float)
	* @param far(float)
	*
	* @return mat4.
	*/
	static mat4 perspective(float fovy, float width, float height, float near, float far);

	/**
	* @brief Nomalize a vec4.
	*
	* @param vec(vec4) - Vector being normalized.
	*
	* @return vec4 - Normalized vector.
	*/
	static vec4 normalizev4(vec4 vec);

	/**
	* @brief Nomalize a vec3.
	*
	* @param vec(vec3) - Vector being normalized.
	*
	* @return vec3 - Normalized vector.
	*/
	static vec3 normalize(vec3 vec);

	/**
	* @brief Turn degrees into radians.
	*
	* @param a(float) - Angle being converted.
	*
	* @return float - Radians.
	*/
	static float radians(float a);

	/**
	* @brief Return inverse matrix of input.
	*
	* @param m(mat4) - Matrix being inversed.
	*
	* @return mat4 - Inversed matrix.
	*/
	static mat4 inverse(mat4 m);

	/**
	* @brief Returns perspective matrix from 4 inputs.
	*
	* @param a(float).
	* @param b(float).
	* @param c(float).
	* @param d(float).
	*
	* @return mat4 - Perspective matrix.
	*/
	static mat4 perspective(float a, float b, float c, float d);

	/**
	* @brief Transform(multiply) 2 matricies.
	*
	* @param mat1(mat4) - First matrix.
	* @param mat2(mat4) - Second matrix.
	*
	* @return mat4 - Outcome.
	*/
	static mat4 transform(mat4 mat1, mat4 mat2);

	/**
	* @brief Transform(multiply) 3 matricies.
	*
	* @param projectionm(mat4) - First matrix.
	* @param translatem(mat4) - Second matrix.
	* @param rotm(mat4) - Third matrix.
	*
	* @return mat4 - Outcome.
	*/
	static mat4 transform(mat4 projectionm, mat4 translatem, mat4 rotm);

	/**
	* @brief Transform(multiply) 4 matricies.
	*
	* @param projectionm(mat4) - First matrix.
	* @param rotm(mat4) - Second matrix.
	* @param scalem(mat4) - Third matrix.
	* @param mat(mat4) - Fourth matrix.
	*
	* @return mat4 - Outcome.
	*/
	static mat4 transform(mat4 translatem, mat4 rotm, mat4 scalem, mat4 mat);
};