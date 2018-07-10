#include "TextSearcher.h"

namespace network_parser
{
namespace searchers
{
TextSearcher::TextSearcher( QObject* parent )
    : QObject ( parent )
{
}

const QString&
TextSearcher::get_text( ) const
{
    return m_text;
}

void
TextSearcher::set_text( const QString& text )
{
    m_text = text;
}

void
TextSearcher::search( const QString& page )
{
    emit started( );

    int result = page.count( m_text );
    emit finished( result );
}

}  // namespace searchers
}  // namespace network_parser
