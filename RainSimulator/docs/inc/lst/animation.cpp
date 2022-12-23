void MainWindow::animate()
{
    for (std::size_t i = 0; i < NUM_OF_DROPLETS; i++)
    {
        if (droplets[i]->get_dy() < MIN_DROPLETS_Y)
        {
            droplets[i]->set_dx(droplets[i]->get_dx() - this->sum_dx_delta * this->correction);
            droplets[i]->set_dy(1);
            droplets[i]->set_dz(droplets[i]->get_dz() - this->sum_dz_delta * this->correction);
            continue;
        }
        droplets[i]->translate(dx, dy, dz);
    }
    this->render();
}
