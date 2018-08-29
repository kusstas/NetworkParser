#pragma once

#include <QObject>
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
    void finished( QSet< QString > urls );

public slots:
    void search( const QString& text );
};
}  // namespace searchers
}  // namespace network_parser
