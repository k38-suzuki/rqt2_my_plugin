/**
    @author Kenta Suzuki
*/

#include "rqt2_mypkg/my_plugin.hpp"

#include <QStringList>

namespace rqt2_mypkg
{

MyPlugin::MyPlugin()
    : rqt_gui_cpp::Plugin()
    , widget_(0)
{
    // Constructor is called first before initPlugin function, needless to say.

    // give QObjects reasonable names
    setObjectName("MyPlugin");
}

MyPlugin::~MyPlugin()
{
}

void MyPlugin::initPlugin(qt_gui_cpp::PluginContext& context)
{
    // access standalone command line arguments
    QStringList argv = context.argv();
    // create QWidget
    widget_ = new MyWidget;
    if(context.serialNumber() > 1) {
        widget_->setWindowTitle(widget_->windowTitle() + " (" + QString::number(context.serialNumber()) + ")");
    }
    // extend the widget with all attributes and children from UI file

    // add widget to the user interface
    context.addWidget(widget_);
}

void MyPlugin::shutdownPlugin()
{
    // TODO unregister all publishers here
}

void MyPlugin::saveSettings(qt_gui_cpp::Settings& plugin_settings, qt_gui_cpp::Settings& instance_settings) const
{
    // TODO save intrinsic configuration, usually using:
    // instance_settings.setValue(k, v)
    (void) plugin_settings;
    (void) instance_settings;
}

void MyPlugin::restoreSettings(const qt_gui_cpp::Settings& plugin_settings, const qt_gui_cpp::Settings& instance_settings)
{
    // TODO restore intrinsic configuration, usually using:
    // v = instance_settings.value(k)
    (void) plugin_settings;
    (void) instance_settings;
}

/*bool MyPlugin::hasConfiguration() const
{
    return true;
}

void MyPlugin::triggerConfiguration()
{
    // Usually used to open a dialog to offer the user a set of configuration
}*/

}  // namespace rqt2_mypkg

#include <pluginlib/class_list_macros.hpp>

PLUGINLIB_EXPORT_CLASS(rqt2_mypkg::MyPlugin, rqt_gui_cpp::Plugin)
