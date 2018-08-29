#pragma once

#include <QNetworkAccessManager>
#include <QObject>
#include <QSet>
#include <QUrl>

#include "PageDownloader.h"
#include "TextSearcher.h"
#include "UrlSearcher.h"

namespace network_parser
{
class Session : public QObject
{
    Q_OBJECT

public:
    explicit Session( QNetworkAccessManager& network_access_manager,
                      QSet< QUrl >* history = nullptr,
                      QObject* parent = nullptr );

    void set_url( const QUrl& url );
    const QUrl& get_url( ) const;

    void set_search_text( const QString& text );
    const QString& get_search_text( );

signals:
    void started( );
    void finished( int result );

public slots:
    void start( );

private:
    QSet< QUrl >* m_history;
    QUrl m_url;
    int m_result;

    network::PageDownloader m_page_downloader;
    searchers::TextSearcher m_text_searcher;
    searchers::UrlSearcher m_url_searcher;
};

}  // namespace network_parser
