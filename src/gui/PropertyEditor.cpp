#include "PropertyEditor.h"
#include <QHeaderView>
#include <QMetaProperty>
#include <QDebug>

PropertyEditor::PropertyEditor(QWidget *parent) : QTableWidget(parent)
{
    setColumnCount(2);
    setHorizontalHeaderLabels({"Propriedade", "Valor"});
    horizontalHeader()->setStretchLastSection(true);
    setAlternatingRowColors(true);
    
    connect(this, &QTableWidget::cellChanged, this, &PropertyEditor::onCellValueChanged);
}

void PropertyEditor::setTargetWidget(QWidget *widget)
{
    m_target = widget;
    m_isLoading = true;
    
    clearContents();
    setRowCount(0);

    if (!widget) {
        m_isLoading = false;
        return;
    }

    const QMetaObject *meta = widget->metaObject();
    
    // Iterar sobre todas as propriedades (incluindo herdadas)
    for (int i = 0; i < meta->propertyCount(); ++i) {
        QMetaProperty prop = meta->property(i);
        
        // Ignorar propriedades não editáveis ou internas
        if (!prop.isWritable() || !prop.isDesignable()) continue;
        
        // Vamos focar nas propriedades mais úteis por enquanto
        QString name = prop.name();
        QVariant value = prop.read(widget);
        
        addPropertyRow(name, value);
    }
    
    m_isLoading = false;
}

void PropertyEditor::addPropertyRow(const QString &name, const QVariant &value)
{
    int row = rowCount();
    insertRow(row);
    
    // Nome da Propriedade (Read-only)
    QTableWidgetItem *nameItem = new QTableWidgetItem(name);
    nameItem->setFlags(nameItem->flags() ^ Qt::ItemIsEditable);
    setItem(row, 0, nameItem);
    
    // Valor (Editável)
    QTableWidgetItem *valueItem = new QTableWidgetItem(value.toString());
    
    // Armazenar o nome da propriedade original para usar depois
    valueItem->setData(Qt::UserRole, name);
    
    setItem(row, 1, valueItem);
}

void PropertyEditor::onCellValueChanged(int row, int col)
{
    // Se estivermos carregando a tabela, ignorar (evita loops)
    if (m_isLoading || !m_target || col != 1) return;
    
    QTableWidgetItem *valueItem = item(row, 1);
    QString propName = valueItem->data(Qt::UserRole).toString();
    QString newValueStr = valueItem->text();
    
    // Aplicar o novo valor ao widget
    if (!propName.isEmpty()) {
        m_target->setProperty(propName.toUtf8().constData(), newValueStr);
    }
}
