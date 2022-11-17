#include "object.h"
#include "vertex.h"
#include "matrix.h"
#include "mainwindow.h"

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

Object::~Object()
{

}

static void drawLine(int x, int y, QGraphicsScene *scene, QColor color)
{
    scene->addLine(x, -y, x + 1, -y + 1, color);
}

void Object::triangle(Vertex t0, Vertex t1, Vertex t2, const int width,
                      int *z_buffer, QGraphicsScene *scene, QColor color)
{
    if (t0.y == t1.y && t0.y == t2.y) // вырожденный полигон
        return;

    if (t0.y > t1.y)
        std::swap(t0, t1);

    if (t0.y > t2.y)
        std::swap(t0, t2);

    if (t1.y > t2.y)
        std::swap(t1, t2);

    int total_height = t2.y - t0.y;

    for (int i = 0; i < total_height; i++)
    {
        bool second_half = i > t1.y - t0.y || t1.y == t0.y;
        int segment_height = second_half ? t2.y - t1.y : t1.y - t0.y;

        double alpha = (double)i / total_height;
        double beta  = (double)(i - (second_half ? t1.y - t0.y : 0)) / segment_height; // be careful: with above conditions no division by zero here

        Vertex A = t0 + (t2 - t0) * alpha;
        Vertex B = second_half ? t1 + (t2 - t1) * beta : t0 + (t1 - t0) * beta;

        if (A.x > B.x)
            std::swap(A, B);

        for (int j = A.x; j <= B.x; j++)
        {
            double phi = B.x == A.x ? 1. : (double)(j - A.x) / (double)(B.x - A.x);
            Vertex P = A + (B - A) * phi;
            int k = P.x + P.y * width;

            if (z_buffer[k] < P.z)
            {
                z_buffer[k] = P.z;
                drawLine(P.x, P.y, scene, color);
            }
        }
    }
}

void Object::draw(const std::size_t width, const std::size_t height,
                  QGraphicsScene *scene, QColor color)
{
    int *z_buffer = new int[width * height];

    for (int i = 0; i < width * height; i++)
        z_buffer[i] = 0;

    for (std::size_t i = 0; i < this->getFacesNumber(); i++)
    {
        face_t current_face = this->getFace(i);

        Vertex v_0 = this->getVertex(current_face.vertices[0]);
        Vertex v_1 = this->getVertex(current_face.vertices[1]);
        Vertex v_2 = this->getVertex(current_face.vertices[2]);

        Vector4d vec4d_0 = Vector4d(v_0);
        Vector4d vec4d_1 = Vector4d(v_1);
        Vector4d vec4d_2 = Vector4d(v_2);

        TranslationMatrix matrix_0 = TranslationMatrix(v_0);
        TranslationMatrix matrix_1 = TranslationMatrix(v_1);
        TranslationMatrix matrix_2 = TranslationMatrix(v_2);

        ScaleMatrix sc_matrix_0 = ScaleMatrix(v_0);
        ScaleMatrix sc_matrix_1 = ScaleMatrix(v_1);
        ScaleMatrix sc_matrix_2 = ScaleMatrix(v_2);

        ViewMatrix view_matrix = ViewMatrix();
        ProjectionMatrix projection_matrix = ProjectionMatrix();

        vec4d_0 = projection_matrix * (view_matrix * ((matrix_0 * sc_matrix_0) * vec4d_0));
        vec4d_1 = projection_matrix * view_matrix * matrix_1 * sc_matrix_1 * vec4d_1;
        vec4d_2 = projection_matrix * view_matrix * matrix_2 * sc_matrix_2 * vec4d_2;

        int x_0 = (vec4d_0.x + 1.0) * WIDTH / 2.0;
        int y_0 = (vec4d_0.y + 1.0) * HEIGHT / 2.0;
        int z_0 = (vec4d_0.z + 1.0) * 255 / 2.0;

        int x_1 = (vec4d_1.x + 1.0) * WIDTH / 2.0;
        int y_1 = (vec4d_1.y + 1.0) * HEIGHT / 2.0;
        int z_1 = (vec4d_1.z + 1.0) * 255 / 2.0;

        int x_2 = (vec4d_2.x + 1.0) * WIDTH / 2.0;
        int y_2 = (vec4d_2.y + 1.0) * HEIGHT / 2.0;
        int z_2 = (vec4d_2.z + 1.0) * 255 / 2.0;

        Vertex t_0 = { x_0, y_0, z_0 };
        Vertex t_1 = { x_1, y_1, z_1 };
        Vertex t_2 = { x_2, y_2, z_2 };

        Vertex normal = (t_2 - t_0) ^ (t_1 - t_0);
        Vertex light_dir = { 0, 0, -1 };

        normal.normalize();
        light_dir.normalize();

        double intensity = normal * light_dir;

        if (intensity > 0)
            triangle(t_0, t_1, t_2, width, z_buffer, scene,
                     QColor(0, intensity * 191, intensity * 255));
    }

    delete[] z_buffer;
}

Vertex Object::getVertex(std::size_t number) const
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

Object::Object(const char *const filename)
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
            Vertex v;

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

void Object::transfer(double dx, double dy, double dz)
{
    for (std::size_t i = 0; i < this->getVerticesNumber(); i++)
    {
        this->vertices[i].x += dx;
        this->vertices[i].y += dy;
        this->vertices[i].z += dz;
    }
}

void Object::rotate_x(double degrees)
{
    double radians = degrees * 3.14 / 180;
    double x_old, y_old, z_old;

    for (std::size_t i = 0; i < this->getVerticesNumber(); i++)
    {
        x_old = this->vertices[i].x;
        y_old = this->vertices[i].y;
        z_old = this->vertices[i].z;

        this->vertices[i].y = y_old * cos(radians) - z_old * sin(radians);
        this->vertices[i].z = y_old * sin(radians) + z_old * cos(radians);
    }
}

void Object::rotate_y(double degrees)
{
    double radians = degrees * 3.14 / 180;
    double x_old, y_old, z_old;

    for (std::size_t i = 0; i < this->getVerticesNumber(); i++)
    {
        x_old = this->vertices[i].x;
        y_old = this->vertices[i].y;
        z_old = this->vertices[i].z;

        this->vertices[i].x = z_old * sin(radians) + x_old * cos(radians);
        this->vertices[i].z = y_old * cos(radians) - x_old * sin(radians);
    }
}

void Object::rotate_z(double degrees)
{
    double radians = degrees * 3.14 / 180;
    double x_old, y_old;

    for (std::size_t i = 0; i < this->getVerticesNumber(); i++)
    {
        x_old = this->vertices[i].x;
        y_old = this->vertices[i].y;

        this->vertices[i].x = x_old * cos(radians) - y_old * sin(radians);
        this->vertices[i].y = x_old * sin(radians) + y_old * cos(radians);
    }
}
