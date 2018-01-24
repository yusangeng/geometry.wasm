#ifndef VERTEX_H
#define VERTEX_H

#include "./def.h"

NAMESPACE_BEGIN(pano)

union Vertex {
  struct {
    double x;
    double y;
    double z;
  } components;

  double xyz[3];

  Vertex& operator =(const double* arr) {
    this->components.x = arr[0];
    this->components.y = arr[1];
    this->components.z = arr[2];

    return *this;
  }
};

Vertex createVertex(double x, double y, double z);

NAMESPACE_END

#endif
