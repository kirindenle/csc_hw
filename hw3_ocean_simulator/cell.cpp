#include "cell.h"
#include <QColor>

bool ICell::isPlant() const
{
    return false;
}

bool ICell::isCreature() const
{
    return false;
}

bool ICell::isWall() const
{
    return false;
}

void Water::make_step(int, int) {}

QColor Water::show() const
{
    return "blue";
}

void Shell::make_step(int, int){}

QColor Shell::show() const
{
    return "pink";
}

bool Shell::isWall() const
{
    return true;
}

void Plant::make_step(int row, int column)
{
    const int direction = rand() % 9;

    const int dir_column = direction % 3 - 1;
    const int dir_row = direction / 3 - 1;

    const int current_point_ind =
            model.row_column_to_array_index(row, column);
    const int next_point_ind =
            model.row_column_to_array_index(row + dir_row, column + dir_column);

    if (next_point_ind != current_point_ind
            && 0 <= next_point_ind && next_point_ind < model.size
            && !model.buffer[next_point_ind]->isWall()
            && !model.buffer[next_point_ind]->isPlant()
            && !model.buffer[next_point_ind]->isCreature())
    {
        model.buffer[next_point_ind] = model.current_state_array[current_point_ind];
        model.buffer[current_point_ind] = model.basic_water;
    }
}

QColor Plant::show() const
{
    return "green";
}

bool Plant::isPlant() const
{
    return true;
}

void Hunter::make_step(int row, int column)
{
    const int direction = rand() % 9;

    const int dir_column = direction % 3 - 1;
    const int dir_row = direction / 3 - 1;

    const int current_point_ind =
            model.row_column_to_array_index(row, column);
    const int next_point_ind =
            model.row_column_to_array_index(row + dir_row, column + dir_column);

    if (next_point_ind != current_point_ind
            && 0 <= row + dir_row && row + dir_row < model.height
            && 0 <= column + dir_column && column + dir_column < model.width
            && !model.buffer[next_point_ind]->isWall())
    {
        if (model.buffer[next_point_ind]->isPlant()
                || model.buffer[next_point_ind]->isCreature())
        {
            model.current_state_array[next_point_ind] = model.basic_water;
        }
        model.buffer[next_point_ind] = model.current_state_array[current_point_ind];
        model.buffer[current_point_ind] = model.basic_water;
    }
}

bool Hunter::isCreature() const
{
    return true;
}

QColor Hunter::show() const
{
    return "red";
}
