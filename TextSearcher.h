#pragma once

#include <QObject>

namespace network_parser
{
namespace searchers
{
class TextSearcher : public QObject
{
    Q_OBJECT

public:
    explicit TextSearcher( QObject* parent = nullptr );

    const QString& get_search_text( ) const;
    void set_search_text( const QString& search_text );

signals:
    void started( );
    void finished( int count );

public slots:
    void search( const QString& text );

private:
    QString m_search_text;
};
}  // namespace searchers
}  // namespace network_parser
