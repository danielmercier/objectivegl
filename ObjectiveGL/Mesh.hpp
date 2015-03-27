#pragma once

#include <vector>
#include <GL\glew.h>
#include <glm.hpp>
#include <gtc\type_ptr.hpp>

#include "VertexArray.h"

class Mesh
{
public:
	/*Constructor*/
	Mesh();

	/*use to add another data to mesh*/
	/*Like normals, or tangent and bitangent or what u want*/
	/*This data will appear in the same order location as u add them for shaders purpose*/
	/*size define if data as to be read 1 value per 1, 2 value per 2 ...*/
	template<typename T>
	void addData(std::vector<T> data, int dimension, bool normalized = false){
		VertexBuffer vbo(GL_ARRAY_BUFFER, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);
		_vao.attribBuffer(vbo, dimension, normalized);
	}

	void addDynamicalData(std::vector<float> *data, int dimension, bool normalized = false){
		VertexBuffer *vbo = new VertexBuffer(GL_ARRAY_BUFFER, data->size() * sizeof(float), data->data(), GL_STATIC_DRAW);
		_vao.attribBuffer(*vbo, dimension, normalized);
		_dynamicalData.push_back(Couple(vbo, data));
	}

	void updateDynamicalData();
	
	/*Setters*/
	void setVertices(std::vector<float> vertices);
	void setDynamicalVertices(std::vector<float> *vertices);
	void setTexCoords(std::vector<float> texCoords);
	void setIndices(std::vector<unsigned int> indices);

	/*Getters*/
	bool useIndices();
	VertexArray getVertexArray(){ return _vao; }
	VertexBuffer getIndices(){ return *_ibo; }
	int getSize(){ return _size; }

private:
	class Couple{
	public:
		Couple(VertexBuffer *vbo, std::vector<float> *data){
			_vbo = vbo;
			_data = data;
		}
		VertexBuffer *_vbo;
		std::vector<float> *_data;
	};
	
	/*Store all the vertices of a mesh*/
	VertexArray _vao;
	VertexBuffer *_ibo;

	std::vector<Couple> _dynamicalData;

	int _size;
};