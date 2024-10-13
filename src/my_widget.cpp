/**
   @author Kenta Suzuki
*/

#include "rqt2_mypkg/my_widget.hpp"

namespace rqt2_mypkg
{

class MyWidget::Impl
{
public:
    MyWidget* self;

    Impl(MyWidget* self);
    ~Impl();
};

MyWidget::MyWidget(QWidget* parent)
    : QWidget(parent)
{
    impl = new Impl(this);
}

MyWidget::Impl::Impl(MyWidget* self)
    : self(self)
{
    self->setWindowTitle("MyPlugin");
}

MyWidget::~MyWidget()
{
    delete impl;
}

MyWidget::Impl::~Impl()
{

}

}
