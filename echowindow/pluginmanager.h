#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#if defined(QT_QML_LIB)
#   include <QQmlEngine>
#endif

#include <QJsonObject>
#include <QVector>
#include <QPluginLoader>
#include <echointerface.h>

class PluginManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList pluginNames READ pluginNames NOTIFY pluginNamesChanged)
    Q_PROPERTY(QString currentPluginName READ currentPluginName NOTIFY currentPluginNameChanged)
    Q_PROPERTY(QObject* currentPlugin READ currentPluginQObject NOTIFY currentPluginNameChanged)

public:
    Q_INVOKABLE bool loadPlugin(const QString& name);
    QStringList pluginNames();
    QString currentPluginName();
    QObject* currentPluginQObject() { return m_currentPluginInterface ? m_currentPluginInterface->getObject() : nullptr; }
    EchoInterface* currentPlugin() { return m_currentPluginInterface; }

#if defined(QT_QML_LIB)
    static QJSValue singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine);
#else
    static PluginManager* instance();
#endif

signals:
    void pluginNamesChanged();
    void currentPluginNameChanged(const QString& newName);

private:
    PluginManager(QObject* parent = nullptr);
    virtual ~PluginManager();
    void init();

private:
    static PluginManager* s_instance;
    QVector<QPluginLoader*> m_pluginLoaders;
    EchoInterface* m_currentPluginInterface = nullptr;
    QJsonObject m_currentPluginMetadata;
};

#endif // PLUGINMANAGER_H
