#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QVBoxLayout>

class Canvas : public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = nullptr);
    
    void addWidget(QWidget *widget);

private:
    QVBoxLayout *m_layout;
};

#endif // CANVAS_H
