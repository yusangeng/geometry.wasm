#include "./Vertex.h"

NAMESPACE_BEGIN(pano)

Vertex createVertex(double x, double y, double z) {
  Vertex vt;

  vt.components.x = 0;
  vt.components.y = 0;
  vt.components.z = 0;

  return vt;
}

NAMESPACE_END