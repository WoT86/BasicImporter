#include "basicimporter.h"


BasicImporter::BasicImporter():
    ErrorCode(0),
    Error(false),
    ErrorDescription(""),
    Version("0.1"),
    Type(IMPORTER_PLUGIN),
    Name("Basic Image Importer")
{
    foreach(QByteArray format,QImageReader::supportedImageFormats())
    {
        this->FileExtensions.append(format);
    }
}

bool BasicImporter::hasFailed() const
{
    return this->Error;
}

unsigned int BasicImporter::getErrorCode() const
{
    return this->ErrorCode;
}

QString BasicImporter::getErrorDescription() const
{
    return this->ErrorDescription;
}

QString BasicImporter::getPluginName() const
{
    return this->Name;
}

QString BasicImporter::getPluginType() const
{
    return this->Type;
}

QString BasicImporter::getPluginVersion() const
{
    return this->Version;
}

void BasicImporter::registerLogger(LoggerInterface *logger)
{
    this->Logger = logger;
    this->logInfo(QObject::tr("logger registered."));
    this->logInfo(QObject::tr("valid file extensions: %1").arg(this->getValidFileExtensions().join(",")));
}

QStringList BasicImporter::getValidFileExtensions() const
{
    return this->FileExtensions;
}

QPixmap BasicImporter::loadImage(const QString &path)
{
    QImageReader reader(path);

    if(reader.canRead())
    {
        this->logInfo(tr("loading %1; file format %2").arg(path,QImageReader::imageFormat(path).constData()));

        QImage image = reader.read();

        if(image.isNull())
        {
            this->Error = true;
            this->ErrorCode = reader.error();
            this->ErrorDescription = reader.errorString();

            this->logError(tr("unable to load image ERRORCODE %1 DESCRIPTION %2").arg(QString::number(this->ErrorCode),this->ErrorDescription));
            return QPixmap();
        }
        else
        {
            this->logInfo(tr("%1 successfully loaded").arg(path));
            return QPixmap::fromImage(image);
        }
    }
    else
    {
        this->logError(tr("%1 is not readable!").arg(path));
    }

    return QPixmap();
}

void BasicImporter::logError(const QString &msg)
{
    this->Logger->log(this->getPluginName(),msg,ERROR);
}

void BasicImporter::logWarning(const QString &msg)
{
    this->Logger->log(this->getPluginName(),msg,WARNING);
}

void BasicImporter::logInfo(const QString &msg)
{
    this->Logger->log(this->getPluginName(),msg,INFO);
}
