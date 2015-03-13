#include <vector>
#include <GL\glew.h>
#include <glm.hpp>
#include <gtc\type_ptr.hpp>

#pragma once
class Mesh
{
public:
	/*struct composed by vertex coordinate and his corresponding tex coords*/
	struct vertex
	{
		float pos[3];
		float uv[2];
	};

	/*Constructor*/
	Mesh(bool useIndices = false);

	/*use to add another data to mesh*/
	/*Like normals, or tangent and bitangent or what u want*/
	/*This data will appear in the same order location as u add them for shaders purpose*/
	/*size define if data as to be read 1 value per 1, 2 value per 2 ...*/
	void addData(float *data, int size, int nb, bool normalized = false);

	/*Setters*/
	void setDrawMod(int drawMod);
	void setVertices(std::vector<vertex> vertices);
	void setIndices(std::vector<unsigned int> indices);

	/*Getters*/
	int getDrawMod();
	std::vector<vertex> getVertices();
	bool useIndices();
	std::vector<unsigned int> getIndices();

	
private:
	friend class MeshDrawer;
	/*Struct to store data*/
	struct dataFVAO{
		float *data;
		bool normalized;
		int nb;
		int size;
	};

	/*One of GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_LINES, GL_LINE_STRIP, GL_POINTS...*/
	int _drawMod;

	/*Store all the vertices of a mesh*/
	std::vector<vertex> _vertices;

	/*Indices used?*/
	bool _useIndices;
	/*Stored indices*/
	std::vector<unsigned int> _indices;

	/*Other value stored*/
	std::vector<dataFVAO> _data;
};