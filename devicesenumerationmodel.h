#pragma once

#include <QAbstractListModel>

#include "pimpl.h"

namespace recorder
{
struct Process;
}

class DevicesEnumerationModel final : public QAbstractListModel
{
    Q_OBJECT
public:
    enum class Role
    {
        Name = Qt::UserRole + 1
    };

    DevicesEnumerationModel();
    ~DevicesEnumerationModel();

    void append(const recorder::Process& proc);

    int rowCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    DECLARE_PIMPL
};

