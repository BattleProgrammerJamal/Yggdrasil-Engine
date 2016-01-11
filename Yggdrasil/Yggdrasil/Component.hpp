#ifndef YGGDRASIL_COMPONENT_HPP
#define YGGDRASIL_COMPONENT_HPP

#include <iostream>
#include <vector>
#include "Asset.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Actor.hpp"

namespace YG
{
	namespace Core
	{
		class Component;

		struct OnComponentInit
		{
			virtual void operator()(Component *comp)
			{
			}
		};

		struct OnComponentUpdate
		{
			virtual void operator()(Component *comp)
			{
			}
		};

		struct BaseProperty
		{
		};

		template <typename T>
		struct Property : public BaseProperty
		{
			public:
				Property<T>(std::string name, T data)
				{
					m_name = name;
					m_data = data;
				}

				std::string& getName() const { return m_name; }
				void setName(const std::string& name) { m_name = name; }

				T getData() const { return m_data; }
				void setData(const T& data) { m_data = data; }

				friend std::ostream& operator<<(std::ostream& out, const Property& prop)
				{
					out << prop.getData();
					return out;
				}

			protected:
				std::string m_name;
				T m_data;
		};

		struct IntProperty : Property<int>
		{
			public:
				IntProperty(std::string name, int value)
					: Property<int>(name, value){}
		};

		struct FloatProperty : Property<float>
		{
			public:
				FloatProperty(std::string name, float value)
					: Property<float>(name, value){}
		};

		struct DoubleProperty : Property<double>
		{
			public:
				DoubleProperty(std::string name, double value)
					: Property<double>(name, value){}
		};

		struct StringProperty : Property<std::string>
		{
			public:
				StringProperty(std::string name, std::string value)
					: Property<std::string>(name, value){}
		};

		class Component
		{
			public:
				Component(std::string name = "Component", Actor* owner = 0)
				{
					m_name = name;
					m_owner = owner;
				}

				std::string getName() const { return m_name; }

				Actor* getOwner() const { return m_owner; }

				void addInitEvent(OnComponentInit *initEvt)
				{
					m_initEvents.push_back(initEvt);
				}

				void addUpdateEvent(OnComponentUpdate *updateEvt)
				{
					m_updateEvents.push_back(updateEvt);
				}

				void addProperty(BaseProperty *prop)
				{
					m_properties.push_back(prop);
				}

			protected:
				std::string m_name;
				Actor *m_owner;
				std::vector<OnComponentInit*> m_initEvents;
				std::vector<OnComponentUpdate*> m_updateEvents;
				std::vector<BaseProperty*> m_properties;
		};
	};
};

#endif