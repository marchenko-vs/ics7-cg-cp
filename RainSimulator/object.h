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
    Object(const char *const filename);

    void triangle(Vertex t0, Vertex t1, Vertex t2, const int width, int *z_buffer,
                  QGraphicsScene *scene, QColor color);

    void draw(const int width, const int height,
              QGraphicsScene *scene, QColor color);

    std::size_t getVerticesNumber() const;
    std::size_t getFacesNumber() const;

    Vertex getVertex(std::size_t number) const;
    face_t getFace(std::size_t number) const;

    ~Object();

private:
    std::vector<Vertex> vertices;
    std::vector<face_t> faces;
};

#endif // OBJECT_H
