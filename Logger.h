#pragma once

#include <QString>

namespace network_parser
{
namespace utility
{
class Logger
{
public:
    static void error( const QString& msg );
    static void warning( const QString& msg );
    static void message( const QString& msg );
};
}  // namespace utility
}  // namespace network_parser
