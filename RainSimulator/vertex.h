#ifndef VERTEX_H
#define VERTEX_H

class Vertex
{
public:
    Vertex();
    Vertex(double x, double y, double z);
    double get_x() const;
    double get_y() const;
    double get_z() const;
    void set_x(double x);
    void set_y(double y);
    void set_z(double z);
    void change_x(double x);
    void change_y(double y);
    void change_z(double z);
    void normalize(void);
    Vertex operator + (const Vertex &vertex);
    Vertex operator - (const Vertex &vertex);
    Vertex operator * (const double multiplier);
    Vertex operator ^ (const Vertex &vertex);
    double operator * (const Vertex &vertex);
    ~Vertex();

private:
    double x, y, z;
};

#endif // VERTEX_H
