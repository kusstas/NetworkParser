#include <QCoreApplication>

#include <QNetworkAccessManager>
#include "Logger.h"

#include "PageDownloader.h"
#include "UrlSearcher.h"

#include <iostream>
#include <string>

using network_parser::network::PageDownloader;
using network_parser::searchers::UrlSearcher;
using network_parser::utility::Logger;

int
main( int argc, char* argv[] )
{
    QCoreApplication application( argc, argv );
    QNetworkAccessManager network_access_manager;

    PageDownloader page_downloader( network_access_manager );
    UrlSearcher url_searcher;

    QObject::connect(
            &page_downloader, &PageDownloader::finished, &url_searcher, &UrlSearcher::search );

    QObject::connect( &url_searcher, &UrlSearcher::finished, []( QStringList urls ) {
        for ( auto const& url : urls )
        {
            Logger::message( url );
        }
        Logger::message( "END" );
    } );

    std::string std_url;
    std::cout << "Enter url: ";
    std::cin >> std_url;

    page_downloader.download( QUrl( QString::fromStdString( std_url ) ) );

    return QCoreApplication::exec( );
}
