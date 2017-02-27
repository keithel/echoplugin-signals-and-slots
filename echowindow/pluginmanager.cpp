#include "pluginmanager.h"
#include <QCoreApplication>
#include <QDebug>
#include <QDir>

PluginManager* PluginManager::s_instance = nullptr;

PluginManager::PluginManager(QObject* parent)
    : QObject(parent)
{
    init();
}

PluginManager::~PluginManager()
{
    for (auto loader : m_pluginLoaders)
    {
        delete loader;
    }
    m_pluginLoaders.clear();
}

void PluginManager::init()
{
    QDir pluginsDir(QCoreApplication::instance()->applicationDirPath());
#if defined(Q_OS_WIN)
    if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
        pluginsDir.cdUp();
#elif defined(Q_OS_MAC)
    if (pluginsDir.dirName() == "MacOS") {
        pluginsDir.cdUp();
        pluginsDir.cdUp();
        pluginsDir.cdUp();
    }
#endif
    pluginsDir.cd("plugins");
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        if (!QLibrary::isLibrary(fileName))
            continue;

        QPluginLoader* loader = new QPluginLoader(pluginsDir.absoluteFilePath(fileName), this);
        m_pluginLoaders.append(loader);
    }
    emit pluginNamesChanged();
}

bool PluginManager::loadPlugin(const QString &name)
{
    bool loadOk = false;

    for (auto loader : m_pluginLoaders)
    {
        QJsonObject metadata = loader->metaData();
        if (!metadata.contains("className"))
            continue;

        QString pluginName(metadata.value("className").toString());
        if (pluginName != name)
            continue;

        QObject* plugin = loader->instance();
        if (!plugin)
            continue;

        EchoInterface* interface = qobject_cast<EchoInterface *>(plugin);  // Maybe I should templatize this class to the Interface?
        if (!interface)
            continue;

        if (m_currentPlugin != nullptr) {
            delete m_currentPlugin;
            m_currentPluginMetadata = QJsonObject();
        }

        m_currentPlugin = interface;
        m_currentPluginMetadata = metadata;
        emit currentPluginNameChanged(currentPluginName());
        loadOk = true;
    }
    return loadOk;
}

QStringList PluginManager::pluginNames()
{
    QStringList names;
    for (auto loader : m_pluginLoaders)
    {
        QJsonObject md = loader->metaData();
        if (md.contains("className"))
            names.append(md.value("className").toString());
    }
    return names;
}

QString PluginManager::currentPluginName()
{
    if (m_currentPluginMetadata.contains("className"))
        return m_currentPluginMetadata.value("className").toString();
    return QString();
}

#if defined(QT_QML_LIB)
QJSValue PluginManager::singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    qDebug() << "PluginManager::singletontype_provider registered";

    if (s_instance == nullptr)
        s_instance = new PluginManager(scriptEngine);

    QJSValue jPluginManager = scriptEngine->newQObject(s_instance);
    return jPluginManager;
}
#else
PluginManager* PluginManager::instance()
{
    if (s_instance == nullptr)
        s_instance = new PluginManager();
    return s_instance;
}
#endif
