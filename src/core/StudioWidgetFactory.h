#ifndef STUDIOWIDGETFACTORY_H
#define STUDIOWIDGETFACTORY_H

#include "IStudioWidgetFactory.h"
#include <QPushButton>
#include <QLabel>
#include <widget_factory.h> // Core Showbox UI Library

class StudioWidgetFactory : public IStudioWidgetFactory {
public:
    QWidget* createPushButton(const QString &title, const QString &name) override {
        // Agora usamos a biblioteca Core para criar o widget real
        QWidget *w = WidgetFactory::create("button");
        if (auto *btn = qobject_cast<QPushButton*>(w)) {
            btn->setText(title);
        }
        w->setObjectName(name);
        setupStudioWidget(w);
        return w;
    }

    QWidget* createLabel(const QString &text, const QString &name) override {
        // Agora usamos a biblioteca Core para criar o widget real
        QWidget *w = WidgetFactory::create("label");
        if (auto *lbl = qobject_cast<QLabel*>(w)) {
            lbl->setText(text);
        }
        w->setObjectName(name);
        setupStudioWidget(w);
        return w;
    }

    QWidget* createChart(const QString &title, const QString &name) override {
        // Por enquanto Chart ainda não está na Factory da Core, mantemos fallback ou nullptr
        QWidget *w = WidgetFactory::create("chart");
        if (!w) {
            // Fallback para implementação local enquanto não migramos Chart na Core
            return nullptr; 
        }
        w->setObjectName(name);
        setupStudioWidget(w);
        return w;
    }

private:
    void setupStudioWidget(QWidget *widget) {
        if (!widget) return;
        // Atributo para garantir que o widget aceite eventos mas possa ser "gerenciado" pelo Studio
        widget->setAttribute(Qt::WA_TransparentForMouseEvents, false); 
    }
};

#endif // STUDIOWIDGETFACTORY_H
