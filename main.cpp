#include <iostream>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <json/json.h>


void createJson()
{
     Json::Value person;

     person[ "id" ] = boost::uuids::to_string( boost::uuids::random_generator()() );

     person[ "name" ][ "last" ] = "Петров";
     person[ "name" ][ "first" ] = "Сергей";
     person[ "name" ][ "middle" ] = "Владимирович";

     person[ "email" ].append( "petrov.sv@mail.ru" );
     person[ "email" ].append( "petrov.sergei@gmail.com" );
     person[ "email" ].append( "milashka@gaydate.ua" );

//          std::cout << "Result:\n" << person << '\n';
     Json::StreamWriterBuilder writeBuilder;
     writeBuilder[ "indentation" ] = "  ";
     const std::string document = Json::writeString( writeBuilder, person );

     std::cout << "Result:\n" << document << '\n';
}


struct Coord3D
{
     int x, y, z;
};


std::ostream& operator<<( std::ostream& os, const Coord3D& c )
{
     os << "(" << c.x << "; " << c.y << "; " << c.z << ")";
     return os;
}


void parseJson( const std::string& json )
{
     std::istringstream istr( json );

     Json::CharReaderBuilder readerBuilder;
     std::string err;
     Json::Value root;

     const bool ok = Json::parseFromStream( readerBuilder, istr, &root, &err );

     if( !ok )
          throw std::runtime_error( err );

     Coord3D c;

     if( !root[ "x" ] || !root[ "x" ].isInt() )
          throw std::runtime_error( "no \"x\" parameter set" );

     if( !root[ "y" ] || !root[ "y" ].isInt() )
          throw std::runtime_error( "no \"y\" parameter set" );

     if( !root[ "z" ] || !root[ "z" ].isInt() )
          throw std::runtime_error( "no \"z\" parameter set" );

     c.x = root[ "x" ].asInt();
     c.y = root[ "y" ].asInt();
     c.z = root[ "z" ].asInt();

     std::cout << "Coord3D: " << c << '\n';
}


int main()
{
    try
    {
          parseJson( "{ \"x\": 10, \"y\": -14, \"z\": true }" );
    }
    catch( const std::exception& e )
    {
        std::cerr << "exception: " << boost::diagnostic_information( e ) << '\n';
        return 1;
    }

    return 0;
}

