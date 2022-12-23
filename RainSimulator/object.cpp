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

Vertex light_dir = Vertex(DEFAULT_LIGHT_X, DEFAULT_LIGHT_Y, DEFAULT_LIGHT_Z);
Vertex from = Vertex(DEFAULT_FROM_X, DEFAULT_FROM_Y, DEFAULT_FROM_Z);
Vertex target = Vertex(0, 0, 0);
Vertex up = Vertex(0, 1, 0);

Object::Object()
{

}

void Object::addVertex(Vertex vertex)
{
    this->vertices.push_back(vertex);
}

void Object::addFace(const Face face)
{
    this->faces.push_back(face);
}

OriginalRainDroplet::OriginalRainDroplet()
{

}

Object::~Object()
{

}

void Object::draw_polygon(Vertex t0, Vertex t1, Vertex t2,
                          int *z_buffer, QImage *scene,
                          QColor color)
{
    if (t0.get_y() == t1.get_y() &&
        t0.get_y() == t2.get_y())
        return;
    if (t0.get_y() > t1.get_y())
        std::swap(t0, t1);
    if (t0.get_y() > t2.get_y())
        std::swap(t0, t2);
    if (t1.get_y() > t2.get_y())
        std::swap(t1, t2);
    int total_height = t2.get_y() - t0.get_y();
    for (std::size_t i = 0; i < total_height; i++)
    {
        bool second_half = i > t1.get_y() - t0.get_y() || t1.get_y() == t0.get_y();
        int segment_height = 0;
        if (second_half)
            segment_height = t2.get_y() - t1.get_y();
        else
            segment_height = t1.get_y() - t0.get_y();
        double alpha = (double)i / total_height;
        double beta  = (double)(i - (second_half ? t1.get_y() -
                                t0.get_y() : 0)) / segment_height;
        Vertex A = t0 + (t2 - t0) * alpha;
        Vertex B;
        if (second_half)
            B = t1 + (t2 - t1) * beta;
        else
            B = t0 + (t1 - t0) * beta;
        if (A.get_x() > B.get_x())
            std::swap(A, B);
        for (int j = A.get_x(); j <= B.get_x(); j++)
        {
            double phi = 0.0;
            if (B.get_x() == A.get_x())
                phi = 1.0;
            else
                phi = (double)(j - A.get_x()) / (double)(B.get_x() - A.get_x());
            Vertex P = A + (B - A) * phi;
            int k = P.get_x() + P.get_y() * WIDTH;

            if (P.get_x() < 0 || round(P.get_x()) >= WIDTH ||
                    P.get_y() < 0 || round(P.get_y()) >= HEIGHT)
                continue;
            P.set_x(j);
            P.set_y(t0.get_y() + i);
            if (z_buffer[k] < P.get_z())
            {
                z_buffer[k] = P.get_z();
                scene->setPixel(P.get_x(), HEIGHT - P.get_y() - 1, color.rgb());
            }
        }
    }
}

