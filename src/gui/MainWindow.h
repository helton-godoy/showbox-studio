#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Canvas;
class IStudioWidgetFactory;
class ObjectInspector;
class StudioController;
class PropertyEditor;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupUI();
    void createSampleWidgets();

    Canvas *m_canvas;
    IStudioWidgetFactory *m_factory;
    ObjectInspector *m_inspector;
    StudioController *m_controller;
    PropertyEditor *m_propEditor;
};

#endif // MAINWINDOW_H
