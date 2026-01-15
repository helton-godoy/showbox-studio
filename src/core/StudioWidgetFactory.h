#ifndef STUDIOWIDGETFACTORY_H
#define STUDIOWIDGETFACTORY_H

#include "WidgetFactory.h"
#include <QPushButton>
#include <QLabel>
#include "custom_chart_widget.h"

class StudioWidgetFactory : public WidgetFactory {
public:
    QWidget* createPushButton(const QString &title, const QString &name) override {
        QPushButton *btn = new QPushButton(title);
        btn->setObjectName(name);
        setupStudioWidget(btn);
        return btn;
    }

    QWidget* createLabel(const QString &text, const QString &name) override {
        QLabel *lbl = new QLabel(text);
        lbl->setObjectName(name);
        setupStudioWidget(lbl);
        return lbl;
    }

    QWidget* createChart(const QString &title, const QString &name) override {
        CustomChartWidget *chart = new CustomChartWidget();
        chart->setObjectName(name);
        // Chart já é complexo, talvez precise de tratamento especial
        setupStudioWidget(chart);
        return chart;
    }

private:
    void setupStudioWidget(QWidget *widget) {
        // Aqui instalaremos o event filter para seleção visual
        // widget->installEventFilter(m_studioController); 
        
        // Por enquanto, apenas desabilitamos a interação para teste
        widget->setAttribute(Qt::WA_TransparentForMouseEvents, false); 
    }
};

#endif // STUDIOWIDGETFACTORY_H
