#ifndef CONFIGMGR_H
#define CONFIGMGR_H

#include <memory>
#include <QObject>
#include <QString>
#include <QVariant>
#include <QSettings>

class QsciScintilla;

typedef std::shared_ptr<QsciScintilla> QsciScintillaPtr;

class IConfigMgr
{
public:
    virtual ~IConfigMgr(){}
    virtual QsciScintillaPtr createSciObject(QWidget* parent = nullptr) = 0;
    virtual void configSciObject(QsciScintillaPtr sciPtr) = 0;
    virtual void setProperty(const QString &key, const QVariant &value) = 0;
    virtual QVariant getProperty(const QString &key, const QVariant &defaultValue = QVariant()) const = 0;
};
typedef std::shared_ptr<IConfigMgr> ConfigMgrPtr;

class ConfigMgr : public IConfigMgr
{
    //Q_OBJECT
public:
    explicit ConfigMgr(QObject *parent = nullptr);

    virtual QsciScintillaPtr createSciObject(QWidget* parent = nullptr) override;
    virtual void configSciObject(QsciScintillaPtr sciPtr) override;
    virtual void setProperty(const QString &key, const QVariant &value) override;
    virtual QVariant getProperty(const QString &key, const QVariant &defaultValue = QVariant()) const  override;

private:
    QSettings settings_;

};

#endif // CONFIGMGR_H
