#include <QCoreApplication>

#include <QNetworkAccessManager>
#include "Logger.h"

#include <Session.h>

#include <iostream>
#include <string>

using network_parser::Session;
using network_parser::utility::Logger;

int
main( int argc, char* argv[] )
{
    QCoreApplication application( argc, argv );
    QNetworkAccessManager network_access_manager;
    QSet< QUrl > history;

    Session session( network_access_manager, &history );

    std::string std_url, std_text;
    std::cout << "Enter url: ";
    std::cin >> std_url;
    std::cout << "Enter text: ";
    std::cin >> std_text;

    session.set_url( QUrl( QString::fromStdString( std_url ) ) );
    session.set_search_text( QString::fromStdString( std_text ) );

    return application.exec( );
}
