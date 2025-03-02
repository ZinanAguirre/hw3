#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below

  std::vector<T> items;
  size_t dary;
  PComparator user;


};

// Add implementation of member functions here
template <typename T, typename Comparator>
Heap<T,Comparator>::Heap(int m, Comparator c) : dary(m), user(c)
{

}
template <typename T, typename Comparator>
Heap<T,Comparator>::~Heap()
{

}



// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");


  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return items[0];


}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty.");

  }
  items[0] = items.back();
  items.pop_back();
  size_t start = 0;

  // Will check if the parent has a child node
  while((dary*start+1) < items.size()) {
    T& parent = items[start];
    size_t lchild = dary*start+1;
    size_t best = dary*start+1;
    size_t current = 2;
      // For every possible child up to m, it will find highest priority within the children
      while(current <= dary){
        if(((start*dary+current) < items.size()) && (user(items[start*dary+current],items[lchild]) == true)) {
          best = start*dary+current;
          lchild = best;
          current += 1;
        }
        else{
          current += 1;
        }
      }
      if(user(parent,items[best]) == true) {
        break;
      }
    
      // The highest priority within the the children will swap with parent to follow heap property
      std::swap(items[best],parent);
      start = best;
  
  }


}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
    items.push_back(item);
    int current = items.size()-1;
    
    //Will check the parent node as it goes up heap in order to follow heap property
    while((current > 0)){
      int parent = ((current - 1) / dary);
      if(user(items[current],items[parent])==true) {
        std::swap(items[current],items[parent]);
      }
      else{
        break;
      }
      current = parent;
    }
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
  if(items.size() == 0){
    return true;
  }
  else{
    return false;
  }

}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const
{
  return items.size();

}

#endif

