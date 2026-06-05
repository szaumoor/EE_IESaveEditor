#ifndef EE_SAVEEDITOR_VARIABLE_TABLE_MODEL_H
#define EE_SAVEEDITOR_VARIABLE_TABLE_MODEL_H

#include <vector>

#include <QAbstractTableModel>
#include <QVariant>

#include "../../backend/binary_layouts/gam.h"


class VariableTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit VariableTableModel( QObject *parent = nullptr );

    [[nodiscard]]
    int rowCount( const QModelIndex& parent ) const override;

    [[nodiscard]]
    int columnCount( const QModelIndex& parent ) const override;

    [[nodiscard]]
    QVariant data( const QModelIndex& index, int role ) const override;

    [[nodiscard]]
    QVariant headerData( int section, Qt::Orientation orientation, int role ) const override;

    void set_variables(std::vector<GamGlobalVariable> variables);

    [[nodiscard]]
    const GamGlobalVariable* at(int row) const;

    [[nodiscard]]
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    bool setData(const QModelIndex& index, const QVariant& value, int role) override;

    bool removeRows(int row, int count, const QModelIndex& parent) override;

private:
    std::vector<GamGlobalVariable> m_variables;
};


#endif //EE_SAVEEDITOR_VARIABLE_TABLE_MODEL_H
