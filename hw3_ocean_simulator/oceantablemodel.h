#pragma once

#include <QAbstractTableModel>
#include <array>
#include "cell.h"

class ICell;
class Water;
class Shell;
class Plant;

class OceanTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:

    static constexpr int max_width = 256;
    static constexpr int max_height = 256;
    static constexpr int max_size = max_width * max_height;
    typedef std::array<std::shared_ptr<ICell>, max_size> field_container;

    int row_column_to_array_index(int row, int column) const;

    explicit OceanTableModel(QObject *parent = nullptr);

    // QAbstractTableModel requirements:
    enum Roles {
        CellRole
    };

    QHash<int, QByteArray> roleNames() const override {
        return {
            { CellRole, "color" }
        };
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // QAbstractTableModel end requirements.

    Q_INVOKABLE void nextStep();

    std::shared_ptr<Water> basic_water = std::make_shared<Water>();
    std::shared_ptr<Plant> basic_plant = std::make_shared<Plant>();
    std::shared_ptr<Shell> basic_shell = std::make_shared<Shell>();

    int width = 10;
    int height = 10;
    int size = width * height;

    field_container current_state_array;
    field_container buffer;

    std::vector<int> random_walk;

    QChar shelf = 's';
    QChar water = 'w';
    QChar creature = 'c';

};
