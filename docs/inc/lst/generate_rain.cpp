void MainWindow::generateRain(const double density)
{
    const double left_x = -1.4;
    const double up_y = 1.1;
    bool even = 0;
    int cube = cbrt(NUM_OF_DROPLETS);
    double init_dx = left_x, init_dy = up_y, init_dz = 1.6;
    double delta_x = density;
    double delta_y = density;
    double delta_z = density;
    int cube_2 = cube * cube;
    double offset = density / 2.0;
    for (std::size_t i = 0; i < cube; i++)
    {
        for (std::size_t j = 0; j < cube; j++)
        {
            for (std::size_t k = 0; k < cube; k++)
            {
                droplets[i * cube_2 + j * cube + k]->translate(init_dx, init_dy, init_dz);
                init_dx += delta_x;
            }
            if (even)
                init_dx = left_x + offset;
            else
                init_dx = left_x;
            init_dz -= delta_z;
        }
        init_dy -= delta_y;
        if (even)
        {
            even = 0;
            init_dx = left_x;
            init_dz = 1.6;
        }
        else
        {
            even = 1;
            init_dx = left_x + offset;
            init_dz = 1.55;
        }
    }
}
