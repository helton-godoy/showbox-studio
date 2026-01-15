#include "Canvas.h"

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    m_layout = new QVBoxLayout(this);
    m_layout->setAlignment(Qt::AlignTop);
    
    // Visual do Canvas (parecido com uma janela de diálogo)
    setStyleSheet("Canvas { background-color: #f0f0f0; border: 1px solid #ccc; }");
}

void Canvas::addWidget(QWidget *widget)
{
    m_layout->addWidget(widget);
}
