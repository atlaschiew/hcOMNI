#ifndef _WN_QUEUE_H
#define _WN_QUEUE_H

#include <deque>
#include "WnLock.h"
#include "WnScopedLock.h"
#include <boost/make_shared.hpp>

template<class T> class CWnQueue : public std::deque<T>
{
public:
  CWnQueue()
	{
		m_ptr_mutex = boost::make_shared<CWnLock>();
	}
  ~CWnQueue()
	{
	}

public:
	void push(const T& t)
  {
    CWnScopedLock lock(*m_ptr_mutex);
    __super::push_back(t);
  }

	bool get(T& t)
  {
    CWnScopedLock lock(*m_ptr_mutex);
    if(!__super::empty())
    {
      t = __super::front();
      __super::pop_front(); 
      return true;
    }
    return false;
  }

	void clear()
  {
    CWnScopedLock lock(*m_ptr_mutex);
    __super::clear();
  }

protected:
	boost::shared_ptr<CWnLock> m_ptr_mutex;
};

#endif //_WN_QUEUE_H