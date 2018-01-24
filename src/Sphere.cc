#include "./Sphere.h"
#include <math.h>

#define MESH_COUNT 200
#define PI 3.1415926535897932384626433832795
#define TWO_PI 6.283185307179586476925286766559
#define HALF_PI 1.5707963267948966192313216916398

NAMESPACE_BEGIN(pano)

namespace {
  vector<Vertex> genVerexes (double radius, const Vertex& center) {
    int thetaCount = MESH_COUNT; // 水平分割数
    int phiCount = MESH_COUNT; // 垂直分割数，包含上下两顶点

    double thetaStep = TWO_PI / thetaCount;
    double phiStep = PI / (phiCount - 1);
    vector<Vertex> vertexes;

    for (int i = 0; i < phiCount; ++i) {
      double phi = phiStep * i - HALF_PI;

      if (i == 0) {
        vertexes.push_back({center.components.x, -radius + center.components.y, center.components.z});
        continue;
      }

      if (i == phiCount - 1) {
        vertexes.push_back({center.components.x, radius + center.components.y, center.components.z});
        continue;
      }

      double layerRadius = radius * cos(phi);
      double layerY = radius * sin(phi);

      for (int j = 0; j < thetaCount; ++j) {
        double theta = thetaStep * j;
        vertexes.push_back({
          layerRadius * cos(theta) + center.components.x,
          layerY + center.components.y,
          layerRadius * sin(theta) + center.components.z
        });
      }
    }

    return vertexes;
  }



  vector<Polygon*> genPlanes (const vector<Vertex>& vts) {
    int thetaCount = MESH_COUNT; // 水平分割数
    int phiCount = MESH_COUNT;  // 垂直分割数，包含上下两顶点
    vector<Polygon*> planes;

    auto computeLayerOffset = [thetaCount] (int layer) {
      if (layer == 0) return 0;
      return (layer - 1) * thetaCount + 1;
    };

    for (int i = 0; i < phiCount - 1; ++i) {
      int layer = i;
      int layerOffset = computeLayerOffset(i);
      int nextLayerOffset = computeLayerOffset(i + 1);

      if (layer == 0) {
        auto vtx0 = vts.at(0);

        for (int j = 0; j < thetaCount - 1; ++j) {
          planes.push_back(new Polygon({vtx0, vts[nextLayerOffset + j], vts[nextLayerOffset + j + 1]}));
        }

        planes.push_back(new Polygon({vtx0, vts[nextLayerOffset + thetaCount - 1], vts[nextLayerOffset]}));

        continue;
      }

      if (layer == phiCount - 2) {
        auto vtxLast = vts[nextLayerOffset + 0];

        for (int j = 0; j < thetaCount - 1; ++j) {
          planes.push_back(new Polygon({vtxLast, vts[layerOffset + j], vts[layerOffset + j + 1]}));
        }

        planes.push_back(new Polygon({vtxLast, vts[layerOffset + thetaCount - 1], vts[layerOffset]}));

        continue;
      }

      for (int j = 0; j < thetaCount; ++j) {
        planes.push_back(new Polygon({vts[layerOffset + j], vts[layerOffset + j + 1],
          vts[nextLayerOffset + j + 1], vts[nextLayerOffset + j]
        }));
      }

      planes.push_back(new Polygon({vts[layerOffset + thetaCount - 1], vts[layerOffset],
        vts[nextLayerOffset], vts[nextLayerOffset + +thetaCount - 1]
      }));
    }

    return planes;
  }
}

Sphere::Sphere(double radius, const Vertex& center) {
  this->initGeometry(genVerexes(radius, center));
}

vector<double> Sphere::mesh() {
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