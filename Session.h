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
                      QSet< QUrl >& history,
                      QObject* parent = nullptr );
    QUrl get_url( ) const;
    void set_url( QUrl url );

signals:
    void started( );
    void finished( int result, QSet<QUrl> urls );

public slots:
    void start( QString text );

private slots:
    void on_failed_download( );
    void on_text_searcher_finished( int count );
    void on_url_searcher_finished ( QSet< QString > result );

private:
    QSet< QUrl >& m_history;
    QUrl m_url;
    int m_result;

    network::PageDownloader m_page_downloader;
    searchers::TextSearcher m_text_searcher;
    searchers::UrlSearcher m_url_searcher;
};

}  // namespace network_parser
