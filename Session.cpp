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

void
Session::start( )
{
    m_page_downloader.download( m_url );
}

}  // namespace network_parser
