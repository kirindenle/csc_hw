#include "oceantablemodel.h"
#include <memory>
#include <algorithm>
#include <random>
#include <QColor>
#include <QFile>
#include <QTextStream>

OceanTableModel::OceanTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    QFile file("../ocean_first_try/size.opt");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    in >> width >> height;
    size = width * height;

    random_walk.resize(size);

    for (int i = 0; i < size; ++i)
    {
        current_state_array[i] = basic_water;
    }
    for (int i = 0; i < size; ++i)
    {
        random_walk[i] = i;
    }

    for (auto & cell : current_state_array)
    {
        if (rand() % 5 == 0)
        {
            cell = basic_plant;
        }
        else if (rand() % 11 == 0)
        {
            cell = basic_shell;
        }
        else if (rand() % 13 == 0)
        {
            cell = std::make_shared<Hunter>();
        }
    }

    emit dataChanged(index(0, 0), index(height - 1, width - 1), {CellRole});
}

int OceanTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return height;
}

int OceanTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return width;
}

QVariant OceanTableModel::data(const QModelIndex &index, int) const
{
    if (!index.isValid())
        return QVariant();

    return QVariant(
                current_state_array[
                    row_column_to_array_index(index.row(), index.column())
                ]->show());
}

int OceanTableModel::row_column_to_array_index(int row, int column) const
{
    return row * width + column;
}

void OceanTableModel::nextStep()
{
    std::shuffle(random_walk.begin(), random_walk.end(), std::random_device());

    buffer = current_state_array;


    for (int i : random_walk)
    {
        current_state_array[i]->make_step(i / width, i % width);
    }

    current_state_array = std::move(buffer);
    emit dataChanged(index(0, 0), index(height - 1, width - 1), {CellRole});
}
