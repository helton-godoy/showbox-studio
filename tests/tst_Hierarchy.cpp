#include <QtTest>
#include <QTreeWidget>
#include <QWidget>
#include "gui/ObjectInspector.h"
#include "core/StudioController.h"

class tst_Hierarchy : public QObject
{
    Q_OBJECT

private slots:
    void testReparentingLogic();
};

void tst_Hierarchy::testReparentingLogic()
{
    ObjectInspector inspector;
    QWidget root;
    QWidget parent1(&root); parent1.setObjectName("parent1");
    QWidget parent2(&root); parent2.setObjectName("parent2");
    QWidget child(&parent1); child.setObjectName("child");

    inspector.updateHierarchy(&root);

    // Simular que o usuário moveu 'child' para 'parent2' na árvore
    // Nota: Como não vamos rodar um loop de GUI completo com Drag real, 
    // vamos testar se a lógica que o dropEvent executará funciona.
    
    // O teste aqui deve validar se o widget real mudou de pai no Qt
    // quando a árvore for manipulada (será implementado no dropEvent).
    
    // Por enquanto, apenas validar se a árvore inicial está correta
    QCOMPARE(child.parentWidget(), &parent1);
}

QTEST_MAIN(tst_Hierarchy)
#include "tst_Hierarchy.moc"
