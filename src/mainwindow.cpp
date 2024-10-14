/**
   @author Kenta Suzuki
*/

#include "rqt2_mypkg/mainwindow.hpp"

#include <QAction>
#include <QBoxLayout>
#include <QContextMenuEvent>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>

#include "rqt2_mypkg/my_widget.hpp"

namespace rqt2_mypkg
{

class MainWindow::Impl
{
public:
    MainWindow* self;

    Impl(MainWindow* self);
    ~Impl();

    void newFile();
    void open();
    void save();

    void createActions();
    void createMenus();
    void createToolBars();

    QMenu* fileMenu;
    QToolBar* fileToolBar;
    QAction* newAct;
    QAction* openAct;
    QAction* saveAct;

    MyWidget* widget;
};

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    impl = new Impl(this);
}

MainWindow::Impl::Impl(MainWindow* self)
    : self(self)
{
    widget = new MyWidget;
    self->setCentralWidget(widget);

    auto layout = new QVBoxLayout;
    widget->setLayout(layout);

    createActions();
    createMenus();
    createToolBars();

    QString message = "A context menu is available by right-clicking";
    self->statusBar()->showMessage(message);

    self->setWindowTitle("MainWindow");
}

MainWindow::~MainWindow()
{
    delete impl;
}

MainWindow::Impl::~Impl()
{

}

#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent* event)
{
    QMenu menu(this);

    menu.exec(event->globalPos());
}
#endif

void MainWindow::Impl::newFile()
{

}

void MainWindow::Impl::open()
{

}

void MainWindow::Impl::save()
{

}

void MainWindow::Impl::createActions()
{
    newAct = new QAction(QIcon::fromTheme("document-new"),
                            "&New", self);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip("Create a new file");
    self->connect(newAct, &QAction::triggered, [&](){ newFile(); });

    openAct = new QAction(QIcon::fromTheme("document-open"),
                            "&Open...", self);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip("Open an existing file");
    self->connect(openAct, &QAction::triggered, [&](){ open(); });

    saveAct = new QAction(QIcon::fromTheme("document-save"),
                            "&Save", self);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip("Save the document to disk");
    self->connect(saveAct, &QAction::triggered, [&](){ save(); });
}

void MainWindow::Impl::createMenus()
{
    fileMenu = self->menuBar()->addMenu("&File");
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();
}

void MainWindow::Impl::createToolBars()
{
    fileToolBar = self->addToolBar("File");
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
    fileToolBar->addSeparator();
}

}
