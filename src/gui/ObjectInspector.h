#ifndef OBJECTINSPECTOR_H
#define OBJECTINSPECTOR_H

#include <QTreeWidget>

class ObjectInspector : public QTreeWidget
{
    Q_OBJECT
public:
    explicit ObjectInspector(QWidget *parent = nullptr);

    // Atualiza a árvore baseada no widget raiz do canvas
    void updateHierarchy(QWidget *root);

    // Sincroniza a seleção quando clicado no canvas
    void selectItemForWidget(QWidget *widget);

signals:
    void itemSelected(QWidget *widget);

private slots:
    void onCurrentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

private:
    void addWidgetToTree(QWidget *widget, QTreeWidgetItem *parentItem);
    QMap<QWidget*, QTreeWidgetItem*> m_widgetToItem;
};

#endif // OBJECTINSPECTOR_H
