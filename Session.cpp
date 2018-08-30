#include "Session.h"
#include "Logger.h"

namespace network_parser
{
using network::PageDownloader;
using searchers::TextSearcher;
using searchers::UrlSearcher;
using utility::Logger;

Session::Session( QNetworkAccessManager& network_access_manager,
                  QSet< QUrl >* history,
                  QObject* parent )
    : QObject( parent )
    , m_history( history )
    , m_page_downloader( network_access_manager )
    , m_text_searcher( )
{
    connect( &m_page_downloader, &PageDownloader::finished, &m_url_searcher, &UrlSearcher::search );
    connect( &m_page_downloader, &PageDownloader::finished, &m_text_searcher, &TextSearcher::search );
    connect( &m_page_downloader, &PageDownloader::failed, this, &Session::finished );

    connect( &m_url_searcher, &UrlSearcher::finished, this, &Session::on_url_searcher_finished );
    connect( &m_text_searcher, &TextSearcher::finished, this, &Session::on_text_searcher_finished );
}

void
Session::set_url( const QUrl& url )
{
    m_url = url;
}

const QUrl&
Session::get_url( ) const
{
    return m_url;
}

void
Session::set_search_text( const QString& search_text )
{
    m_text_searcher.set_search_text( search_text );
}

const QString&
Session::get_search_text( )
{
    return m_text_searcher.get_search_text( );
}

int
Session::get_result( ) const
{
    return m_result;
}

void
Session::start( )
{
    emit started( );
    m_page_downloader.download( m_url );
}

void
Session::on_url_searcher_finished( QSet< QUrl > urls )
{
    for ( const auto& url : urls )
    {
        if ( m_history != nullptr )
        {
            if ( m_history->contains( url ) )
            {
                continue;
            }
            else
            {
                *m_history << url;
            }
        }
        auto child_session = new Session( m_page_downloader.get_network_access_manager( ),
                                          m_history, this );
        child_session->set_url( url );
        child_session->set_search_text( get_search_text( ) );
    }

    Logger::message( QString( "Content on \"%1\" has %2 urls" ).arg( m_url.toString( ) )
                     .arg( QString::number( urls.size( ) ) ) );

    m_url_searcher_finished = true;
    check_on_finish_session( );
}

void
Session::on_text_searcher_finished( int count )
{
    m_result = count;

    Logger::message( QString( "Content on \"%1\" has %2 entries to \"%3\"" ).arg( m_url.toString( ) )
                     .arg( QString::number( count ) ).arg( get_search_text( ) ) );


    m_text_searcher_finished = true;
    check_on_finish_session( );
}

void
Session::check_on_finish_session()
{
    if ( m_url_searcher_finished && m_text_searcher_finished )
    {
        emit finished( );
    }
}

}  // namespace network_parser
