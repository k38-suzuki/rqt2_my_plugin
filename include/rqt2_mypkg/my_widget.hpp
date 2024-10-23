/**
   @author Kenta Suzuki
*/

#ifndef RQT2_MYPKG__MY_WIDGET_HPP_
#define RQT2_MYPKG__MY_WIDGET_HPP_

#include <QWidget>

namespace rqt2_mypkg
{

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    MyWidget(QWidget* parent = nullptr);

    virtual ~MyWidget();

private:
    class Impl;
    Impl* impl;
};

}  // namespace rqt2_mypkg

#endif // RQT2_MYPKG__MY_WIDGET_HPP_
