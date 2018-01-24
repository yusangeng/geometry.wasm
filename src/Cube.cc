#include "./Cube.h"
#include "./Polygon.h"

NAMESPACE_BEGIN(pano)

namespace {
  vector<Vertex> genVerexes (double sideLen, const Vertex& center) {
    double len = sideLen / 2;

    double arrVts[8][3] = {
      {-len, -len, len}, {len, -len, len},
      {len, len, len}, {-len, len, len},
      {-len, -len, -len}, {len, -len, -len},
      {len, len, -len}, {-len, len, -len}
    };

    const Vertex* pVts = reinterpret_cast<const Vertex*>(arrVts);
    
    vector<Vertex> ret;
    ret.assign(pVts, pVts + 8);
    
    for (auto it = ret.begin(); it != ret.end(); ++it) {
      it->components.x += center.components.x;
      it->components.y += center.components.y;
      it->components.z += center.components.z;
    }

    return ret;
  }



  vector<Polygon*> genPlanes (const vector<Vertex>& vts) {
    auto makePolygon = [vts] (int index1, int index2, int index3, int index4) {
      return new Polygon({vts[index1], vts[index2], vts[index3], vts[index4]});
    };

    vector<Polygon*> ret;

    ret.push_back(makePolygon(0, 1, 2, 3));
    ret.push_back(makePolygon(1, 5, 6, 2));
    ret.push_back(makePolygon(2, 6, 7, 3));
    ret.push_back(makePolygon(3, 7, 4, 0));
    ret.push_back(makePolygon(0, 4, 5, 1));
    ret.push_back(makePolygon(4, 5, 6, 7));

    return ret;
  }
}

Cube::Cube(double sideLen, const Vertex& center) {
  this->initGeometry(genVerexes(sideLen, center));
}

vector<double> Cube::mesh() {
  vector<Polygon*> planes = genPlanes(this->getVertexes());
  vector<double> ret;  

  for (auto it = planes.begin(); it != planes.end(); ++it) {
    Polygon* plane = *it;
    vector<double> arr = plane->mesh();
    ret.insert(ret.end(), arr.begin(), arr.end());
    delete plane; // 清理资源
  }

  return ret;
}

NAMESPACE_END