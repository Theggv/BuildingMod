#if !defined(_INTERFACES_IRESOLVER_)
#define _INTERFACES_IRESOLVER_

#include <memory>

template <class Source, class Target>
class IResolver
{
private:
public:
    inline bool Check(std::shared_ptr<void *> &source, std::shared_ptr<void *> &target)
    {
        if (!std::dynamic_pointer_cast<int>(source) ||
            !std::dynamic_pointer_cast<int>(source))
            return false;

        return true;
    }

    virtual bool CanExecute(std::shared_ptr<Source *> source, std::shared_ptr<Target *> target) = 0;
};

#endif // _INTERFACES_IRESOLVER_
