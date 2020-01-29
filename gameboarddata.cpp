#include <iterator>
#include <cmath>
#include "gameboarddata.h"

GameBoardData::GameBoardData(int size, QObject* parent) : QAbstractListModel(parent),
    m_size(size), m_dimention(size * size)
{
    Q_UNUSED(parent);
    for (int i = 0; i < m_dimention; i++) {
        m_data.push_back(QString::number(i+1));
    }
    m_dataStart = m_data;
    hiddenElement = m_data.last();
    shuffleAtStart();
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

QString GameBoardData::getHiddenElement() const
{
    return hiddenElement;
}

Position GameBoardData::getPosition(int index) const
{
    int row = index / m_dimention;
    int col = index % m_dimention;

    return Position{row, col};
}

void GameBoardData::shuffleAtStart()
{
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 g(seed);
    do {
        std::shuffle(m_data.begin(), m_data.end(), g);
    } while (!isAggregate());
}

bool GameBoardData::ifNear(int first, int second) const
{
    return ((std::abs(first - second) == 1) || (std::abs(first - second) == 4));
}

bool GameBoardData::isAggregate() const
{
    int inv {0};
    for (int i = 0; i < m_dimention; ++i) {
        if (m_data[i].toInt() == 16) {
            continue;
        }
        for (int j = i; j < m_dimention; ++j) {
            if ((m_data[j].toInt() < m_data[i].toInt())) {
                ++inv;
            }
        }
    }
    auto hidden = std::find(m_data.begin(), m_data.end(), "16");
    int index = hidden - m_data.begin();
    inv += index / m_size + 1;

    return !(inv % 2);
}


void GameBoardData::move(int index)
{
    auto hiddenElementIterator = std::find(m_data.begin(), m_data.end(), hiddenElement);
    int distance = std::abs(std::distance(m_data.begin(), hiddenElementIterator));

    int offsetForHorizontal = index < distance ? 1 : 0;
    int offsetForVertical = index < distance ? 0 : 1;

    if(ifNear(distance, index)) {
        if (std::abs(distance - index) == 1) {

            beginMoveRows(QModelIndex(), index, index, QModelIndex(), distance + offsetForHorizontal);

        } else if (std::abs(distance - index) == m_size) {

            beginMoveRows(QModelIndex(), index, index, QModelIndex(), distance);
            endMoveRows();
            beginMoveRows(QModelIndex(), distance + offsetForVertical,
                          distance + offsetForVertical, QModelIndex(), index + offsetForVertical);

        }
        std::swap(m_data[index], *hiddenElementIterator);
        endMoveRows();
    }
    if (m_data == m_dataStart) {
        emit winGame();
    }

}

void GameBoardData::shuffle()
{
    beginResetModel();
    shuffleAtStart();
    endResetModel();
}
