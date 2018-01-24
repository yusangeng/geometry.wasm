#ifndef CUBE_H
#define CUBE_H

#include "./Geometry.h"

NAMESPACE_BEGIN(pano)

class Cube : public Geometry {
public:
  Cube(double sideLen, const Vertex& center);
  vector<double> mesh();
};

NAMESPACE_END

#endif