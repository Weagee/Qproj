#include "widget.h"
#include <QGridLayout>
#include <QContextMenuEvent>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("右击切换屏幕显示人数");
    initWidget();
    this->resize(QSize(800, 500));
    this->setContextMenuPolicy(Qt::DefaultContextMenu);
}

Widget::~Widget()
{
}

void Widget::initWidget()
{
    initMenu();

    for (int i = 0; i < 9; i++)
    {
        QLabel* label = new QLabel;

        label->setStyleSheet(QString("QLabel{background-image:url(:/new/prefix1/resources/%1.jpg); \
            border:1px solid gray; \
            background-position:center; \
            background-repeat:no-repeat; \
            }").arg(QString::number(i + 1)));

        m_videoLabelList.append(label);
    }

    switchLayout(VideoLayoutType::OneVideo);
}
void Widget::initMenu()
{
    m_switchMenu = new QMenu(this);
    m_switchMenu->addAction("单屏幕");
    m_switchMenu->addAction("四屏幕");
    m_switchMenu->addAction("五屏幕");
    m_switchMenu->addAction("六屏幕");
    m_switchMenu->addAction("九屏幕");

    QMap<QString, int> strTypeMap;
    strTypeMap["单屏幕"] = VideoLayoutType::OneVideo;
    strTypeMap["四屏幕"] = VideoLayoutType::FourVideo;
    strTypeMap["五屏幕"] = VideoLayoutType::FiveVideo;
    strTypeMap["六屏幕"] = VideoLayoutType::SixVideo;
    strTypeMap["九屏幕"] = VideoLayoutType::NineVideo;

    connect(m_switchMenu, &QMenu::triggered, this, [=](QAction* action) {
        QString strText = action->text();
        VideoLayoutType type = VideoLayoutType(strTypeMap[strText]);
        switchLayout(type);
        });
}
void Widget::contextMenuEvent(QContextMenuEvent* event)
{
    m_switchMenu->exec(QCursor::pos());
}

void Widget::switchLayout(VideoLayoutType type)
{
    QLayout* layout = this->layout();
    if (layout)
    {
        QLayoutItem* child;
        while ((child = layout->takeAt(0)) != 0)
        {
            if (child->widget())
            {
                child->widget()->setParent(NULL);
            }
            delete child;
        }
        delete layout;
    }

    switch (type)
    {
    case OneVideo:
    {
        QGridLayout* gLayout = new QGridLayout(this);
        gLayout->addWidget(m_videoLabelList[0]);
        gLayout->setMargin(0);
    }
    break;

    case FourVideo:
    {
        QGridLayout* gLayout = new QGridLayout(this);
        gLayout->setSpacing(0);
        gLayout->setMargin(0);

        for (int i = 0; i < 4; i++)
        {
            gLayout->addWidget(m_videoLabelList[i], i / 2, i % 2);
        }
    }
    break;

    case FiveVideo:
    {
        QVBoxLayout* pVLay = new QVBoxLayout(this);
        pVLay->setSpacing(0);

        QHBoxLayout* pHTopLay = new QHBoxLayout(this);
        pHTopLay->setSpacing(0);
        for (int i = 0; i < 3; i++)
        {
            pHTopLay->addWidget(m_videoLabelList[i]);
        }

        QHBoxLayout* pHBottomLay = new QHBoxLayout(this);
        pHBottomLay->setSpacing(0);
        for (int i = 3; i < 5; i++)
        {
            pHBottomLay->addWidget(m_videoLabelList[i]);
        }

        pVLay->addLayout(pHTopLay);
        pVLay->addLayout(pHBottomLay);

    }
    break;

    case SixVideo:
    {
        QGridLayout* gLayout = new QGridLayout(this);
        gLayout->addWidget(m_videoLabelList[0], 0, 0, 2, 2);
        gLayout->addWidget(m_videoLabelList[1], 0, 2);
        gLayout->addWidget(m_videoLabelList[2], 1, 2);
        gLayout->addWidget(m_videoLabelList[3], 2, 0);
        gLayout->addWidget(m_videoLabelList[4], 2, 1);
        gLayout->addWidget(m_videoLabelList[5], 2, 2);
        gLayout->setSpacing(0);
        gLayout->setMargin(0);
    }
    break;

    case NineVideo:
    {
        QGridLayout* gLayout = new QGridLayout(this);
        gLayout->setSpacing(0);
        gLayout->setMargin(0);

        for (int i = 0; i < 9; i++)
        {
            gLayout->addWidget(m_videoLabelList[i], i / 3, i % 3);
        }
    }
    break;

    default:
        break;
    }
}
