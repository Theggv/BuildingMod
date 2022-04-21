#if !defined(_INTERFACES_IGUARD_)
#define _INTERFACES_IGUARD_

class IGuard
{
private:
public:
    virtual bool CanExecute() = 0;
};

#endif // _INTERFACES_IGUARD_
