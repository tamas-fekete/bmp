#pragma pack(1)

typedef struct{unsigned  char red;
unsigned  char green;
unsigned  char blue;
}color_t;

typedef struct{
  float x;
  float y;
  float z;
}point_t;

typedef struct{
 point_t center;
 float r;
 color_t color;
}sphere_t;

typedef struct{
  float x;
  float y;
  float z;
}vector_t;

typedef struct{
  point_t p1;
  point_t p2;
}line_t; // equation of a line r = r1 + t(r2 - r1)
         // r1 = < x1, y1, z1 > ; r2 = < x2, y2, z2 > ; r = < x, y, z >

vector_t createunitvector(vector_t *v);
vector_t pointstovector(point_t *start, point_t *end);
vector_t scalartimesvector(float scalar, vector_t v);
vector_t vectorminusvector(vector_t v1, vector_t v2);