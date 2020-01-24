#ifndef GAMEBOARDDATA_H
#define GAMEBOARDDATA_H
#include <QtCore>
#include <QtGui>

class GameBoardData : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QList<QString> m_data READ getm_data WRITE setm_data NOTIFY m_dataChanged)
    Q_PROPERTY(QString hiddenElement READ gethiddenElement WRITE sethiddenElement NOTIFY hiddenElementChanged)
public:
    GameBoardData(QObject* parent = nullptr);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QString gethiddenElement();
    void sethiddenElement(QString& element);

    QList<QString> getm_data();
    void setm_data(QList<QString>);

    Q_INVOKABLE void shuffle();
signals:
    void hiddenElementChanged();
    void m_dataChanged();
private:
    QList<QString> m_data;
    QString hiddenElement;

};

#endif // GAMEBOARDDATA_H
