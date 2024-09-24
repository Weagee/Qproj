#include "QScrollAreaproj2.h"
#include <QHBoxLayout>
#include <string>
#include <QScrollBar>
using namespace std;
QScrollAreaproj2::QScrollAreaproj2(QWidget *parent)
    : QWidget(parent)
{
	setFixedSize(150 + 1000 + 30 + 15, 900);
	this->setStyleSheet("background-color:rgb(26, 26, 26)");
    myList = new QListWidget(this);
    myScroll = new QScrollArea(this);
    myList->setFixedWidth(150);
    myScroll->setFixedWidth(1000+30);
    QHBoxLayout* HLayout = new QHBoxLayout(this);
    HLayout->addWidget(myList);
    HLayout->addWidget(myScroll);

    myStringList << u8"基本" << u8"云盘" << u8"下载" << u8"接管" << u8"任务管理" << u8"提醒"<< u8"悬浮框" << u8"高级设置";
    myList->addItems(myStringList);

	string list_qss = R"(
		QListWidget
		{
			/*border:1px solid gray;   */
			background:rgb(26, 26, 26);  
			color:rgb(200, 200, 200);    
			font-size:15px;
			border-radius:1px;
		}

		QListWidget::item
		{
			height:40px;
			padding-left:10px; 
		}
		
		QListWidget::item:!active
		{
			background:rgb(26, 26, 26);
			margin:5px 20px 1px 20px;  
		}

		QListWidget::item:hover
		{
			background:rgb(56, 56, 56);
			padding-left:30px;
		}

		QListWidget::item:selected
		{
			border-radius:15px;
			background:lightblue;
		}


		QListWidget::item:selected:!active
		{
			background:rgb(51,51,51);
			color:#3F85FF;
		})";

	myList->setStyleSheet(QString::fromStdString(list_qss));



	myScroll = new QScrollArea(this);
	myScroll->setFixedWidth(1000 + 30);
	myScroll->setFrameShape(QFrame::NoFrame);//
	myScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	myScroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	string verticalbar_qss = R"(
		QScrollBar{width:16px;background:rgb(26, 26, 26);margin:0px, 0px, 0px, 0px;}
		QScrollBar::handle:vertical{width:8px;background:rgba(162, 163, 165, 100%);border-radius:4px;min-height:40;}
              QScrollBar::handle:vertical:hover{width:8px;background:rgba(115,118,118, 100%);border-radius:4px;min-height:40;}
              QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical{background:rgb(26, 26, 26);border-radius:4px;}
              QScrollBar::top-arrow:vertical,QScrollBar::bottom-arrow:vertical{border: none;background: none;color: none;}
              QScrollBar::add-line:vertical{border:none;background:none;}
              QScrollBar::sub-line:vertical{border:none;background:none;}
		)";

	myScroll->verticalScrollBar()->setStyleSheet(QString::fromStdString(verticalbar_qss));

	QWidget *m_pBaseSetWidget = new firstScroll(this);
	m_vecWidget.push_back(m_pBaseSetWidget);
	
	QWidget *m_pYunpanSetWidget = new QWidget(this);
	m_pYunpanSetWidget->setStyleSheet("background-image:url(:/QScrollAreaproj2/resources/YunPanSet.png);background-repeat: no-repeat;background-color:rgb(51, 51, 51)");
	m_pYunpanSetWidget->setFixedSize(1000, 478);
	m_vecWidget.push_back(m_pYunpanSetWidget);

	QWidget *m_pDownloadWidget = new QWidget(this);
	m_pDownloadWidget->setStyleSheet("background-image:url(:/QScrollAreaproj2/resources/XiaZai.png);background-repeat: no-repeat;background-color:rgb(51, 51, 51)");
	m_pDownloadWidget->setFixedSize(1000, 337);
	m_vecWidget.push_back(m_pDownloadWidget);

	QWidget*m_pJieguanWidget = new QWidget(this);
	m_pJieguanWidget->setStyleSheet("background-image:url(:/QScrollAreaproj2/resources/JieGuanSet.png);background-repeat: no-repeat;background-color:rgb(51, 51, 51)");
	m_pJieguanWidget->setFixedSize(1000, 340);
	m_vecWidget.push_back(m_pJieguanWidget);

	QWidget*m_pRenwuWidget = new QWidget(this);
	m_pRenwuWidget->setStyleSheet("background-image:url(:/QScrollAreaproj2/resources/RenwuGuanli.png);background-repeat: no-repeat;background-color:rgb(51, 51, 51)");
	m_pRenwuWidget->setFixedSize(1000, 413);
	m_vecWidget.push_back(m_pRenwuWidget);

	QWidget*m_pTixingWidget = new QWidget(this);
	m_pTixingWidget->setStyleSheet("background-image:url(:/QScrollAreaproj2/resources/TiXing.png);background-repeat: no-repeat;background-color:rgb(51, 51, 51)");
	m_pTixingWidget->setFixedSize(1000, 728);
	m_vecWidget.push_back(m_pTixingWidget);

	QWidget*m_pXuanfuWidget = new QWidget(this);
	m_pXuanfuWidget->setStyleSheet("background-image:url(:/QScrollAreaproj2/resources/XuanFuChuang.png);background-repeat: no-repeat;background-color:rgb(51, 51, 51)");
	m_pXuanfuWidget->setFixedSize(1000, 206);
	m_vecWidget.push_back(m_pXuanfuWidget);



	QWidget* widget = new QWidget;

	QVBoxLayout* pVLay = new QVBoxLayout(widget);

	for (auto w : m_vecWidget)
	{
		pVLay->addWidget(w);
		pVLay->addSpacing(15);
	}

	pVLay->setContentsMargins(0, 5, 0, 5);

	myScroll->setWidget(widget);

	QHBoxLayout* hlay = new QHBoxLayout(this);
	hlay->addWidget(myList);
	hlay->setSpacing(0);
	hlay->addWidget(myScroll);


	connect(myList, &QListWidget::itemClicked, this, &QScrollAreaproj2::slotItemClicked);

	connect(myScroll->verticalScrollBar(), &QScrollBar::valueChanged,
		this, &QScrollAreaproj2::slotValueChanged);

}

QScrollAreaproj2::~QScrollAreaproj2()
{}


void QScrollAreaproj2::slotItemClicked(QListWidgetItem* item)
{
	signFlag = true;
	QString itemText = item->text();
	QPoint widgetPos;

	int size = myStringList.size();
	for (int i = 0; i < size; i++)
	{
		if (itemText == myStringList[i])
		{
			widgetPos = m_vecWidget[i]->pos();
		}
	}
	myScroll->verticalScrollBar()->setValue(widgetPos.y());
}

void QScrollAreaproj2::slotValueChanged(int value)
{
	if (!signFlag)
	{
		int itemSize = m_vecWidget.size();
		for (int i = 0; i < itemSize; i++)
		{
			if (!m_vecWidget[i]->visibleRegion().isEmpty())
			{
				myList->item(i)->setSelected(true);
				return;
			}
			else
			{
				myList->item(i)->setSelected(false);
			}
		}
	}

	signFlag = false;
}