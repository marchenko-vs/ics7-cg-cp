#include "object.h"
#include "vertex.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>

Object::Object()
{

}

void Object::draw(const int width, const int height,
                  QGraphicsScene *scene, QColor color) const
{
    for (std::size_t i = 0; i < this->getFacesNumber(); i++)
    {
        face_t current_face = this->getFace(i);

        vertex_t v_0 = this->getVertex(current_face.vertices[0]);
        vertex_t v_1 = this->getVertex(current_face.vertices[1]);
        vertex_t v_2 = this->getVertex(current_face.vertices[2]);

        int x_0 = (v_0.x + 1.0) * width / 2.0;
        int y_0 = (v_0.y + 1.0) * height / 2.0;

        int x_1 = (v_1.x + 1.0) * width / 2.0;
        int y_1 = (v_1.y + 1.0) * height / 2.0;

        /* we need to reverse only y-axis */
        scene->addLine(x_0, -y_0, x_1, -y_1, color);

        x_0 = (v_0.x + 1.0) * width / 2.0;
        y_0 = (v_0.y + 1.0) * height / 2.0;

        x_1 = (v_2.x + 1.0) * width / 2.0;
        y_1 = (v_2.y + 1.0) * height / 2.0;

        scene->addLine(x_0, -y_0, x_1, -y_1, color);

        x_0 = (v_1.x + 1.0) * width / 2.0;
        y_0 = (v_1.y + 1.0) * height / 2.0;

        x_1 = (v_2.x + 1.0) * width / 2.0;
        y_1 = (v_2.y + 1.0) * height / 2.0;

        scene->addLine(x_0, -y_0, x_1, -y_1, color);
    }
}

vertex_t Object::getVertex(std::size_t number) const
{
    return this->vertices[number];
}

face_t Object::getFace(std::size_t number) const
{
    return this->faces[number];
}

std::size_t Object::getVerticesNumber() const
{
    return this->vertices.size();
}

std::size_t Object::getFacesNumber() const
{
    return this->faces.size();
}

void Object::GetObject(const char *const filename)
{
    std::ifstream input_file;

    input_file.open(filename, std::ifstream::in);

    if (input_file.fail())
    {
        return;
    }

    std::string line;

    while (!input_file.eof())
    {
        std::getline(input_file, line);
        std::istringstream iss(line.c_str());

        char trash;

        if (!line.compare(0, 2, "v "))
        {
            iss >> trash;
            vertex_t v;

            iss >> v.x;
            iss >> v.y;
            iss >> v.z;

            this->vertices.push_back(v);
        }
        else if (!line.compare(0, 2, "f "))
        {
            std::vector<int> f;
            int itrash, idx;

            iss >> trash;

            while (iss >> idx >> trash >> itrash >> trash >> itrash)
            {
                idx--;
                f.push_back(idx);
            }

            face_t face;

            face.vertices[0] = f[0];
            face.vertices[1] = f[1];
            face.vertices[2] = f[2];

            this->faces.push_back(face);
        }
    }

    input_file.close();
}
