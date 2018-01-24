#ifndef POLYGON_H
#define POLYGON_H

#include "./Geometry.h"

NAMESPACE_BEGIN(pano)

class Polygon : public Geometry {
public:
  explicit Polygon(vector<Vertex>& vertexes);
  explicit Polygon(vector<Vertex>&& vertexes);
  vector<double> mesh();
};

NAMESPACE_END

#endif