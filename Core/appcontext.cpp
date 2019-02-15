#include "appcontext.h"

namespace core
{

void AppContext::addComponent(QObjectPtr obj)
{
    ComponentMapType::iterator iter = componentMap_.find(obj->metaObject()->className());
    if (iter != componentMap_.end())
        return;

    std::string objName = obj->metaObject()->className();
    const QMetaObject *baseTypeInfo = obj->metaObject()->superClass();
    if (baseTypeInfo)
        objName = baseTypeInfo->className(); //save Interface of object

    componentMap_.insert(std::make_pair(objName, obj));
}

QObjectPtr AppContext::getComponent(const std::string &compoentType)
{
    ComponentMapType::iterator iter = componentMap_.find(compoentType);
    if (iter == componentMap_.end())
        return QObjectPtr();

    return iter->second;
}

}
