#include "./Vertex.h"
#include "./Sphere.h"
#include <stdio.h>
#include <sys/time.h>

using namespace pano;

long currentTime() {
  struct timeval tv;
  gettimeofday(&tv,NULL);
  return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

int main() {
  long t = currentTime();
  printf("==== BEGIN\n");

  Vertex vt = createVertex(0, 0, 0);
  Sphere* sp = new Sphere(100, vt);
  sp->mesh();

  printf("==== END, SPEND: %ld ms\n", currentTime() - t);

  return 0;
}