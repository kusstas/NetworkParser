#include "PageDownloader.h"
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QStringBuilder>

#include "Logger.h"

namespace network_parser
{
namespace network
{
using utility::Logger;

PageDownloader::PageDownloader( QNetworkAccessManager& network_access_manager, QObject* parent )
    : QObject( parent )
    , m_network_access_manager( network_access_manager )
{
}

bool
PageDownloader::is_download( ) const
{
    return m_is_download;
}

bool
PageDownloader::is_downloaded( ) const
{
    return m_is_downloaded;
}

QNetworkAccessManager&
PageDownloader::get_network_access_manager( ) const
{
    return m_network_access_manager;
}

void
PageDownloader::download( const QUrl& url )
{
    QNetworkRequest request;
    request.setUrl( url );
    m_reply = m_network_access_manager.get( request );
    m_is_download = true;
    m_is_downloaded = false;

    Logger::message( "Download: " + url.toString( ) );
    emit started( );
    connect( m_reply, &QNetworkReply::finished, this, &PageDownloader::on_reply );
}

void
PageDownloader::on_reply( )
{
    m_is_download = false;
    if ( m_reply->error( ) )
    {
        Logger::warning( m_reply->url( ).toString( ) % " : " % m_reply->errorString( ) );
        emit failed( m_reply->errorString( ) );
        return;
    }
    m_is_downloaded = true;

    Logger::message( "Download complete: " + m_reply->url( ).toString( ) );
    emit finished( m_reply->readAll( ) );
}

}  // namespace network
}  // namespace network_parser
