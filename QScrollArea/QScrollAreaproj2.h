#pragma once

#include <QtWidgets/QWidget>
#include <QListWidget>
#include <QScrollArea>
#include <QStringList>
#include "firstScroll.h"

class QScrollAreaproj2 : public QWidget
{
    Q_OBJECT

public:
    QScrollAreaproj2(QWidget *parent = nullptr);
    ~QScrollAreaproj2();

private slots:
    void slotItemClicked(QListWidgetItem* item);
    void slotValueChanged(int value);

private:
    QListWidget* myList = nullptr;
    QScrollArea* myScroll = nullptr;
    QStringList myStringList;
    vector<QWidget*> m_vecWidget;

    bool signFlag = false;
};
