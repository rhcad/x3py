// x3py framework: https://github.com/rhcad/x3py
#ifndef X3_CORE_MODULEITEM_H
#define X3_CORE_MODULEITEM_H

namespace x3 {

class ModuleItem
{
protected:
    ModuleItem() : _index(-1)
    {
    }
    virtual ~ModuleItem()
    {
    }

    void addModuleItem()
    {
        _index = InterlockedDecrement(&index());
        if (_index >= 0)
        {
            items()[_index] = this;     // only one thread can do it.
        }
    }

public:
    static void free()
    {
        if (items())
        {
            for (long i = index(); i < maxCount(); i++)
            {
                if (i >= 0 && items()[i])
                {
                    delete items()[i];
                    items()[i] = NULL;
                }
            }
            index() = 0;

            delete[] items();
            items() = NULL;
        }
    }

    static void init(int singletonClassCount)
    {
        if (!items() && singletonClassCount > 0)
        {
            maxCount() = (singletonClassCount > maxCount())
                ? singletonClassCount : maxCount();
            index() = maxCount();
            items() = new ModuleItem*[maxCount()];
        }
    }

private:
    long    _index;     // index in the single instance stack.

    static long& maxCount()
    {
        static long count = 0;
        return count;
    }
    static long& index()
    {
        static long n = 0;
        return n;
    }
    static ModuleItem**& items()
    {
        static ModuleItem** p = NULL;
        return p;
    }
};

} // x3
#endif