#pragma once

#include <QObject>
#include <QUrl>
#include <QSet>

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
    void finished( QSet< QUrl > urls );

public slots:
    void search( const QString& text );
};
}  // namespace searchers
}  // namespace network_parser
