#pragma once

#include <functional>

namespace Engine
{
	template<typename T>
	class Event
	{
	public:
		using Callback = std::function<bool(const T&)>;

		Event() = default;

		~Event() = default;

		void Invoke(const T& payload);

		void AddCallback(const Callback& cb);

		void RemoveCallback(const Callback& cb);

	private:
		std::vector<Callback> m_callbacks;
	};


}