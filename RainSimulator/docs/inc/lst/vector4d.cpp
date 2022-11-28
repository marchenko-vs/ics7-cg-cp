class Vector4d
{
public:
    double x, y, z, w;
public:
    Vector4d();
    Vector4d(const double x, const double y, const double z,
             const double w);
    Vector4d(const Vertex &vertex);

    void normalize(void);

    Vector4d operator + (const Vector4d &vertex);
    Vector4d operator - (const Vector4d &vertex);
    Vector4d operator * (const double multiplier);
    Vector4d operator ^ (const Vector4d &vertex);
    double operator * (const Vector4d &vertex);
};
