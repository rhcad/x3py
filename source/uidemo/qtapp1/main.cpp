#include <QApplication>
#include <QLabel>

#include <portability/x3port.h>
#include <nonplugin/useplugins.h>

#include <plsimple/isimple.h>

int main(int argc, char** argv)
{
    const char* plugins[] = { "plsimple.pln", NULL };
    x3::AutoLoadPlugins autoload(plugins, "plugins");
    
    x3::Object<ISimple> p(clsidSimple);
    
    QApplication app(argc, argv);
    QLabel label(p ? "Hello World.\nThe plugin is loaded." : "plugin not loaded");
    
    label.show();
    return app.exec();
}
