#pragma once

#include <QNetworkAccessManager>
#include <QObject>
#include <QString>

class QNetworkReply;

namespace network_parser
{
namespace network
{
class PageDownloader : public QObject
{
    Q_OBJECT
    Q_PROPERTY( bool is_download READ is_download )
    Q_PROPERTY( bool is_downloaded READ is_downloaded )

public:
    explicit PageDownloader( QNetworkAccessManager& network_access_manager,
                             QObject* parent = nullptr );
    bool is_download( ) const;
    bool is_downloaded( ) const;
    QString readAll( ) const;
    QUrl current_url( ) const;

signals:
    void started( );
    void failed( const QString& error );
    void finished( const QString& result );

public slots:
    void download( const QUrl& url );

private slots:
    void on_reply( );

private:
    QNetworkAccessManager& m_network_access_manager;
    QNetworkReply* m_reply = nullptr;
    bool m_is_download = false;
    bool m_is_downloaded = false;
};
}  // namespace network
}  // namespace network_parser
