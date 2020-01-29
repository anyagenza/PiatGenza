#pragma once
#include <QAbstractItemModel>


struct Position {
    int x;
    int y;
};

class GameBoardData : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString hiddenElement READ getHiddenElement NOTIFY hiddenElementChanged)

public:
    GameBoardData(int size = 4, QObject* parent = nullptr);
    Q_INVOKABLE void move(int);
    Q_INVOKABLE void shuffle();

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QString getHiddenElement() const;

private:
    bool ifNear(int first, int secoond) const;
    bool isAggregate() const;
    Position getPosition(int index) const;
    void shuffleAtStart();

signals:
    void hiddenElementChanged();
    void winGame();

private:
    QList<QString> m_data;
    QList<QString> m_dataStart;
    QString hiddenElement;
    const int m_size;
    const int m_dimention;

};

