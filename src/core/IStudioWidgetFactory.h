#ifndef ISTUDIOWIDGETFACTORY_H
#define ISTUDIOWIDGETFACTORY_H

#include <QWidget>
#include <QString>

class IStudioWidgetFactory {
public:
    virtual ~IStudioWidgetFactory() = default;
    
    virtual QWidget* createPushButton(const QString &title, const QString &name) = 0;
    virtual QWidget* createLabel(const QString &text, const QString &name) = 0;
    virtual QWidget* createChart(const QString &title, const QString &name) = 0;
    // Adicionaremos os outros 17 conforme progredirmos
};

#endif // ISTUDIOWIDGETFACTORY_H
