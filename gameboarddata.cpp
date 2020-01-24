#include <QtGui>
#include <QtCore>
#include "gameboarddata.h"

GameBoardData::GameBoardData(QObject* parent)
{
    Q_UNUSED(parent);
    //int i = 42;
    //QString s = QString::number(i);
    m_data = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16"};
    hiddenElement = "16";
}

QVariant GameBoardData::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row < 0 || row >= m_data.count()) {
            return QVariant();
        }
    switch(role) {
            case Qt::DisplayRole:
                return m_data.value(row);
        }
        return QVariant();
}

int GameBoardData::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.count();
}

QString GameBoardData::gethiddenElement()
{
    return hiddenElement;
}

void GameBoardData::sethiddenElement(QString& element)
{
    hiddenElement = element;
}

QList<QString> GameBoardData::getm_data()
{
    return m_data;
}

void GameBoardData::setm_data(QList<QString> newData)
{
    m_data = newData;
}

void GameBoardData::shuffle()
{
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937 g(seed);
    std::shuffle(m_data.begin(), m_data.end(), g);
    emit m_dataChanged();
    qDebug() << "shhhh";


}
