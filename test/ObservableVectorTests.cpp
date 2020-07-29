#define BOOST_TEST_MODULE ObservableVector

#include <pch.h>
#include <boost/test/included/unit_test.hpp>

class Observer : public IObserver
{
public:
    Observer() : IsUpdated(false) {}
    bool IsUpdated;
    virtual void Update() override { IsUpdated = true; }
};

BOOST_AUTO_TEST_CASE(ObservableVectorCreate)
{
    auto vector = new ObservableVector;
    auto observer = new Observer;

    BOOST_CHECK_EQUAL(observer->IsUpdated, false);

    vector->Attach(observer);
    vector->y(1);

    BOOST_CHECK_EQUAL(observer->IsUpdated, true);

    vector->Detach(observer);

    delete observer;
    delete vector;
}

BOOST_AUTO_TEST_CASE(TransformObserverTest)
{

}
