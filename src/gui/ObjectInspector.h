#ifndef OBJECTINSPECTOR_H
#define OBJECTINSPECTOR_H

#include <QTreeWidget>

class StudioController;

class ObjectInspector : public QTreeWidget
{
    Q_OBJECT
public:
    explicit ObjectInspector(QWidget *parent = nullptr);

    void setController(StudioController *controller) { m_controller = controller; }

    // Atualiza a árvore baseada no widget raiz do canvas
    void updateHierarchy(QWidget *root);

    // Sincroniza a seleção quando clicado no canvas
    void selectItemForWidget(QWidget *widget);

signals:
    void itemSelected(QWidget *widget);

protected:
    void dropEvent(QDropEvent *event) override;

private slots:
    void onCurrentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

private:
    void addWidgetToTree(QWidget *widget, QTreeWidgetItem *parentItem);
    QMap<QWidget*, QTreeWidgetItem*> m_widgetToItem;
    StudioController *m_controller = nullptr;
};

#endif // OBJECTINSPECTOR_H
