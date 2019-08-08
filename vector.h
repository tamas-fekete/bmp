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
typedef point_t vector_t;
typedef struct{
 point_t center;
 float r;
 color_t color;
 point_t intersection;
}sphere_t;

typedef struct{
  point_t p1;
  point_t p2;
}line_t; // equation of a line r = r1 + t(r2 - r1)
         // r1 = < x1, y1, z1 > ; r2 = < x2, y2, z2 > ; r = < x, y, z >
sphere_t* Intersection(line_t *line);
vector_t createunitvector(vector_t *v);
vector_t pointstovector(point_t *start, point_t *end);
line_t* pointstoline(point_t *start, point_t *end);
vector_t scalartimesvector(float scalar, vector_t v);
vector_t vectorminusvector(vector_t v1, vector_t v2);
vector_t vectorplusvector(vector_t v1, vector_t v2);
color_t AddColors(color_t c1, color_t c2);
float cosalpha(vector_t p1, vector_t p2);
float dotproduct(vector_t v1, vector_t v2);
float PointToPointDistance(point_t p1, point_t p2);
char LineIntersectsSphere(line_t *line, sphere_t *sphere, point_t* point);
