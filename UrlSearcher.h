#pragma once

#include <QObject>
#include <QStringList>

namespace network_parser
{
namespace searchers
{
class UrlSearcher : public QObject
{
    Q_OBJECT

public:
    UrlSearcher( QObject* parent = nullptr );

signals:
    void started( );
    void finished( QStringList urls );

public slots:
    void search( const QString& page );
};
}  // namespace searchers
}  // namespace network_parser
