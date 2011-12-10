/*! \file lockcount.h
*  \brief Define helper class to auto increment and decrement: x3::LockCount
 *  \author Zhang Yungui, X3 C++ PluginFramework
 *  \date   2010.5.19
 */
#ifndef X3_UTILFUNC_LOCKCOUNT_H_
#define X3_UTILFUNC_LOCKCOUNT_H_

namespace x3 {

//! Helper class to auto increment and decrement.
/*! Use this to declare local variable in functions,
    then counter will be auto decreased (--counter;) when leave from the function.
    So you can check the counter with initial value to known some status.
    \ingroup _GROUP_UTILFUNC
*/
class LockCount
{
public:
    //! Auto add counter.
    /*!
        \param p address of counter, the initial value of counter is usually zero.
    */
    LockCount(long* p) : m_count(p)
    {
        InterlockedIncrement(m_count);
    }

    //! Auto decrease counter.
    ~LockCount()
    {
        Unlock();
    }

    //! Auto decrease counter.
    void Unlock()
    {
        if (m_count)
        {
            InterlockedDecrement(m_count);
            m_count = NULL;
        }
    }

private:
    LockCount(const LockCount&);
    void operator=(const LockCount&);

    long*   m_count;
};

} // x3
#endif