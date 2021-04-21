#define BOOST_TEST_NO_LIB

#include <pch.h>
#include <boost/test/unit_test.hpp>

#include <game/Utility/IObserver.h>
#include <game/Utility/ObservableVector.h>

class Observer : public IObserver
{
public:
    Observer() : IsUpdated(false) {}
    bool IsUpdated;
    virtual void Update() override { IsUpdated = true; }
};

BOOST_AUTO_TEST_SUITE(ObservableVectorTests)

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

BOOST_AUTO_TEST_SUITE_END()
