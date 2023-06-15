#pragma once

/**
 * TO turn off define NDEBUG
 */

#define ASSERT(a)                                                               \
    if (!a) {                                                                   \
        CORE_ERROR_LOG("ASSERT FAILED FILE:{0}, LINE:{1}", __FILE__, __LINE__); \
        assert(false);                                                          \
    }
