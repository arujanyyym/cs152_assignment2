
#include "queue.h"

// TODO: Implement everything from the queue class here, along with
// testqueue ... we are only providing checkinvariant

bool queue::checkinvariant( ) const
{
   if( current_size == 0 )
   {
      if( first )
      {
         std::cout << "INVARIANT: ";
         std::cout << "current_size == 0, but first != nullptr\n";
         return false;
      }

      if( last )
      {
         std::cout << "INVARIANT: ";
         std::cout << "current_size == 0, but last != nullptr\n";
         return false;
      }

      return true;
   }

   size_t s = 0;
   const qnode* l = nullptr; // This will remember the last node.

   for( const qnode* p = first; p; p = p -> next )
   {
      if( s == current_size )
      {
         std::cout << "INVARIANT: ";
         std::cout << "current_size is less than real size: ";
         std::cout << current_size << "\n\n";
         // I don't want to count further because list may be corrupt.
         return false;
      }
      ++ s;
      l = p;
   }

   if( s != current_size )
   {
      std::cout << "INVARIANT ";
      std::cout << "current_size is not equal to real size\n";
      std::cout << "current_size = " << current_size << "\n";
      std::cout << "real size    = " << s << "\n";

      return false;
   }

   if( l != last )
   {
      std::cout << "INVARIANT: last is not correct, ";
      std::cout << "it is " << last << " but must be " << l << "\n";
      return false;
   }

   return true;
}

queue::queue( ):
  current_size(0),
  first(nullptr),
  last(nullptr)
  {

  }

queue::queue( const queue& q ):
  current_size(0),
  first(nullptr),
  last(nullptr)
{
  qnode* ptr=q.first;
  for(size_t i=0; i<q.size(); ++i){
    push(ptr->val);
    ptr=ptr->next;
  }
}

const queue& queue::operator = ( const queue& q )
{
  if(&q!=this){
    clear();
    qnode* ptr=q.first;
    for(size_t i=0; i<q.size(); ++i){
      push(ptr->val);
      ptr=ptr->next;
    }
  }
  return *this;
}

queue::~queue( ){
  clear();
}

queue::queue( std::initializer_list<double> init ):
  current_size(0),
  first(nullptr),
  last(nullptr)
{
  for(double d : init) {
    push(d);
  }
}
   // So that you can write q = { 1,2,3 };
   // You can use init. size( ) to see the size, and
   // for( double d : init ) to go through all
   // elements in the initializer_list.

void queue::push( double d ){

  if(current_size==0){
    first=new qnode(d);
    last=first;

  } else {
    qnode* newNode=new qnode(d);
    last->next=newNode;
    last=newNode;
  }
    ++current_size;
}

void queue::pop( )
{
  if(current_size==0){
    throw std::runtime_error("stack is empty");
  }else{
    qnode* ptr=first->next;
    delete first;
    if(current_size==1){
      first=nullptr;
      last=nullptr;
    }else{
      first=ptr;
    }
    --current_size;
  }

}
void queue::clear( )
{
  size_t size=current_size;
  for(size_t i=0; i<size; ++i){
    pop();
  }
}

double queue::peek( ) const
{
  if(current_size==0){
    throw std::runtime_error("peek: queue is empty");
  }
    return first->val;


}


void queue::print( std::ostream& out) const
{
  out << "{";
  qnode* ptr=first;
  for(size_t i=0; i<current_size; ++i){
      out << ptr->val;
      if(i!=current_size-1){
        out << ", ";
      }
      ptr=ptr->next;

  }
  out << "}";
}


void testqueue( )
{
 queue q1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
 queue q2;

 for(size_t i=0; i<10; ++i){
   q2.push(i+5);
 }
 queue q3=q2;
 for(size_t i=0; i<5; ++i){
   q3.pop();
 }
 q1=q1;
 q1.checkinvariant();
 q2.checkinvariant();
 q3.checkinvariant();
 std::cout<<"q1:"<<q1<<"\n";
 std::cout<<"q2:"<<q2<<"\n";
 std::cout<<"q3:"<<q3<<"\n";
 q1=q3;
 q1.checkinvariant();
 std::cout<<"q1:"<<q1<<"\n";
}
