
#ifndef QUEUE_INCLUDED
#define QUEUE_INCLUDED  1

#include <iostream>
#include <initializer_list>

// Normally, one would define qnode inside queue:

struct qnode
{
   double val;
   qnode* next;    // Next in the queue.

   qnode( double val ) :
      val( val ),
      next( nullptr )
   { }
};


class queue
{
   size_t current_size;
   qnode* first;
   qnode* last;

public:
   queue( );

   queue( const queue& q );
   const queue& operator = ( const queue& q );
   ~queue( );

   queue( std::initializer_list<double> init );
      // So that you can write q = { 1,2,3 };
      // You can use init. size( ) to see the size, and
      // for( double d : init ) to go through all
      // elements in the initializer_list.

   void push( double d );

   void pop( );
   void clear( );

   double peek( ) const;

   size_t size( ) const { return current_size; }
   bool empty( ) const { return current_size == 0; }

   void print( std::ostream& ) const;

   bool checkinvariant( ) const;
      // Call this function frequently.
};

inline std::ostream& operator << (std::ostream& out, const queue& q)
{
    q.print(out);
    return out;
}


void testqueue( );
   // Write this function in queue.cpp. It must do some tests on
   // queue.

#endif