void Object::draw(const std::size_t width, const std::size_t height,
                  uint8_t red, uint8_t green, uint8_t blue, QImage *scene)
{
    Matrix scaling_matrix = Matrix::getScalingMatrix(*this);
    Matrix rotation_matrix = Matrix::getRotationMatrix(*this);
    Matrix translation_matrix = Matrix::getTranslationMatrix(*this);
    Matrix model_matrix = translation_matrix * rotation_matrix * scaling_matrix;
    Matrix look_at_matrix = Matrix::getLookAtMatrix(from, target, up);
    Matrix projection_matrix = Matrix::getProjectionMatrix(90, (double)WIDTH / (double)HEIGHT,
                                                           0.1, 1.0);
    Matrix mvp_matrix = projection_matrix * look_at_matrix * model_matrix;
    for (std::size_t i = 0; i < this->getFacesNumber(); i++)
    {
        Face current_face = Face(this->getFace(i));
        Vertex v_0 = this->getVertex(current_face.getVertex(0));
        Vertex v_1 = this->getVertex(current_face.getVertex(1));
        Vertex v_2 = this->getVertex(current_face.getVertex(2));
        Vector4d vec4d_0 = Vector4d(v_0);
        Vector4d vec4d_1 = Vector4d(v_1);
        Vector4d vec4d_2 = Vector4d(v_2);
        vec4d_0 = mvp_matrix * vec4d_0;
        vec4d_1 = mvp_matrix * vec4d_1;
        vec4d_2 = mvp_matrix * vec4d_2;
        int x_0 = (vec4d_0.get_x() + 1) * WIDTH / 2.0;
        int y_0 = (vec4d_0.get_y() + 1) * HEIGHT / 2.0;
        int z_0 = (vec4d_0.get_z() + 1) * DEPTH;
        int x_1 = (vec4d_1.get_x() + 1) * WIDTH / 2.0;
        int y_1 = (vec4d_1.get_y() + 1) * HEIGHT / 2.0;
        int z_1 = (vec4d_1.get_z() + 1) * DEPTH;
        int x_2 = (vec4d_2.get_x() + 1) * WIDTH / 2.0;
        int y_2 = (vec4d_2.get_y() + 1) * HEIGHT / 2.0;
        int z_2 = (vec4d_2.get_z() + 1) * DEPTH;
        Vertex t_0 = { x_0, y_0, z_0 };
        Vertex t_1 = { x_1, y_1, z_1 };
        Vertex t_2 = { x_2, y_2, z_2 };
        Vertex normal = (t_2 - t_0) ^ (t_1 - t_0);
        normal.normalize();
        light_dir.normalize();
        double intensity = normal * light_dir;
        draw_polygon(t_0, t_1, t_2, z_buffer, scene,
                     QColor(intensity * red,
                            intensity * green,
                            intensity * blue));
    }
}

void RainDroplet::draw(const std::size_t width, const std::size_t height,
                       uint8_t red, uint8_t green, uint8_t blue, QImage *scene)
{
    Matrix scaling_matrix = Matrix::getScalingMatrix(*this);
    Matrix rotation_matrix = Matrix::getRotationMatrix(*this);
    Matrix translation_matrix = Matrix::getTranslationMatrix(*this);
    Matrix model_matrix = translation_matrix * rotation_matrix * scaling_matrix;
    Matrix look_at_matrix = Matrix::getLookAtMatrix(from, target, up);
    Matrix projection_matrix = Matrix::getProjectionMatrix(90, (double)WIDTH / (double)HEIGHT,
                                                           0.1, 1.0);
    Matrix mvp_matrix = projection_matrix * look_at_matrix * model_matrix;
    for (std::size_t i = 0; i < this->ptr->getFacesNumber(); i++)
    {
        Face current_face = this->ptr->getFace(i);
        Vertex v_0 = this->ptr->getVertex(current_face.getVertex(0));
        Vertex v_1 = this->ptr->getVertex(current_face.getVertex(1));
        Vertex v_2 = this->ptr->getVertex(current_face.getVertex(2));
        Vector4d vec4d_0 = Vector4d(v_0);
        Vector4d vec4d_1 = Vector4d(v_1);
        Vector4d vec4d_2 = Vector4d(v_2);
        vec4d_0 = mvp_matrix * vec4d_0;
        vec4d_1 = mvp_matrix * vec4d_1;
        vec4d_2 = mvp_matrix * vec4d_2;
        int x_0 = (vec4d_0.get_x() + 1) * WIDTH / 2.0;
        int y_0 = (vec4d_0.get_y() + 1) * HEIGHT / 2.0;
        int z_0 = (vec4d_0.get_z() + 1) * DEPTH;
        int x_1 = (vec4d_1.get_x() + 1) * WIDTH / 2.0;
        int y_1 = (vec4d_1.get_y() + 1) * HEIGHT / 2.0;
        int z_1 = (vec4d_1.get_z() + 1) * DEPTH;
        int x_2 = (vec4d_2.get_x() + 1) * WIDTH / 2.0;
        int y_2 = (vec4d_2.get_y() + 1) * HEIGHT / 2.0;
        int z_2 = (vec4d_2.get_z() + 1) * DEPTH;

        Vertex t_0 = { x_0, y_0, z_0 };
        Vertex t_1 = { x_1, y_1, z_1 };
        Vertex t_2 = { x_2, y_2, z_2 };

        Vertex normal = (t_2 - t_0) ^ (t_1 - t_0);

        normal.normalize();
        light_dir.normalize();

        double intensity = normal * light_dir;

        draw_polygon(t_0, t_1, t_2, z_buffer, scene,
                     QColor(intensity * red,
                            intensity * green,
                            intensity * blue));
    }
}

