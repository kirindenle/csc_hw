#pragma once

#include "oceantablemodel.h"

class OceanTableModel;

class ICell
{
public:
    virtual ~ICell(){}
    virtual void make_step(int row, int column) = 0;
    virtual QColor show() const = 0;
    virtual bool isPlant() const;
    virtual bool isCreature() const;
    virtual bool isWall() const;
    static OceanTableModel & model;
};

class Water : public ICell
{
public:
    void make_step(int row, int column) override;
    QColor show() const override;
};

class Shell : public ICell
{
public:
    void make_step(int row, int column) override;
    QColor show() const override;
    bool isWall() const override;
};

class Plant : public ICell
{
public:
    void make_step(int row, int column) override;
    QColor show() const override;
    virtual bool isPlant() const override;
};

class Hunter : public ICell
{
public:
    void make_step(int row, int column) override;
    virtual bool isCreature() const override;
    QColor show() const override;
};
