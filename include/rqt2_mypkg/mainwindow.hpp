/**
   @author Kenta Suzuki
*/

#ifndef RQT2_MYPKG__MAIN_WINDOW_HPP_
#define RQT2_MYPKG__MAIN_WINDOW_HPP_

#include <QMainWindow>

namespace rqt2_mypkg
{

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);

    virtual ~MainWindow();

protected:
#ifndef QT_NO_CONTEXTMENU
    virtual void contextMenuEvent(QContextMenuEvent* event) override;
#endif

private:
    class Impl;
    Impl* impl;
};

}  // namespace rqt2_mypkg

#endif // RQT2_MYPKG__MAIN_WINDOW_HPP_