Vertex Object::getVertex(std::size_t number)
{
    return this->vertices[number];
}

Face Object::getFace(std::size_t number)
{
    return this->faces[number];
}

std::size_t Object::getVerticesNumber()
{
    return this->vertices.size();
}

std::size_t Object::getFacesNumber()
{
    return this->faces.size();
}

Object::Object(const char *const filename)
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
            double x, y, z;

            iss >> x;
            iss >> y;
            iss >> z;

            Vertex v = Vertex(x, y, z);

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

            Face face = Face(f[0], f[1], f[2]);
            this->faces.push_back(face);
        }
    }

    input_file.close();

    this->set_dx(0.0);
    this->set_dy(0.0);
    this->set_dz(0.0);

    this->set_kx(1.0);
    this->set_ky(1.0);
    this->set_kz(1.0);

    this->set_phi_x(0.0);
    this->set_phi_y(0.0);
    this->set_phi_z(0.0);
}

OriginalRainDroplet::OriginalRainDroplet(const char *const filename)
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
            double x, y, z;

            iss >> x;
            iss >> y;
            iss >> z;

            Vertex v = Vertex(x, y, z);
            this->addVertex(v);
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

            Face face = Face(f[0], f[1], f[2]);
            this->addFace(face);
        }
    }

    input_file.close();

    this->set_dx(0.0);
    this->set_dy(0.0);
    this->set_dz(0.0);

    this->set_kx(.01);
    this->set_ky(.01);
    this->set_kz(.01);

    this->set_phi_x(0.0);
    this->set_phi_y(0.0);
    this->set_phi_z(0.0);
}

RainDroplet::RainDroplet(OriginalRainDroplet *object)
{
    this->ptr = object;

    this->set_dx(0.0);
    this->set_dy(0.0);
    this->set_dz(0.0);

    this->set_kx(.005);
    this->set_ky(.005);
    this->set_kz(.005);

    this->set_phi_x(0.0);
    this->set_phi_y(0.0);
    this->set_phi_z(0.0);
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
            double x, y, z;

            iss >> x;
            iss >> y;
            iss >> z;

            Vertex v = Vertex(x, y, z);
            this->addVertex(v);
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

            Face face = Face(f[0], f[1], f[2]);
            this->addFace(face);
        }
    }

    input_file.close();

    this->set_dx(0.0);
    this->set_dy(0.0);
    this->set_dz(0.0);

    this->set_kx(1.0);
    this->set_ky(1.0);
    this->set_kz(1.0);

    this->set_phi_x(0.0);
    this->set_phi_y(0.0);
    this->set_phi_z(0.0);
}

void Object::translate(double dx, double dy, double dz)
{
    this->dx += dx;
    this->dy += dy;
    this->dz += dz;
}

void Object::scale(double kx, double ky, double kz)
{
    this->kx += kx;
    this->ky += ky;
    this->kz += kz;
}

void Object::rotate(double phi_x, double phi_y, double phi_z)
{
    this->phi_x += phi_x * 3.14 / 180;
    this->phi_y += phi_y * 3.14 / 180;
    this->phi_z += phi_z * 3.14 / 180;
}

double Object::get_dx() const
{
    return this->dx;
}

double Object::get_dy() const
{
    return this->dy;
}

double Object::get_dz() const
{
    return this->dz;
}

double Object::get_kx() const
{
    return this->kx;
}

double Object::get_ky() const
{
    return this->ky;
}

double Object::get_kz() const
{
    return this->kz;
}

double Object::get_phi_x() const
{
    return this->phi_x;
}

double Object::get_phi_y() const
{
    return this->phi_y;
}

double Object::get_phi_z() const
{
    return this->phi_z;
}

void Object::set_kx(double kx)
{
    this->kx = kx;
}

void Object::set_ky(double ky)
{
    this->ky = ky;
}

void Object::set_kz(double kz)
{
    this->kz = kz;
}

void Object::set_dx(double dx)
{
    this->dx = dx;
}

void Object::set_dy(double dy)
{
    this->dy = dy;
}

void Object::set_dz(double dz)
{
    this->dz = dz;
}

void Object::set_phi_x(double phi_x)
{
    this->phi_x = phi_x;
}

void Object::set_phi_y(double phi_y)
{
    this->phi_y = phi_y;
}

void Object::set_phi_z(double phi_z)
{
    this->phi_z = phi_z;
}
