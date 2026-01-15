#ifndef WIDGETFACTORY_H
#define WIDGETFACTORY_H

#include <QWidget>
#include <QString>

class WidgetFactory {
public:
    virtual ~WidgetFactory() = default;
    
    virtual QWidget* createPushButton(const QString &title, const QString &name) = 0;
    virtual QWidget* createLabel(const QString &text, const QString &name) = 0;
    virtual QWidget* createChart(const QString &title, const QString &name) = 0;
    // Adicionaremos os outros 17 conforme progredirmos
};

#endif // WIDGETFACTORY_H
