#include "Canvas.h"
#include "../core/IStudioWidgetFactory.h"
#include "../core/StudioCommands.h"
#include "../core/StudioController.h"
#include <QDebug>
#include <QListWidget>
#include <QMenu>
#include <QMimeData>
#include <QStyle>
#include <QTreeWidget>

Canvas::Canvas(IStudioWidgetFactory *factory, QWidget *parent)
    : QWidget(parent), m_factory(factory) {
  m_layout = new QVBoxLayout(this);
  m_layout->setAlignment(Qt::AlignTop);

  // Visual do Canvas (parecido com uma janela de diálogo)
  // O seletor *[selected="true"] garante que a borda de seleção não apague as
  // cores do usuário
  setStyleSheet("Canvas { background-color: #f0f0f0; border: 1px solid #ccc; } "
                "*[selected=\"true\"] { border: 2px solid #0078d7; }");

  setAcceptDrops(true);
}

void Canvas::mousePressEvent(QMouseEvent *event) {
  // Clicar no fundo do canvas limpa a seleção
  if (m_controller) {
    m_controller->selectWidget(nullptr);
  }
  QWidget::mousePressEvent(event);
}

void Canvas::contextMenuEvent(QContextMenuEvent *event) {
  if (!m_controller)
    return;

  QMenu menu(this);
  auto selected = m_controller->selectedWidgets();

  if (!selected.isEmpty()) {
    QAction *groupFrame = menu.addAction("Group in Frame (HBox)");
    QAction *groupGroupBox = menu.addAction("Group in GroupBox (VBox)");
    menu.addSeparator();
    QAction *deleteAction = menu.addAction("Delete");

    QAction *res = menu.exec(event->globalPos());

    if (res == groupFrame) {
      emit requestGrouping("Frame");
    } else if (res == groupGroupBox) {
      emit requestGrouping("GroupBox");
    } else if (res == deleteAction) {
      // Reaproveitar lógica de delete da MainWindow (ou mover para Controller)
      // Por enquanto, sinalizamos
      emit requestDelete();
    }
  } else {
    menu.addAction("Canvas context menu (No selection)");
    menu.exec(event->globalPos());
  }
}

void Canvas::addWidget(QWidget *widget) {
  if (!widget)
    return;
  widget->setParent(this);
  m_layout->addWidget(widget);
  widget->show();
}

void Canvas::removeWidget(QWidget *widget) {
  if (!widget)
    return;
  m_layout->removeWidget(widget);
  widget->hide();
  widget->setParent(nullptr); // Desvincular para não aparecer no children() se
                              // o teste checar o pai
}

void Canvas::clear() {
  setSelectedWidget(nullptr);
  QLayoutItem *item;
  while ((item = m_layout->takeAt(0)) != nullptr) {
    if (QWidget *w = item->widget()) {
      delete w;
    }
    delete item;
  }
}

void Canvas::setSelectedWidget(QWidget *widget) {
  m_currentSelection = widget;
  // A lógica visual de seleção agora é tratada pelo StudioController
}

void Canvas::dragEnterEvent(QDragEnterEvent *event) {
  // Aceitar drag de QListWidget (Classic) ou QTreeWidget (Tree)
  if (event->mimeData()->hasText() ||
      qobject_cast<QListWidget *>(event->source()) ||
      qobject_cast<QTreeWidget *>(event->source())) {
    event->acceptProposedAction();
  }
}

void Canvas::dragMoveEvent(QDragMoveEvent *event) {
  // Highlight container quando arrasta sobre ele
  QWidget *container = findContainerAtPos(event->position().toPoint());

  // Remover highlight do container anterior se houver
  static QWidget *lastHighlighted = nullptr;
  if (lastHighlighted && lastHighlighted != container) {
    highlightContainer(lastHighlighted, false);
  }

  if (container && container != this) {
    highlightContainer(container, true);
    lastHighlighted = container;
  } else {
    lastHighlighted = nullptr;
  }

  event->acceptProposedAction();
}

void Canvas::dropEvent(QDropEvent *event) {
  QString type;
  const QMimeData *mime = event->mimeData();

  if (mime->hasText()) {
    type = mime->text();
  } else if (QListWidget *list = qobject_cast<QListWidget *>(event->source())) {
    // Modo Classic (QToolBox com QListWidget)
    QList<QListWidgetItem *> items = list->selectedItems();
    if (!items.isEmpty()) {
      type = items.first()->text();
    }
  } else if (QTreeWidget *tree = qobject_cast<QTreeWidget *>(event->source())) {
    // Modo Tree (QTreeWidget)
    QList<QTreeWidgetItem *> items = tree->selectedItems();
    if (!items.isEmpty()) {
      QTreeWidgetItem *item = items.first();
      // Apenas itens folha (sem filhos) são widgets
      if (item->childCount() == 0) {
        type = item->text(0);
      }
    }
  }

  if (type.isEmpty())
    return;

  // Gerar um nome único simples
  QString name =
      QString("%1_%2").arg(type.toLower()).arg(m_layout->count() + 1);

  QWidget *newWidget = m_factory->createWidget(type, name);

  if (newWidget) {
    // Detectar se o drop foi sobre um container que aceita filhos
    QWidget *targetContainer = findContainerAtPos(event->position().toPoint());

    if (targetContainer && targetContainer != this) {
      // Adicionar ao layout do container
      if (QLayout *containerLayout = targetContainer->layout()) {
        newWidget->setParent(targetContainer);
        containerLayout->addWidget(newWidget);
        newWidget->show();

        // Feedback visual
        highlightContainer(targetContainer, false);
      } else {
        // Container sem layout, adicionar ao canvas normalmente
        addWidget(newWidget);
      }
    } else {
      // Drop no canvas principal
      if (m_controller) {
        m_controller->undoStack()->push(new AddWidgetCommand(this, newWidget));
      } else {
        addWidget(newWidget);
      }
    }

    emit widgetAdded(newWidget);
    event->acceptProposedAction();
  }
}

QWidget *Canvas::findContainerAtPos(const QPoint &pos) {
  // Iterar pelos widgets filhos em ordem reversa (os de cima primeiro)
  QList<QWidget *> children =
      findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly);

  for (int i = children.size() - 1; i >= 0; --i) {
    QWidget *child = children[i];
    if (!child->isVisible())
      continue;

    // Verificar se o ponto está dentro do widget
    QRect childRect = child->geometry();
    if (childRect.contains(pos)) {
      // Verificar se é um container (tem layout)
      QString showboxType = child->property("showbox_type").toString();
      if (showboxType.contains("layout") || showboxType == "groupbox" ||
          showboxType == "frame" || showboxType == "scrollarea") {
        return child;
      }
    }
  }

  return nullptr;
}

void Canvas::highlightContainer(QWidget *container, bool highlight) {
  if (!container)
    return;

  if (highlight) {
    container->setProperty("drop_target", true);
    container->setStyleSheet(
        container->styleSheet() +
        " QWidget[drop_target=\"true\"] { border: 2px solid #00ff00; }");
  } else {
    container->setProperty("drop_target", false);
    // Restaurar estilo original (a propriedade será removida no próximo update)
  }
  container->style()->polish(container);
}
