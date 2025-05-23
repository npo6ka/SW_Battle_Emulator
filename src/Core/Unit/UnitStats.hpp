#pragma once

#include <any>
#include <map>
#include <stdexcept>
#include <string>
#include <typeindex>
#include <unordered_map>

namespace sw::game
{

	class UnitStats
	{
	public:
		UnitStats() = default;

		template <typename T>
		UnitStats& set(const T& value)
		{
			stats_[std::type_index(typeid(T))] = value;
			return *this;
		}

		template <typename T>
		T& get()
		{
			using BaseType = std::remove_const_t<T>;
			auto it = stats_.find(std::type_index(typeid(BaseType)));
			if (it == stats_.end())
			{
				throw std::runtime_error("Stat of type " + std::string(typeid(BaseType).name()) + " does not exist");
			}
			try
			{
				return std::any_cast<BaseType&>(it->second);
			}
			catch (const std::bad_any_cast&)
			{
				throw std::runtime_error("Invalid type cast for stat type: " + std::string(typeid(BaseType).name()));
			}
		}

		template <typename T>
		const T& get() const
		{
			using BaseType = std::remove_const_t<T>;
			auto it = stats_.find(std::type_index(typeid(BaseType)));
			if (it == stats_.end())
			{
				throw std::runtime_error("Stat of type " + std::string(typeid(BaseType).name()) + " does not exist");
			}
			try
			{
				return std::any_cast<const BaseType&>(it->second);
			}
			catch (const std::bad_any_cast&)
			{
				throw std::runtime_error("Invalid type cast for stat type: " + std::string(typeid(BaseType).name()));
			}
		}

		template <typename T>
		bool has() const
		{
			return stats_.find(std::type_index(typeid(T))) != stats_.end();
		}

	private:
		std::unordered_map<std::type_index, std::any> stats_;
	};

}
