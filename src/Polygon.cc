#include "./Polygon.h"

NAMESPACE_BEGIN(pano)

Polygon::Polygon(vector<Vertex>& vertexes) {
  this->initGeometry(vertexes);
}

Polygon::Polygon(vector<Vertex>&& vertexes)  {
  this->initGeometry(move(vertexes));
}

vector<double> Polygon::mesh() {
  const vector<Vertex>& vts = this->getVertexes();
  size_t len = vts.size();
  size_t end = len - 1;

  if (len == 3) {
    return this->flatten();
  }

  vector<double> ret;

  for (size_t i = 1; i < end; ++i) {
    const double* xyz =  vts.at(0).xyz;
    ret.insert(ret.end(), xyz, xyz + 3);

    xyz = vts.at(i).xyz;
    ret.insert(ret.end(), xyz, xyz + 3);

    xyz = vts.at(i + 1).xyz;
    ret.insert(ret.end(), xyz, xyz + 3);
  }

  return ret;
}

NAMESPACE_END