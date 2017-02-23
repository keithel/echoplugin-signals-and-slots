#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#if defined(QT_QML_LIB)
#   include <QQmlEngine>
#endif

#include <QJsonObject>
#include <QVector>
#include <QPluginLoader>
#include "echointerface.h"

class PluginManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList pluginNames READ pluginNames NOTIFY pluginNamesChanged)
    Q_PROPERTY(QString currentPluginName READ currentPluginName NOTIFY currentPluginNameChanged)

public:
    Q_INVOKABLE bool loadPlugin(const QString& name);
    QStringList pluginNames();
    QString currentPluginName();
    EchoInterface* currentPlugin() { return m_currentPlugin; }

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
    EchoInterface* m_currentPlugin = nullptr;
    QJsonObject m_currentPluginMetadata;
};

#endif // PLUGINMANAGER_H
