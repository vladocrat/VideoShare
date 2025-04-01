#include "devicesenumerationmodel.h"

#include <QList>

#include "recorder/process.h"

struct DevicesEnumerationModel::impl_t
{
    QList<recorder::Process> processes;
};

DevicesEnumerationModel::DevicesEnumerationModel()
{
    createImpl();
}

DevicesEnumerationModel::~DevicesEnumerationModel()
{

}

void DevicesEnumerationModel::append(const recorder::Process& proc)
{
    beginInsertColumns(QModelIndex(), 0, 0);
    impl().processes.append(proc);
    endInsertColumns();
}

int DevicesEnumerationModel::rowCount(const QModelIndex& parent) const
{
    return impl().processes.size();
}

QVariant DevicesEnumerationModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const auto value = impl().processes.at(index.row());

    switch (static_cast<Role>(role)) {
    case Role::Name:
        return value.name;
    }

    return QVariant();
}

QHash<int, QByteArray> DevicesEnumerationModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[static_cast<int>(Role::Name)] = "name";
    return roles;
}
