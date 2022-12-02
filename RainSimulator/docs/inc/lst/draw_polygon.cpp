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
    for (int i = 0; i < total_height; i++)
    {
        bool second_half = i > t1.get_y() - t0.get_y() || 
                               t1.get_y() == t0.get_y();
        int segment_height = second_half ? t2.get_y() - 
                             t1.get_y() : t1.get_y() - t0.get_y();
        double alpha = (double)i / total_height;
        double beta  = (double)(i - (second_half ? t1.get_y() -
                                t0.get_y() : 0)) / segment_height;
        Vertex A = t0 + (t2 - t0) * alpha;
        Vertex B = second_half ? t1 + (t2 - t1) * 
                   beta : t0 + (t1 - t0) * beta;
        if (A.get_x() > B.get_x())
            std::swap(A, B);
        for (int j = A.get_x(); j <= B.get_x(); j++)
        {
            double phi = B.get_x() == A.get_x() ? 1. : 
                         (double)(j - A.get_x()) /
                         (double)(B.get_x() - A.get_x());
            Vertex P = A + (B - A) * phi;
            int k = P.get_x() + P.get_y() * width;

            if (P.get_x() < 0 || P.get_x() >= WIDTH ||
                    P.get_y() < 0 || P.get_y() >= HEIGHT)
                continue;
            P.set_x(j);
            P.set_y(t0.get_y() + i);
            if (z_buffer[k] < P.get_z())
            {
                z_buffer[k] = P.get_z();
                scene->setPixel(P.get_x(), HEIGHT - 
                                P.get_y() - 1, color.rgb());
            }
        }
    }
}
