#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "./def.h"
#include "./Vertex.h"
#include <vector>
#include <assert.h>

NAMESPACE_BEGIN(pano)

using std::vector;
using std::move;

class Geometry {
private:
  vector<Vertex> vertexes;

protected:
  void initGeometry(const vector<Vertex>& vertexes) {
    assert(vertexes.size() >= 3);
    this->vertexes = vertexes;
  }

  void initGeometry(vector<Vertex>&& vertexes) {
    assert(vertexes.size() >= 3);
    this->vertexes = move(vertexes);
  }

public:
  Geometry() {}

  Geometry(const Geometry& other) {
    this->vertexes = other.vertexes;
  }

  Geometry(Geometry&& other) {
    this->vertexes = move(other.vertexes);
  }

  const vector<Vertex>& getVertexes() {
    return this->vertexes;
  }

  vector<double> flatten() {
    vector<double> ret;
    const vector<Vertex>& vts = this->vertexes;

    for (auto it = vts.begin(); it != vts.end(); ++it) {
      ret.insert(ret.end(), it->xyz, it->xyz + 3);
    }

    return ret;
  }

  Geometry& operator =(const Geometry& other) {
    if (&other == this) return *this;

    this->vertexes = other.vertexes;
    return *this;
  }

  Geometry& operator =(Geometry&& other) {
    if (&other == this) return *this;

    this->vertexes = move(other.vertexes);
    return *this;
  }
};

NAMESPACE_END

#endif