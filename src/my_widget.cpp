/**
   @author Kenta Suzuki
*/

#include "rqt2_mypkg/my_widget.hpp"
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

#include <QBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QToolButton>

#include <memory>
#include <mutex>
#include <thread>

namespace rqt2_mypkg
{

class MyWidget::Impl
{
public:
    MyWidget* self;

    Impl(MyWidget* self);
    ~Impl();

    void on_toolButton_clicked();

    QLineEdit* pubLine;
    QLineEdit* subLine;

    rclcpp::Node::SharedPtr node;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
    std::unique_ptr<rclcpp::executors::StaticSingleThreadedExecutor> executor_;
    std::mutex mutex_;
    std::mutex mutex2_;
    std::thread thread_;
};

MyWidget::MyWidget(QWidget* parent)
    : QWidget(parent)
{
    impl = new Impl(this);
}

MyWidget::Impl::Impl(MyWidget* self)
    : self(self)
    , node(std::make_shared<rclcpp::Node>("my_node"))
{
    self->setWindowTitle("MyPlugin");

    pubLine = new QLineEdit;
    pubLine->setText("Hello, world!");
    subLine = new QLineEdit;

    auto button = new QToolButton;
    button->setText("publish");
    connect(button, &QToolButton::clicked, [&](){ on_toolButton_clicked(); });

    auto formLayout = new QFormLayout;
    formLayout->addRow("pub text", pubLine);
    formLayout->addRow("sub text", subLine);

    auto layout = new QVBoxLayout;
    layout->addLayout(formLayout);
    layout->addWidget(button);
    layout->addStretch();
    self->setLayout(layout);

    publisher_ = node->create_publisher<std_msgs::msg::String>("topic", 10);
    subscription_ = node->create_subscription<std_msgs::msg::String>(
        "topic", 10, [&](const std_msgs::msg::String::SharedPtr msg){
            std::lock_guard<std::mutex> lock(mutex_);
            RCLCPP_INFO(node->get_logger(), "I heard: '%s'", msg->data.c_str());
            subLine->setText(msg->data.c_str());
        });

    executor_ = std::make_unique<rclcpp::executors::StaticSingleThreadedExecutor>();
    executor_->add_node(node);
    thread_ = std::thread([&](){ executor_->spin(); });
}

MyWidget::~MyWidget()
{
    delete impl;
}

MyWidget::Impl::~Impl()
{
    if(executor_) {
        executor_->cancel();
        thread_.join();
        executor_->remove_node(node);
        executor_.reset();
    }
}

void MyWidget::Impl::on_toolButton_clicked()
{
    std::lock_guard<std::mutex> lock(mutex2_);
    auto message = std_msgs::msg::String();
    message.data = pubLine->text().toStdString();
    RCLCPP_INFO(node->get_logger(), "Publishing: '%s'", message.data.c_str());
    publisher_->publish(message);
}

}
