#define SIZE 4

class Matrix
{
public:
    Matrix();
    static Matrix getScalingMatrix(const Object& object);
    static Matrix getTranslationMatrix(const Object& object);
    static Matrix getTranslationMatrix(const double x,
                                       const double y,
                                       const double z);
    static Matrix getRotationMatrix(const Object& object);
    static Matrix getLookAtMatrix(Vertex& eye, Vertex& target,
                                  Vertex& up);
    static Matrix getProjectionMatrix(double fov, double aspect,
                                      double znear, double zfar);
    Matrix operator * (const Matrix &matrix);
    Vector4d operator * (const Vector4d &vector);
    ~Matrix() { }

private:
    double elements[SIZE][SIZE];
};
