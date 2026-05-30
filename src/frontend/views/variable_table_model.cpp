#include "variable_table_model.h"
#include <algorithm>

using std::in_range;


VariableTableModel::VariableTableModel( QObject* parent )
    : QAbstractTableModel( parent ) {}

int VariableTableModel::rowCount( const QModelIndex& parent ) const
{
    if ( parent.isValid() )
        return 0;
    return static_cast<int>(m_variables.size());
}

int VariableTableModel::columnCount( const QModelIndex& parent ) const
{
    if ( parent.isValid() )
        return 0;
    return 2;
}

QVariant VariableTableModel::data( const QModelIndex& index, int role ) const
{
    if ( not index.isValid() )
        return {};

    const auto row = index.row();

    if ( not in_range<size_t>(row) )
        return {};

    const auto col = index.column();

    const auto& var = m_variables[static_cast<size_t>(row)];
    const auto name = QString::fromStdString(var.variable_name.to_string());
    const auto value = var.int_value;

    if ( role == Qt::DisplayRole || role == Qt::EditRole )
    {
        switch ( col )
        {
            case 0: return name;
            case 1: return value;
            default: return {};
        }
    }

    if ( role == Qt::TextAlignmentRole )
    {
        if ( col == 1 )
            return Qt::AlignCenter;
    }

    if (role == Qt::ToolTipRole)
        return QString("%1 = %2").arg(name).arg(value);

    return {};
}

QVariant VariableTableModel::headerData( const int section, const Qt::Orientation orientation, const int role ) const
{
    if (role != Qt::DisplayRole)
        return {};

    if (orientation == Qt::Horizontal)
    {
        switch (section)
        {
            case 0: return "Name";
            case 1: return "Value";
            default : return {};
        }
    }
    return section + 1;
}

void VariableTableModel::set_variables( std::vector<GamGlobalVariable> variables )
{
    beginResetModel();
    m_variables = std::move( variables );
    endResetModel();
}

const GamGlobalVariable* VariableTableModel::at( const int row ) const
{
    if ( !in_range<size_t>(row) || static_cast<size_t>(row) >= m_variables.size() )
        return nullptr;
    return &m_variables[static_cast<size_t>(row)];
}

Qt::ItemFlags VariableTableModel::flags( const QModelIndex& index ) const
{
    if (not index.isValid())
        return Qt::NoItemFlags;

    Qt::ItemFlags result = QAbstractTableModel::flags(index);
    switch (index.column()) {
        case 0:
        case 1:
            result |= Qt::ItemIsEditable;
            break;
        default:
            break;
    }

    return result;
}

bool VariableTableModel::setData( const QModelIndex& index, const QVariant& value, const int role )
{
    if (!index.isValid() || role != Qt::EditRole)
        return false;

    const auto row = index.row();
    const auto col = index.column();

    if ( !in_range<size_t>(row) || static_cast<size_t>(row) >= m_variables.size() )
        return false;

    if ( col < 0 || col >= columnCount(QModelIndex{}) )
        return false;

    auto& var = m_variables[static_cast<size_t>(row)];

    switch ( col ) {
        case 0: {
            if ( !var.variable_name.assign_string( value.toString().toStdString() ) )
                return false;
            break;
        }

        case 1: {
            bool ok = false;
            const int parsed = value.toInt(&ok);

            if (!ok)
                return false;
            var.int_value = parsed;
            break;
        }
        default:
            return false;
    }

    emit dataChanged(index, index, { Qt::DisplayRole, Qt::EditRole });

    return true;
}

bool VariableTableModel::removeRows(const int row, const int count, const QModelIndex& parent)
{
    if ( parent.isValid() || count != 1 || !in_range<size_t>(row) ||
        static_cast<size_t>(row) >= m_variables.size() )
    {
        return false;
    }

    beginRemoveRows( parent, row, row );
    m_variables.erase(m_variables.begin() + row );
    endRemoveRows();

    return true;
}
