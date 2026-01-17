#ifndef STUDIOCOMMANDS_H
#define STUDIOCOMMANDS_H

#include <QUndoCommand>
#include <QWidget>
#include <QLayout>
#include "gui/Canvas.h"

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

#endif // STUDIOCOMMANDS_H
