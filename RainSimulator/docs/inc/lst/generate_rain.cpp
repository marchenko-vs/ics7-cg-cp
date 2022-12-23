void MainWindow::generateRain()
{
    bool even = 0;
    int cube = cbrt(NUM_OF_DROPLETS);
    double init_dx = -0.8, init_dy = 1.11, init_dz = 0.5;
    double delta_x = 1.5 / (cube - 2);
    double delta_y = 0.05;
    double delta_z = 0.1;
    int cube_2 = cube * cube;
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
                init_dx = -0.8;
            else
                init_dx = -0.75;
            init_dz -= delta_z;
        }
        init_dy -= delta_y;
        if (even)
        {
            even = 0;
            init_dx = -0.8;
            init_dz = 0.5;
        }
        else
        {
            even = 1;
            init_dx = -0.75;
            init_dz = 0.45;
        }
    }
}
