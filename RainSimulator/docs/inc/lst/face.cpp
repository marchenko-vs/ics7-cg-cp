class Face
{
public:
    Face() { }
    Face(int a, int b, int c);
    Face(const Face &face);

    int getVertex(int index) const;

    ~Face() { }

private:
    int vertices[3];
};
