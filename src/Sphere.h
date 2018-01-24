#ifndef SPHERE_H
#define SPHERE_H

#include "./Geometry.h"
#include "./Polygon.h"
#include "./Vertex.h"

NAMESPACE_BEGIN(pano)

class Sphere : public Geometry {
public:
  Sphere(double radius, const Vertex& center);
  vector<double> mesh();
};

NAMESPACE_END

#endif