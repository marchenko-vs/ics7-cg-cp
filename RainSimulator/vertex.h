#ifndef VERTEX_H
#define VERTEX_H

class Vertex
{
public:
    double dx, dy, dz; // перенос
    double kx, ky, kz; // масштабирование
    double phi_x, phi_y, phi_z; // поворот
public:
    double x;
    double y;
    double z;

    Vertex();
    Vertex(double x, double y, double z);

    void normalize(void);

    Vertex operator + (const Vertex &vertex);
    Vertex operator - (const Vertex &vertex);
    Vertex operator * (const double multiplier);
    Vertex operator ^ (const Vertex &vertex);
    double operator * (const Vertex &vertex);

    ~Vertex();
};

#endif // VERTEX_H
