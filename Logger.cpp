#include "Logger.h"
#include <QDebug>

namespace network_parser
{
namespace utility
{
void
Logger::error( const QString& msg )
{
    qDebug( ).noquote( ) << "[ERROR] : " << msg;
}

void
Logger::warning( const QString& msg )
{
    qDebug( ).noquote( ) << "[WARNING] : " << msg;
}

void
Logger::message( const QString& msg )
{
    qDebug( ).noquote( ) << "[MESSAGE] : " << msg;
}
}  // namespace utility
}  // namespace network_parser
