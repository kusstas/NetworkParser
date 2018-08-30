#include "UrlSearcher.h"
#include <QRegExp>
#include <QSet>

namespace network_parser
{
namespace searchers
{
UrlSearcher::UrlSearcher( QObject* parent )
    : QObject( parent )
{
}

void
UrlSearcher::search( const QString& text )
{
    QRegExp r_expr( "(\\/\\S*)?(((https|http|ftp)://)((\\w|-)+)(([.]|[/])((\\w|-)+))+)(\\/\\S*)?" );

    emit started( );
    QSet< QUrl > result;
    int pos = 0;

    while ( ( pos = r_expr.indexIn( text, pos ) ) != -1 )
    {
        result << QUrl( r_expr.cap( 2 ) );
        pos += r_expr.matchedLength( );
    }
    emit finished( result );
}
}  // namespace searchers
}  // namespace network_parser
