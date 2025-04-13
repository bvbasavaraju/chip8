#pragma once

#include <concepts>

template <typename T>
concept HasPerform = requires {
    { T::perform() };
};

template <typename T>
concept HasCallOperation = requires {
    typename T::call_t;
    requires HasPerform<typename T::call_t>;
};

template <typename T>
concept SupportsChip8Ops = requires {
    requires HasCallOperation<T>;

    //  TODO
    // typename T::assign_t;
    // typename T::bcd_t;
    // typename T::bitwise_t;
    // typename T::conditional_t;
    // typename T::display_t;
    // typename T::flow_t;
    // typename T::math_t;
    // typename T::mem_t;
    // typename T::rand_t;
    // typename T::timer_t;
};
