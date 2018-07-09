#include "UrlSearcher.h"
#include <QRegExp>

namespace network_parser
{
namespace searchers
{
UrlSearcher::UrlSearcher( QObject* parent )
    : QObject( parent )
{
}

void
UrlSearcher::search( const QString& page )
{
    QRegExp r_expr(
            "[\\s<\"]((http[s]?|ftp):\\/)?\\/?([^:\\/\\s]+)((\\/\\w+)*\\/"
            ")([\\w\\-\\.]+[^#?\\s]+)(.*)?(#[\\w\\-]+)?[\\s>\"]" );

    emit started( );
    QStringList result;
    int pos = 0;

    while ( ( pos = r_expr.indexIn( page, pos ) ) != -1 )
    {
        result << r_expr.cap( 0 );
        pos += r_expr.matchedLength( );
    }

    emit finished( result );
}
}  // namespace searchers
}  // namespace network_parser
