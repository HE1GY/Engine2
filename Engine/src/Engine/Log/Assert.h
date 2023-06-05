#pragma once


//deprecated
//TODO multiplatform and multiplatform config
/*
//#define ASSERT(a)                                                                                                      \
    if (!a)                                                                                                            \
    {                                                                                                                  \
        CORE_ERROR_LOG("ASSERT FAILED FILE:{0}, LINE:{1}", __FILE__, __LINE__);                                        \
        __debugbreak();                                                                                                \
    }
*/


/**
 * TO turn off define NDEBUG
 */

#define ASSERT(a) \
    if (!a)                                                                                                            \
        {                                                                                                                  \
        CORE_ERROR_LOG("ASSERT FAILED FILE:{0}, LINE:{1}", __FILE__, __LINE__);                                        \
        assert(false);                                                                                                \
        }

