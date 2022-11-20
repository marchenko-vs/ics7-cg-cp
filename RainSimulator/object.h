#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <cstdlib>

#include <QGraphicsScene>
#include <QImage>

#include "vertex.h"
#include "face.h"

class Object
{
public:
    Object();
    Object(const char *const filename);

    void triangle(Vertex t0, Vertex t1, Vertex t2, const int width, int *z_buffer,
                  QImage *scene, QColor color);

    void draw(const std::size_t width, const std::size_t height,
              uint8_t red, uint8_t green, uint8_t blue, QImage *scene);

    void translate(double dx, double dy, double dz);
    void scale(double kx, double ky, double kz);
    void rotate(double phi_x, double phi_y, double phi_z);

    std::size_t getVerticesNumber() const;
    std::size_t getFacesNumber() const;

    Vertex getVertex(std::size_t number) const;
    face_t getFace(std::size_t number) const;

    ~Object();

public:
    std::vector<Vertex> vertices;
    std::vector<face_t> faces;
};

class Ground : public Object
{
public:
    Ground();
    Ground(const char *const filename);
};

class RainDroplet : public Object
{
public:
    RainDroplet();
    RainDroplet(const RainDroplet &object);
    RainDroplet(const char *const filename);
};

#endif // OBJECT_H
