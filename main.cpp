#include <QApplication>
#include <Core/appcontext.h>
#include <Core/configmgr.h>
#include <View/mainwindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("DELLEMC");
    QCoreApplication::setOrganizationDomain("FILETEAM");
    QCoreApplication::setApplicationName("AARDVARK");

    core::ConfigMgrPtr configMgrPtr = std::make_shared<core::ConfigMgr>();
    core::ContextPtr context = std::make_shared<core::AppContext>();
    context->addComponent(configMgrPtr);

    MainWindow w(context);
    w.showMaximized();

    return a.exec();
}
