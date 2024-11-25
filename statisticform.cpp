#include "statisticform.h"
#include "ui_statisticform.h"
#include "setting.h"
#include "manage.h"

Statisticform::Statisticform(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Statisticform){
    ui->setupUi(this);
    this->setWindowIcon(QIcon(setting::main_icon));
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint&~Qt::WindowMinMaxButtonsHint);

    int sum = manage::statistic();
    ui->sum_le->setText(QString::number(sum));
    ui->sum_le->setFocusPolicy(Qt::NoFocus);
    this->bar();
    this->pie();
}

Statisticform::~Statisticform(){
    delete ui;
}


void Statisticform::pie(){
    QPieSeries *pie_series = new QPieSeries;
    connect(pie_series, SIGNAL(clicked(QPieSlice*)), this, SLOT(pie_series_Clicked(QPieSlice*)));

    sta_type list_data;
    for(times_constIter iter=dress::times_constBegin();iter!=dress::times_constEnd();iter++){
        list_data[iter.key()]=iter.value();
    }

    for (times_constIter iter=list_data.constBegin();iter!=list_data.constEnd();iter++){
        if(iter.value()==0) continue;
        QPieSlice* pie_slice = new QPieSlice;
        pie_slice->setLabelVisible(true);
        pie_slice->setValue(iter.value());
        pie_slice->setLabel(iter.key());
        pie_series->append(pie_slice);
    }

    QChart* chart = new QChart;
    chart->setTitle("消费频次分布图");
    chart->setTheme(QChart::ChartThemeDark);

    QFont font = qApp->font();
    font.setBold(true);
    font.setPointSize(16);
    chart->setTitleFont(font);

    chart->addSeries(pie_series);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->legend()->setBackgroundVisible(false);

    QChartView* chartView = new QChartView;
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setChart(chart);
    ui->verticalLayout->addWidget(chartView);
}

void Statisticform::bar(){
    size_t4 max=0;
    QBarSeries *series = new QBarSeries;
    QStringList *ser_list=manage::get_all_ser();
    size_t4 size=ser_list->size();
    for(emp_constIter iter=manage::emp_constBegin();iter!=manage::emp_constEnd();iter++){
        QBarSet *set = new QBarSet(iter.value()->_name());
        sta_type* _sta_record=iter.value()->sta_record();

        QList<size_t4> data(size);
        for(size_t4 i=0;i<size;i++) data[i]=0;
        for(size_t4 i=0;i<size;i++){
            if(_sta_record->contains(ser_list->at(i))){
                data[i]+=(*_sta_record)[ser_list->at(i)];
            }
        }
        for(size_t4 i=0;i<size;i++){
            if(data[i]>max) max=data[i];
            *set<<data[i];
        }
        series->append(set);
    }

    QChart *chart = new QChart;
    chart->addSeries(series);
    chart->setTitle("营收统计");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis;
    axisX->append(*ser_list);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0, max);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    ui->chartView->setChart(chart);
}

void Statisticform::pie_series_Clicked(QPieSlice* _slice){
    _slice->setExploded(!_slice->isExploded());
    //_slice->setLabelVisible(true);
}

