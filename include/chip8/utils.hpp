#pragma once

#include <concepts>

// Call operation
template <typename T>
concept HasPerform = requires {
    { T::perform() };
};

template <typename T>
concept HasCallOperation = requires {
    typename T::call_t;
    requires HasPerform<typename T::call_t>;
};

// Display operation
template <typename T>
concept HasDisplayOperation = requires {
    typename T::display_t;
    { T::display_t::clear_screen() };
};

// Flow operation
template <typename T>
concept HasFlowOperation = requires {
    typename T::flow_t;
    { T::flow_t::function_return() };
};

// Invalid operation
template <typename T>
concept InvalidOperation = requires {
    typename T::invalid_t;
    { T::invalid_t::handle() };
};

template <typename T>
concept SupportsChip8Ops = requires {
    requires HasCallOperation<T>;
    requires HasDisplayOperation<T>;
    requires HasFlowOperation<T>;
    requires InvalidOperation<T>;


    //  TODO
    // typename T::assign_t;
    // typename T::bcd_t;
    // typename T::bitwise_t;
    // typename T::conditional_t;
    // typename T::flow_t;
    // typename T::math_t;
    // typename T::mem_t;
    // typename T::rand_t;
    // typename T::timer_t;
};
