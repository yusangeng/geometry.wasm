#include "./Sphere.h"
#include "./Vertex.h"
#include <stdio.h>
#include <sys/time.h>
#include <emscripten/emscripten.h>

using namespace pano;

long currentTime() {
  struct timeval tv;
  gettimeofday(&tv,NULL);
  return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

#ifdef __cplusplus
extern "C" {
#endif

int EMSCRIPTEN_KEEPALIVE sphereMesh() {
  long t = currentTime();
  printf("==== BEGIN\n");

  Vertex vt = createVertex(0, 0, 0);
  Sphere* sp = new Sphere(1, vt);
  
  std::vector<double> vec = sp->mesh();
  delete sp;

  printf("==== END, SPEND: %ld ms\n", currentTime() - t);

  return 0;
}

#ifdef __cplusplus
}
#endif

