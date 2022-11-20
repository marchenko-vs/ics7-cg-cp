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
#include <QImage>

Object::Object()
{

}

RainDroplet::RainDroplet()
{

}

RainDroplet::RainDroplet(const RainDroplet &object)
{
    for (std::size_t i = 0; i < object.getVerticesNumber(); i++)
        this->vertices.push_back(object.vertices[i]);
    for (std::size_t i = 0; i < object.getFacesNumber(); i++)
        this->faces.push_back(object.faces[i]);
}

Object::~Object()
{

}

void Object::triangle(Vertex t0, Vertex t1, Vertex t2, const int width,
                      int *z_buffer, QImage *scene, QColor color)
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
                scene->setPixel(P.x, P.y, color.rgb());
            }
        }
    }
}

void Object::draw(const std::size_t width, const std::size_t height,
                  uint8_t red, uint8_t green, uint8_t blue, QImage *scene)
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

        TranslationMatrix translation_matrix_0 = TranslationMatrix(v_0);
        TranslationMatrix translation_matrix_1 = TranslationMatrix(v_1);
        TranslationMatrix translation_matrix_2 = TranslationMatrix(v_2);

        ScaleMatrix scale_matrix_0 = ScaleMatrix(v_0);
        ScaleMatrix scale_matrix_1 = ScaleMatrix(v_1);
        ScaleMatrix scale_matrix_2 = ScaleMatrix(v_2);

        RotateMatrix rotate_matrix_0 = RotateMatrix(v_0);
        RotateMatrix rotate_matrix_1 = RotateMatrix(v_1);
        RotateMatrix rotate_matrix_2 = RotateMatrix(v_2);

        ViewMatrix view_matrix = ViewMatrix();
        ProjectionMatrix projection_matrix = ProjectionMatrix();

        vec4d_0 = projection_matrix * view_matrix * translation_matrix_0 *
                rotate_matrix_0 * scale_matrix_0 * vec4d_0;
        vec4d_1 = projection_matrix * view_matrix * translation_matrix_1 *
                rotate_matrix_1 * scale_matrix_1 * vec4d_1;
        vec4d_2 = projection_matrix * view_matrix * translation_matrix_2 *
                rotate_matrix_2 * scale_matrix_2 * vec4d_2;

        int x_0 = (vec4d_0.x + 1.0) * WIDTH / 2.0;
        int y_0 = (vec4d_0.y + 1.0) * HEIGHT / 2.0;
        int z_0 = (vec4d_0.z + 1.0) * 255 / 2.0;

        int x_1 = (vec4d_1.x + 1.0) * WIDTH / 2.0;
        int y_1 = (vec4d_1.y + 1.0) * HEIGHT / 2.0;
        int z_1 = (vec4d_1.z + 1.0) * 255 / 2.0;

        int x_2 = (vec4d_2.x + 1.0) * WIDTH / 2.0;
        int y_2 = (vec4d_2.y + 1.0) * HEIGHT / 2.0;
        int z_2 = (vec4d_2.z + 1.0) * 255 / 2.0;

        if (x_0 > WIDTH || y_0 > HEIGHT ||
                x_1 > WIDTH || y_1 > HEIGHT ||
                x_2 > WIDTH || y_2 > HEIGHT ||
                x_0 < 0 || y_0 < 0 ||
                                x_1 < 0 || y_1 < 0 ||
                                x_2 < 0 || y_2 < 0)
            continue;

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
                     QColor(intensity * red, intensity * green, intensity * blue));
        else
            triangle(t_0, t_1, t_2, width, z_buffer, scene,
                     QColor(intensity * red, intensity * green, intensity * blue));
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

RainDroplet::RainDroplet(const char *const filename)
{
    std::ifstream input_file;
    input_file.open(filename, std::ifstream::in);

    if (input_file.fail())
        return;

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

    this->scale(-0.9, -0.9, -0.9);
}

Ground::Ground(const char *const filename)
{
    std::ifstream input_file;
    input_file.open(filename, std::ifstream::in);

    if (input_file.fail())
        return;

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

    this->rotate(-10, 0, 0);
    this->translate(0, -1, 0);
}

void Object::translate(double dx, double dy, double dz)
{
    for (std::size_t i = 0; i < this->getVerticesNumber(); i++)
    {
        this->vertices[i].x += dx;
        this->vertices[i].y += dy;
        this->vertices[i].z += dz;
    }
}

void Object::scale(double kx, double ky, double kz)
{
    for (std::size_t i = 0; i < this->getVerticesNumber(); i++)
    {
        this->vertices[i].kx += kx;
        this->vertices[i].ky += ky;
        this->vertices[i].kz += kz;
    }
}

void Object::rotate(double phi_x, double phi_y, double phi_z)
{
    for (std::size_t i = 0; i < this->getVerticesNumber(); i++)
    {
        this->vertices[i].phi_x += phi_x * 3.14 / 180;
        this->vertices[i].phi_y += phi_y * 3.14 / 180;
        this->vertices[i].phi_z += phi_z * 3.14 / 180;
    }
}
