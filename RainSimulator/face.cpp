#include "face.h"

Face::Face(const Face &face)
{
    this->vertices[0] = face.getVertex(0);
    this->vertices[1] = face.getVertex(1);
    this->vertices[2] = face.getVertex(2);
}

Face::Face(int a, int b, int c)
{
    this->vertices[0] = a;
    this->vertices[1] = b;
    this->vertices[2] = c;
}

int Face::getVertex(int index) const
{
    return this->vertices[index];
}
