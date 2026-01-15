#include "ObjectInspector.h"

ObjectInspector::ObjectInspector(QWidget *parent) : QTreeWidget(parent)
{
    setHeaderLabel("Hierarquia de Objetos");
    setColumnCount(1);
    
    connect(this, &QTreeWidget::currentItemChanged, this, &ObjectInspector::onCurrentItemChanged);
}

void ObjectInspector::updateHierarchy(QWidget *root)
{
    clear();
    m_widgetToItem.clear();
    
    if (!root) return;
    
    addWidgetToTree(root, invisibleRootItem());
    expandAll();
}

void ObjectInspector::addWidgetToTree(QWidget *widget, QTreeWidgetItem *parentItem)
{
    if (!widget) return;

    QString name = widget->objectName();
    if (name.isEmpty()) name = widget->metaObject()->className();

    QTreeWidgetItem *item = new QTreeWidgetItem(parentItem);
    item->setText(0, name);
    item->setData(0, Qt::UserRole, QVariant::fromValue(widget));
    
    m_widgetToItem[widget] = item;

    for (QObject *child : widget->children()) {
        if (QWidget *w = qobject_cast<QWidget*>(child)) {
            // Ignorar widgets internos do Qt (como layouts ou barras)
            if (!w->objectName().startsWith("qt_")) {
                addWidgetToTree(w, item);
            }
        }
    }
}

void ObjectInspector::selectItemForWidget(QWidget *widget)
{
    if (m_widgetToItem.contains(widget)) {
        blockSignals(true);
        setCurrentItem(m_widgetToItem[widget]);
        blockSignals(false);
    }
}

void ObjectInspector::onCurrentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    if (current) {
        QWidget *widget = current->data(0, Qt::UserRole).value<QWidget*>();
        emit itemSelected(widget);
    }
}
