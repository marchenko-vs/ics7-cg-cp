#include "object.h"
#include "vertex.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>

#include <QDebug>

Object::Object()
{

}

static void addPoint(int x, int y, QGraphicsScene *scene, QColor color)
{
    scene->addLine(x, -y, x + 1, -y + 1, color);
}

void Object::triangle(vertex_t t0, vertex_t t1, vertex_t t2,
              QGraphicsScene *scene, QColor color)
{
    if (t0.y == t1.y && t0.y == t2.y)
    {
        return;
    }

    if (t0.y > t1.y)
        std::swap(t0, t1);

    if (t0.y > t2.y)
        std::swap(t0, t2);

    if (t1.y > t2.y)
        std::swap(t1, t2);

    int total_height = t2.y - t0.y;

    for (int i = 0; i < total_height; i++)
    {
        bool second_half = i>t1.y-t0.y || t1.y==t0.y;
        int segment_height = second_half ? t2.y-t1.y : t1.y-t0.y;
        double alpha = (double)i/total_height;
        double beta  = (double)(i-(second_half ? t1.y-t0.y : 0))/segment_height; // be careful: with above conditions no division by zero here

        vertex_t A, B;

        A.x = t0.x + (t2.x - t0.x) * alpha;
        A.y = t0.y + (t2.y - t0.y) * alpha;

        B.x = second_half ? t1.x + (t2.x - t1.x) * beta : t0.x + (t1.x - t0.x) * beta;
        B.y = second_half ? t1.y + (t2.y - t1.y) * beta : t0.y + (t1.y - t0.y) * beta;

        if (A.x > B.x)
            std::swap(A, B);

        for (int j = A.x; j <= B.x; j++)
        {
            addPoint(j, t0.y + i, scene, color); // attention, due to int casts t0.y+i != A.y
        }
    }
}

void Object::draw(const int width, const int height,
                  QGraphicsScene *scene, QColor color)
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

        int x_2 = (v_2.x + 1.0) * width / 2.0;
        int y_2 = (v_2.y + 1.0) * height / 2.0;

        vertex_t t_0 = { x_0, y_0, 0};
        vertex_t t_1 = { x_1, y_1, 0};
        vertex_t t_2 = { x_2, y_2, 0};

        qDebug() << 1 << '\n';

        triangle(t_0, t_1, t_2, scene, QColor(rand() % 255, rand() % 255, rand() % 255));
    }
}

//void Object::draw(const int width, const int height,
//                  QGraphicsScene *scene, QColor color) const
//{
//    for (std::size_t i = 0; i < this->getFacesNumber(); i++)
//    {
//        face_t current_face = this->getFace(i);

//        vertex_t v_0 = this->getVertex(current_face.vertices[0]);
//        vertex_t v_1 = this->getVertex(current_face.vertices[1]);
//        vertex_t v_2 = this->getVertex(current_face.vertices[2]);

//        int x_0 = (v_0.x + 1.0) * width / 2.0;
//        int y_0 = (v_0.y + 1.0) * height / 2.0;

//        int x_1 = (v_1.x + 1.0) * width / 2.0;
//        int y_1 = (v_1.y + 1.0) * height / 2.0;

//        /* we need to reverse only y-axis */
//        scene->addLine(x_0, -y_0, x_1, -y_1, color);

//        x_0 = (v_0.x + 1.0) * width / 2.0;
//        y_0 = (v_0.y + 1.0) * height / 2.0;

//        x_1 = (v_2.x + 1.0) * width / 2.0;
//        y_1 = (v_2.y + 1.0) * height / 2.0;

//        scene->addLine(x_0, -y_0, x_1, -y_1, color);

//        x_0 = (v_1.x + 1.0) * width / 2.0;
//        y_0 = (v_1.y + 1.0) * height / 2.0;

//        x_1 = (v_2.x + 1.0) * width / 2.0;
//        y_1 = (v_2.y + 1.0) * height / 2.0;

//        scene->addLine(x_0, -y_0, x_1, -y_1, color);
//    }
//}

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
