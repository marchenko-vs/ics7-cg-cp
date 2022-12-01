#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <cstdlib>

#include <QGraphicsScene>
#include <QImage>

#include "vertex.h"
#include "face.h"

extern int *z_buffer;
extern Vertex from;
extern Vertex light_dir;

class Object
{
public:
    Object();
    Object(const Object&) = default;
    Object(const char *const filename);

    void draw_polygon(Vertex t0, Vertex t1, Vertex t2, const int width,
                  int *z_buffer,
                  QImage *scene, QColor color);

    void draw(const std::size_t width, const std::size_t height,
              uint8_t red, uint8_t green, uint8_t blue, QImage *scene);

    std::size_t getVerticesNumber();
    std::size_t getFacesNumber();

    void addVertex(Vertex vertex);
    void addFace(const Face face);

    Vertex getVertex(std::size_t number);
    Face getFace(std::size_t number);

    double get_dx() const;
    double get_dy() const;
    double get_dz() const;
    double get_kx() const;
    double get_ky() const;
    double get_kz() const;
    double get_phi_x() const;
    double get_phi_y() const;
    double get_phi_z() const;

    void set_dx(double dx);
    void set_dy(double dy);
    void set_dz(double dz);
    void set_kx(double kx);
    void set_ky(double ky);
    void set_kz(double kz);
    void set_phi_x(double phi_x);
    void set_phi_y(double phi_y);
    void set_phi_z(double phi_z);

    void translate(double dx, double dy, double dz);
    void rotate(double phi_x, double phi_y, double phi_z);
    void scale(double kx, double ky, double kz);

    ~Object(); 

private:
    std::vector<Vertex> vertices;
    std::vector<Face> faces;

    double dx, dy, dz;
    double kx, ky, kz;
    double phi_x, phi_y, phi_z;
};

class Ground : public Object
{
public:
    Ground();
    Ground(const char *const filename);
};

class OriginalRainDroplet : public Object
{
public:
    OriginalRainDroplet();
    OriginalRainDroplet(const char *const filename);
};

class RainDroplet : public Object
{
public:
    RainDroplet();
    RainDroplet(OriginalRainDroplet *object);

    void draw(const std::size_t width, const std::size_t height,
              uint8_t red, uint8_t green, uint8_t blue, QImage *scene);

private:
    OriginalRainDroplet *ptr;
};

#endif // OBJECT_H
