#ifndef STUDIOCOMMANDS_H
#define STUDIOCOMMANDS_H

#include <QUndoCommand>
#include <QWidget>
#include <QLayout>
#include <QGroupBox>
#include "gui/Canvas.h"
#include "IStudioWidgetFactory.h"

class AddWidgetCommand : public QUndoCommand
{
public:
    AddWidgetCommand(Canvas *canvas, QWidget *widget, QUndoCommand *parent = nullptr)
        : QUndoCommand(parent), m_canvas(canvas), m_widget(widget)
    {
        setText("Add " + widget->objectName());
    }

    void undo() override {
        m_canvas->removeWidget(m_widget);
    }

    void redo() override {
        m_canvas->addWidget(m_widget);
    }

private:
    Canvas *m_canvas;
    QWidget *m_widget;
};

class DeleteWidgetCommand : public QUndoCommand
{
public:
    DeleteWidgetCommand(Canvas *canvas, QWidget *widget, QUndoCommand *parent = nullptr)
        : QUndoCommand(parent), m_canvas(canvas), m_widget(widget)
    {
        setText("Delete " + widget->objectName());
    }

    void undo() override {
        m_canvas->addWidget(m_widget);
    }

    void redo() override {
        m_canvas->removeWidget(m_widget);
    }

private:
    Canvas *m_canvas;
    QWidget *m_widget;
};

class PropertyChangeCommand : public QUndoCommand
{
public:
    PropertyChangeCommand(QWidget *target, const QString &propertyName, const QVariant &oldValue, const QVariant &newValue, QUndoCommand *parent = nullptr)
        : QUndoCommand(parent), m_target(target), m_propertyName(propertyName), m_oldValue(oldValue), m_newValue(newValue)
    {
        setText(QString("Change %1 of %2").arg(propertyName, target->objectName()));
    }

    void undo() override {
        m_target->setProperty(m_propertyName.toUtf8().constData(), m_oldValue);
    }

    void redo() override {
        m_target->setProperty(m_propertyName.toUtf8().constData(), m_newValue);
    }

private:
    QWidget *m_target;
    QString m_propertyName;
    QVariant m_oldValue;
    QVariant m_newValue;
};

class MoveWidgetCommand : public QUndoCommand
{
public:
    MoveWidgetCommand(QWidget *widget, QWidget *newParent, int newIndex = -1, QUndoCommand *parent = nullptr)
        : QUndoCommand(parent), m_widget(widget), m_newParent(newParent), m_newIndex(newIndex)
    {
        m_oldParent = widget->parentWidget();
        
        // Tentar obter o index antigo se estiver em um layout
        if (m_oldParent && m_oldParent->layout()) {
            m_oldIndex = m_oldParent->layout()->indexOf(widget);
        } else {
            m_oldIndex = -1;
        }

        setText(QString("Move %1 to %2").arg(widget->objectName(), newParent ? newParent->objectName() : "Root"));
    }

    void undo() override {
        applyMove(m_oldParent, m_oldIndex);
    }

    void redo() override {
        applyMove(m_newParent, m_newIndex);
    }

private:
    void applyMove(QWidget *parent, int index) {
        if (!parent || !m_widget) return;
        
        m_widget->setParent(parent);
        if (parent->layout()) {
            if (index >= 0) {
                // Se for um QBoxLayout, podemos inserir
                if (auto *box = qobject_cast<QBoxLayout*>(parent->layout())) {
                    box->insertWidget(index, m_widget);
                } else {
                    parent->layout()->addWidget(m_widget);
                }
            } else {
                parent->layout()->addWidget(m_widget);
            }
        }
        m_widget->show();
    }

    QWidget *m_widget;
    QWidget *m_oldParent;
    QWidget *m_newParent;
    int m_oldIndex;
    int m_newIndex;
};

class GroupWidgetsCommand : public QUndoCommand
{
public:
    struct WidgetInfo {
        QWidget *widget;
        QWidget *oldParent;
        int oldIndex;
    };

    GroupWidgetsCommand(Canvas *canvas, IStudioWidgetFactory *factory, const QList<QWidget*> &widgets, const QString &containerType, QUndoCommand *parent = nullptr)
        : QUndoCommand(parent), m_canvas(canvas), m_factory(factory), m_containerType(containerType)
    {
        for (QWidget *w : widgets) {
            WidgetInfo info;
            info.widget = w;
            info.oldParent = w->parentWidget();
            info.oldIndex = (info.oldParent && info.oldParent->layout()) ? info.oldParent->layout()->indexOf(w) : -1;
            m_widgetsInfo.append(info);
        }
        setText("Group in " + containerType);
    }

    void undo() override {
        for (const auto &info : m_widgetsInfo) {
            info.widget->setParent(info.oldParent);
            if (info.oldParent && info.oldParent->layout()) {
                if (auto *box = qobject_cast<QBoxLayout*>(info.oldParent->layout())) {
                    box->insertWidget(info.oldIndex, info.widget);
                } else {
                    info.oldParent->layout()->addWidget(info.widget);
                }
            }
            info.widget->show();
        }
        m_canvas->removeWidget(m_container);
    }

    void redo() override {
        if (!m_container) {
            m_container = m_factory->createWidget(m_containerType, m_containerType.toLower() + "_group");
            // Configurar layout padrão se for Frame/GroupBox
            if (m_containerType == "Frame") {
                m_container->setProperty("showbox_type", "frame");
                auto *l = new QHBoxLayout(m_container);
                l->setContentsMargins(5, 5, 5, 5);
            } else if (m_containerType == "GroupBox") {
                m_container->setProperty("showbox_type", "groupbox");
                auto *l = new QVBoxLayout(m_container);
                l->setContentsMargins(5, 15, 5, 5);
            }
        }

        m_canvas->addWidget(m_container);
        for (const auto &info : m_widgetsInfo) {
            if (m_container->layout()) {
                m_container->layout()->addWidget(info.widget);
            } else {
                info.widget->setParent(m_container);
            }
            info.widget->show();
        }
    }

private:
    Canvas *m_canvas;
    IStudioWidgetFactory *m_factory;
    QList<WidgetInfo> m_widgetsInfo;
    QString m_containerType;
    QWidget *m_container = nullptr;
};

#endif // STUDIOCOMMANDS_H
