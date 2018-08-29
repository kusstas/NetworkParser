#include "TextSearcher.h"

namespace network_parser
{
namespace searchers
{
TextSearcher::TextSearcher( QObject* parent )
    : QObject( parent )
{
}

const QString&
TextSearcher::get_search_text( ) const
{
    return m_search_text;
}

void
TextSearcher::set_search_text( const QString& search_text )
{
    m_search_text = search_text;
}

void
TextSearcher::search( const QString& text )
{
    emit started( );
    int result = text.count( m_search_text );
    emit finished( result );
}
}  // namespace searchers
}  // namespace network_parser
