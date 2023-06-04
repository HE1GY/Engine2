#include "Event.h"


namespace Engine
{
	template<typename T>
	void Event<T>::Invoke(const T& payload)
	{
		for (const auto& callback: m_callbacks)
		{
			bool handled = callback(payload);
			if (handled)break;
		}
	}

	template<typename T>
	void Event<T>::RemoveCallback(const Event::Callback& cb)
	{
		m_callbacks.erase(std::find(m_callbacks.begin(), m_callbacks.end(), cb));
	}

	template<typename T>
	void Event<T>::AddCallback(const Event::Callback& cb)
	{
		m_callbacks.push_back(cb);
	}
}