#include <QtGui>
#include <QtCore>
#include <iterator>
#include <cmath>
#include "gameboarddata.h"

GameBoardData::GameBoardData(int size, QObject* parent) : m_size(size), m_dimention(size * size)
{
    Q_UNUSED(parent);
    for (int i = 0; i < m_dimention; i++) {
        m_data.push_back(QString::number(i+1));
    }
    m_dataStart = m_data;
    hiddenElement = m_data.last();
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

QString GameBoardData::gethiddenElement() const
{
    return hiddenElement;
}

void GameBoardData::sethiddenElement(QString& element)
{
    hiddenElement = element;
}

Position GameBoardData::getPosition(int index) const
{
    int row = index / m_dimention;
    int col = index % m_dimention;

    return Position{row, col};
}

bool GameBoardData::ifNear(int first, int second) const
{
    if ((std::abs(first - second) == 1)||(std::abs(first - second) == 4))
    {
        return true;
    }
    else
        return false;
}

bool GameBoardData::isAggregate() const
{
    int inv {0};
        for (int i = 0; i < m_dimention; ++i) {
            for (int j = 0; j < i; ++j) {
                if (m_data[j] > m_data[i]) {
                    ++inv;
                }
            }
        }

        const int start_point = 1;

        for (int i = 0; i < m_dimention; ++i) {
            if (m_data[i] == m_dimention){
                inv += start_point + i / m_size;
            }
        }

        return (inv % 2) == 0;
}


void GameBoardData::move(int index)
{
    auto hiddenElementIterator = std::find(m_data.begin(), m_data.end(), hiddenElement);
    int distance = std::abs(std::distance(m_data.begin(), hiddenElementIterator));

    int offsetForHorizontal = index < distance ? 1 : 0;
    int offsetForVertical = index < distance ? 0 : 1;

    if(ifNear(distance, index))
    {
        {
            if (std::abs(distance - index) == 1)
                        beginMoveRows(QModelIndex(), index, index, QModelIndex(), distance + offsetForHorizontal);
            else if (std::abs(distance - index) == m_size) {
                beginMoveRows(QModelIndex(), index, index, QModelIndex(), distance);
                endMoveRows();
                beginMoveRows(QModelIndex(), distance + offsetForVertical,
                              distance + offsetForVertical, QModelIndex(), index + offsetForVertical);
            }

        }
        std::swap(m_data[index], *hiddenElementIterator);
        endMoveRows();
    }
    if (m_data == m_dataStart)
    {
        emit winGame();
    }
}


void GameBoardData::shuffle()
{
    beginResetModel();
    do {
        auto seed = std::chrono::system_clock::now().time_since_epoch().count();
        static std::mt19937 g(seed);
        std::shuffle(m_data.begin(), m_data.end(), g);
    } while (!isAggregate());
    endResetModel();
}
