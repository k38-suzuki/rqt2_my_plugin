/**
    @author Kenta Suzuki
*/

#ifndef RQT2_MYPKG__MY_PLUGIN_HPP_
#define RQT2_MYPKG__MY_PLUGIN_HPP_

#include <rqt_gui_cpp/plugin.h>

#include "rqt2_mypkg/my_widget.hpp"
#include "rqt2_mypkg/visibility_control.h"

namespace rqt2_mypkg
{

class MyPlugin
    : public rqt_gui_cpp::Plugin
{
    Q_OBJECT
public:
    MyPlugin();
    virtual void initPlugin(qt_gui_cpp::PluginContext& context) override;
    virtual void shutdownPlugin() override;
    virtual void saveSettings(qt_gui_cpp::Settings& plugin_settings, qt_gui_cpp::Settings& instance_settings) const override;
    virtual void restoreSettings(const qt_gui_cpp::Settings& plugin_settings, const qt_gui_cpp::Settings& instance_settings) override;

    // Comment in to signal that the plugin has a way to configure it
    //virtual bool hasConfiguration() const override;
    //virtual void triggerConfiguration() override;
private:
    virtual ~MyPlugin();
    MyWidget* widget_;
};

}  // namespace rqt2_mypkg

#endif  // RQT2_MYPKG__MY_PLUGIN_HPP_
