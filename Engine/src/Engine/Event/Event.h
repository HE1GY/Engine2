#pragma once

#include <algorithm>
#include <functional>

/**
 * Subscribe member function
 */
#define MEM_FN_TO_LMD(func)        [this](auto& arg) { func(arg); }
#define MEM_FN_NOARGS_TO_LMD(func) [this]() { func(); }


namespace Engine {
    template <typename... Args>
    class Event {
    public:
        using Callback = std::function<void(const Args&...)>;

        Event() = default;

        ~Event() = default;

        void Invoke(const Args&... payload) const {
            for (auto& cb : m_callbacks) {
                cb(payload...);
            }
        }

        void AddCallback(const Callback& cb) {
            m_callbacks.push_back(cb);
        }

        void RemoveCallback(const Callback& cb) {
            auto it = std::find_if(m_callbacks.begin(), m_callbacks.end(),
                [&](const auto& lambda) { return typeid(lambda) == typeid(cb); });
            if (it != m_callbacks.end()) {
                m_callbacks.erase(it);
            }
        }

    private:
        std::vector<Callback> m_callbacks;
    };


} // namespace Engine
