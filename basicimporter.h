#ifndef BASICIMPORTER_H
#define BASICIMPORTER_H

#include "basicimporter_global.h"
#include "../FastArray/importerplugininterface.h"
#include "../FastArray/plugininterface.h"

#include <QDir>
#include <QImage>
#include <QImageReader>
#include <QPixmap>
#include <QFile>
#include <QObject>

class BASICIMPORTERSHARED_EXPORT BasicImporter : public QObject, public ImporterPluginInterface, public PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "WoT.FastArray.BasicImporterPlugin/0.1")
    Q_INTERFACES(ImporterPluginInterface PluginInterface)

public:
    BasicImporter();

    virtual bool hasFailed() const;
    virtual unsigned int getErrorCode() const;
    virtual QString getErrorDescription() const;

    virtual QString getPluginName() const;
    virtual QString getPluginType() const;
    virtual QString getPluginVersion() const;

    virtual void registerLogger(LoggerInterface *logger);

    virtual QStringList getValidFileExtensions() const;
    virtual QPixmap loadImage(const QString& path);

private:
    //bunch of private convenient functions
    void logError(const QString& msg);
    void logWarning(const QString& msg);
    void logInfo(const QString& msg);

protected:
    unsigned int ErrorCode;

    bool Error;

    QString ErrorDescription;
    QString Version;
    QString Type;
    QString Name;

    QStringList FileExtensions;

    LoggerInterface* Logger;
};

#endif // BASICIMPORTER_H
