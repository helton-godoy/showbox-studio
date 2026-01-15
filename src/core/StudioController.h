#ifndef STUDIOCONTROLLER_H
#define STUDIOCONTROLLER_H

#include <QObject>
#include <QWidget>
#include <QMouseEvent>

class StudioController : public QObject
{
    Q_OBJECT
public:
    explicit StudioController(QObject *parent = nullptr);

    // Adiciona um widget ao controle do editor
    void manageWidget(QWidget *widget);

signals:
    void widgetSelected(QWidget *widget);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    QWidget *m_selectedWidget = nullptr;
    void selectWidget(QWidget *widget);
};

#endif // STUDIOCONTROLLER_H
