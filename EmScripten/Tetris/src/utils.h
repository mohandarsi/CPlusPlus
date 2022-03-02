#pragma once

#define GETTER(type, method, name) \
    /** Retrieves the name value for the object. @return The name value of the object. */ \
    inline type get##method() const { return name; }  \

#define SETTER(type, method, name) \
    /** Retrieves the name value for the object. @return The name value of the object. */ \
    inline void set##method(const type& value) { name = value; }  \
