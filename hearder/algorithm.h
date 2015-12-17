#ifndef ALGORITHM_H
#define ALGORITHM_H

template<class BidirectionalIterator1, class BidirectionalIterator2>
  BidirectionalIterator2 copy_backward( BidirectionalIterator1 first,
                                         BidirectionalIterator1 last,
                                         BidirectionalIterator2 result)
{
  while (last!=first) *(--result) = *(--last);
  return result;
}


template<class InputIterator, class OutputIterator>
OutputIterator copy (InputIterator first, InputIterator last, OutputIterator result)
{
  while (first!=last) {
    *result = *first;
    ++result; ++first;
  }
  return result;
}

#endif