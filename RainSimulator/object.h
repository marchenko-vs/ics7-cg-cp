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

    void draw(const std::size_t width, const std::size_t height,
              QGraphicsScene *scene, QColor color);

    void transfer(double dx, double dy, double dz);

    void rotate_x(double degrees);
    void rotate_y(double degrees);
    void rotate_z(double degrees);

    std::size_t getVerticesNumber() const;
    std::size_t getFacesNumber() const;

    Vertex getVertex(std::size_t number) const;
    face_t getFace(std::size_t number) const;

    ~Object();

public:
    std::vector<Vertex> vertices;
    std::vector<face_t> faces;
};

#endif // OBJECT_H
