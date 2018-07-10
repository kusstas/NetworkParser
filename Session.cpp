#include "Logger.h"
#include "Session.h"

namespace network_parser
{
using network::PageDownloader;
using searchers::UrlSearcher;
using searchers::TextSearcher;
using utility::Logger;

Session::Session( QNetworkAccessManager& network_access_manager,
                  QSet< QUrl >& history,
                  QObject* parent )
    : QObject ( parent )
    , m_history ( history )
    , m_page_downloader( network_access_manager )
    , m_text_searcher ( )
{
    connect( &m_page_downloader, &PageDownloader::finished,
             &m_text_searcher, &TextSearcher::search );
    connect( &m_page_downloader, &PageDownloader::finished,
             &m_url_searcher, &UrlSearcher::search );

    connect( &m_page_downloader, &PageDownloader::failed,
             this, &Session::on_failed_download );
    connect( &m_text_searcher, &TextSearcher::finished,
             this, &Session::on_text_searcher_finished );
    connect( &m_url_searcher, &UrlSearcher::finished,
             this, &Session::on_url_searcher_finished );
}

QUrl
Session::get_url( ) const
{
    return m_url;
}

void
Session::set_url( QUrl url )
{
    m_url = url;
}

void
Session::start( QString text )
{
    m_text_searcher.set_text( text );
    m_page_downloader.download( m_url );
}

void
Session::on_failed_download( )
{
    emit finished( 0 );
}

void
Session::on_text_searcher_finished( int count )
{
    m_result = count;
    Logger::message( m_url.toString( ) + " - count matches: " + QString::number( count ) );
}

void
Session::on_url_searcher_finished( QSet< QString > result )
{
    for ( const auto& url_string : result )
    {
        QUrl url( url_string );
        if ( m_history.find( url ) == m_history.end() )
        {
            m_history << url;

        }
    }
    emit finished( m_result );
}

}  // namespace network_parser
