#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <cstdlib>

#include <QGraphicsScene>

#include "vertex.h"
#include "face.h"

class Object
{
public:
    Object();

    void triangle(vertex_t t0, vertex_t t1, vertex_t t2,
                  QGraphicsScene *scene, QColor color);

    void draw(const int width, const int height,
              QGraphicsScene *scene, QColor color);

    void GetObject(const char *const filename);

    std::size_t getVerticesNumber() const;
    std::size_t getFacesNumber() const;

    vertex_t getVertex(std::size_t number) const;
    face_t getFace(std::size_t number) const;

    ~Object();

private:
    std::vector<vertex_t> vertices;
    std::vector<face_t> faces;
};

#endif // OBJECT_H
