#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include <memory>
#include <QObject>

namespace core
{

typedef std::shared_ptr<QObject> QObjectPtr;

class IContext
{
public:
    virtual void addComponent(QObjectPtr obj) = 0;
    virtual QObjectPtr getComponent(const std::string& compoentType) = 0;

    template<class T>
    std::shared_ptr<T> getComponent(std::function<void(QObjectPtr)> func)
    {
        QObjectPtr object = getComponent(T::staticMetaObject.className());
        std::shared_ptr<T> targetObject = std::dynamic_pointer_cast<T>(object);
        if (func)
            func(targetObject);

        return targetObject;
    }

    template<class T>
    std::shared_ptr<T> operator[] (const std::string& component)
    {
        QObjectPtr object = getComponent(component);
        std::shared_ptr<T> targetObject = std::dynamic_pointer_cast<T>(object);
        return targetObject;
    }
};
typedef std::shared_ptr<IContext> ContextPtr;

class AppContext: public IContext
{
    typedef std::map<std::string, QObjectPtr> ComponentMapType;
public:
    AppContext() = default;
    virtual ~AppContext() = default;

    void addComponent(QObjectPtr obj);
    QObjectPtr getComponent(const std::string& compoentType);

private:
    ComponentMapType componentMap_;

};

}
#endif // APPCONTEXT_H
