#pragma once
#include "GLRenderer.h"
#include "Mesh.hpp"
#include "MeshDrawer.h"
#include "Program.h"
#include "MouseHandler.h"
#include <cmath>
#include <list>

class Bezier{
private:
	class Pos{
	public:
		double x;
		double y;
		Pos(double xarg, double yarg) : x(xarg), y(yarg)
		{}
	};
	std::list<Pos> points;

public:
	void addPoint(double x, double y){
		points.push_back(Pos(x, y));
	}

	void print(){
		for each (Pos p in points)
		{
			printf("%lf, %lf\n", p.x, p.y);
		}
	}

	float* calculate(float t){

		float *res = new float[2];
		res[0] = 0;
		res[1] = 0;

		if (points.size() < 2){
			return res;
		}

		if (t == 0){
			res[0] = points.front().x;
			res[1] = points.front().y;
			return res;
		}
		else if (t == 1){
			res[0] = points.back().x;
			res[1] = points.back().y;
			return res;
		}

		float coef = 1;
		float tval = 1;
		float tmval = pow(1 - t, points.size() - 1);
		int i = 0;

		for each (Pos p in points)
		{
			res[0] += coef * tval * tmval * p.x;
			res[1] += coef * tval * tmval * p.y;

			tval *= t;
			tmval /= (1 - t);
			i++;
			coef *= (float)(points.size() - i) / (float)i;	   
		}

		return res;
	}
};

class BezierRenderer :
	public GLRenderer,
	public MouseHandler
{
public:
	BezierRenderer(int precision = 20);
	~BezierRenderer();
	void render();
	void mouseButtonPressed(Window *w, int button, int mods);

private:
	std::vector<float> _line;
	Mesh _mesh;
	MeshDrawer *_md;
	Program *_p;
	Bezier b;
};

