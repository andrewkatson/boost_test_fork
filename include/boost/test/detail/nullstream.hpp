//  (C) Copyright Gennadiy Rozental 2002-2003.
//  (C) Copyright Daryle Walker 2000-2001. 
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/test for the library home page.
//
//  File        : $RCSfile$
//
//  Version     : $Revision$
//
//  Description : simulate /dev/null stream
// ***************************************************************************

#ifndef BOOST_NULLSTREAM_HPP
#define BOOST_NULLSTREAM_HPP

#include <ostream>    // for std::basic_ostream
#include <streambuf>  // for std::basic_streambuf
#include <string>     // for std::char_traits

#include <boost/utility/base_from_member.hpp>

namespace boost {

// ************************************************************************** //
// **************                 basic_nullbuf                ************** //
// ************************************************************************** //
//  Class for a buffer that reads nothing and writes to nothing.
//  Idea from an Usenet post by Tom <the_wid@my-deja.com> at
//  27 Oct 2000 14:06:21 GMT on comp.lang.c++.

template<typename CharType, class CharTraits = ::std::char_traits<CharType> >
class basic_nullbuf : public ::std::basic_streambuf<CharType, CharTraits> {
    typedef ::std::basic_streambuf<CharType, CharTraits>  base_type;
public:
    // Types
    typedef typename base_type::char_type    char_type;
    typedef typename base_type::traits_type  traits_type;
    typedef typename base_type::int_type     int_type;
    typedef typename base_type::pos_type     pos_type;
    typedef typename base_type::off_type     off_type;

    // Use automatic default constructor and destructor

protected:
    // The default implementations of the miscellaneous virtual
    // member functions are sufficient.

    // The default implementations of the input & putback virtual
    // member functions, being nowhere but EOF, are sufficient.

    // The output virtual member functions need to be changed to
    // accept anything without any problems, instead of being at EOF.
    virtual  ::std::streamsize  xsputn( char_type const* /*s*/, ::std::streamsize n )   { return n; } // "s" is unused
    virtual  int_type           overflow( int_type c = traits_type::eof() )         { return traits_type::not_eof( c ); }
};

typedef basic_nullbuf<char>      nullbuf;
typedef basic_nullbuf<wchar_t>  wnullbuf;

// ************************************************************************** //
// **************               basic_onullstream              ************** //
// ************************************************************************** //
//  Output streams based on basic_nullbuf.

template< typename CharType, class CharTraits = ::std::char_traits<CharType> >
class basic_onullstream : private boost::base_from_member<basic_nullbuf<CharType, CharTraits> >
                        , public ::std::basic_ostream<CharType, CharTraits> {
    typedef boost::base_from_member<basic_nullbuf<CharType, CharTraits> >   pbase_type;
    typedef ::std::basic_ostream<CharType, CharTraits>                      base_type;
public:
    // Constructor
    basic_onullstream() : pbase_type(), base_type( &this->pbase_type::member ) {}
};

typedef basic_onullstream<char>      onullstream;
typedef basic_onullstream<wchar_t>  wonullstream;

}  // namespace boost

// ***************************************************************************
//  Revision History :
//  
//  $Log$
//  Revision 1.8  2004/05/21 06:19:35  rogeeff
//  licence update
//
//  Revision 1.7  2003/12/01 00:41:56  rogeeff
//  prerelease cleaning
//
// ***************************************************************************

#endif  // BOOST_NULLSTREAM_HPP
