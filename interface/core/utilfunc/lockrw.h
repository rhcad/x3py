#ifndef X3_UTILFUNC_LOCKRW_H_
#define X3_UTILFUNC_LOCKRW_H_

namespace x3 {

class LockRW
{
public:
    struct Data {
        long    reader;
        long    writter;
        Data() : reader(0), writter(0) {}
    };

    LockRW(Data& data, bool forWrite = false) : _data(data), _type(0)
    {
        if (forWrite)
        {
            if (0 == _data.reader && 0 == _data.writter)
            {
                if (1 == InterlockedIncrement(&_data.writter))
                    _type = 2;
                else
                    InterlockedDecrement(&_data.writter);
            }
        }
        if (0 == _type)
        {
            if (0 == _data.writter)
            {
                InterlockedIncrement(&_data.reader);
                if (0 == _data.writter)
                    _type = 1;
                else
                    InterlockedDecrement(&_data.reader);
            }
        }
    }

    ~LockRW()
    {
        free();
    }

    void free()
    {
        if (1 == _type)
            InterlockedDecrement(&_data.reader);
        else if (2 == _type)
            InterlockedDecrement(&_data.writter);
        _type = 0;
    }

    bool canRead() const
    {
        return _type > 0;
    }

    bool canWrite() const
    {
        return 2 == _type;
    }

private:
    LockRW(const LockRW&);
    LockRW& operator=(const LockRW&);

    Data&   _data;
    int     _type;
};

template <typename T>
struct LockRW_ : public T {
    mutable LockRW::Data    locker;
};

} // x3
#endif