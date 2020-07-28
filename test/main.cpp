#define BOOST_TEST_MODULE ObservableVector
#include <boost/test/unit_test.hpp>

#include <pch.h>

class Observer : public IObserver
{
public:
    virtual void Update() override {  };
};

BOOST_AUTO_TEST_CASE(ObservableVectorCreate)
{
    auto vector = new ObservableVector;
    auto observer = new Observer;
    vector->Attach(observer);
    vector->y(1);

    BOOST_CHECK_EQUAL(1, 1);
}
