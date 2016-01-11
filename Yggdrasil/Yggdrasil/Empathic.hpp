#ifndef YGGDRASIL_EMPATHIC_HPP
#define YGGDRASIL_EMPATHIC_HPP

#include <iostream>
#include <vector>
#include <string>
#include <ctime>

namespace YG
{
	namespace Empathic
	{
		static double EmotionnalBias = 0.02;

		struct EmotionnalState
		{
			public:
				unsigned int id;
				std::string name;

				EmotionnalState(std::string name)
				{
					this->name = name;
					this->id = this->sid;
					this->sid++;
				}

				friend std::ostream& operator<<(std::ostream& out, const EmotionnalState& estate);

			private:
				static unsigned int sid;
		};

		struct EmotionnalStates
		{
			std::vector<EmotionnalState> states;

			void add(EmotionnalState state)
			{
				states.push_back(state);
			}

			bool remove(unsigned int id)
			{
				bool found = false;
				std::vector<EmotionnalState>::iterator it;
				for (it = states.begin(); it != states.end(); ++it)
				{
					if ((*it).id == id)
					{
						found = true;
						break;
					}
				}
				if (found)
				{
					states.erase(it, it);
				}
				return found;
			}

			EmotionnalState* getById(unsigned int id)
			{
				EmotionnalState *state = 0;
				std::vector<EmotionnalState>::iterator it;
				for (it = states.begin(); it != states.end(); ++it)
				{
					if ((*it).id == id)
					{
						state = &*it;
						break;
					}
				}
				return state;
			}

			EmotionnalState* getByName(std::string name)
			{
				EmotionnalState *state = 0;
				std::vector<EmotionnalState>::iterator it;
				for (it = states.begin(); it != states.end(); ++it)
				{
					if ((*it).name == name)
					{
						state = &*it;
						break;
					}
				}
				return state;
			}

			EmotionnalState* operator[](std::string name)
			{
				return getByName(name);
			}

			EmotionnalState* operator[](unsigned int id)
			{
				return getById(id);
			}

			EmotionnalStates& operator<<(EmotionnalState state)
			{
				add(state);
				return *this;
			}

			EmotionnalStates& operator>>(EmotionnalState *state)
			{
				remove(state->id);
				return *this;
			}

			friend std::ostream& operator<<(std::ostream& out, const EmotionnalStates& states);
		};

		struct Emotion
		{
			public:
				Emotion(EmotionnalState *state, float value)
				{
					m_state = state;
					m_value = value;
				}

				EmotionnalState* getState() const { return m_state; }
				void setState(EmotionnalState *state) { m_state = state; }

				float getValue() const { return m_value; }
				void setValue(float value) { m_value = value; }

				friend std::ostream& operator<<(std::ostream& out, const Emotion& e);

			protected:
				EmotionnalState *m_state;
				float m_value;
		};

		struct EmotionnalAction
		{
			public:
				EmotionnalAction()
				{
					srand(time(0));
					m_id = m_sid;
					m_sid++;
					init();
				}

				virtual void init()
				{
					m_emotions.push_back(new Emotion(new EmotionnalState("JOY"), 1.0f));
					m_emotions.push_back(new Emotion(new EmotionnalState("SADNESS"), 1.0f));
					m_emotions.push_back(new Emotion(new EmotionnalState("FEAR"), 1.0f));
					m_emotions.push_back(new Emotion(new EmotionnalState("ANGER"), 1.0f));
				}

				virtual Emotion* emit()
				{
					if (!m_emotions.size()){ return 0; }

					for (unsigned int i = 0; i < m_emotions.size(); ++i)
					{
						float v = 1.0f / (float)(rand() % 10 + 1);
						m_emotions.at(i)->setValue(m_emotions.at(i)->getValue() + v * EmotionnalBias);
					}

					unsigned int index = 0;
					for (unsigned int i = 1; i < m_emotions.size(); ++i)
					{
						if (m_emotions.at(i) > m_emotions.at(i-1))
						{
							index = i;
						}
					}
					return m_emotions.at(index);
				}

				unsigned int getID() const { return m_id; }

			protected:
				static unsigned int m_sid;
				unsigned int m_id;
				std::vector<Emotion*> m_emotions;
		};

		class EmotionnalStateMachine
		{
			public:
				EmotionnalStateMachine()
				{
					m_current = 0;
				}

				Emotion* getCurrent() const 
				{
					return m_current;
				}

				std::vector<EmotionnalAction*> getActions() const
				{
					return m_actions;
				}

				void addAction(EmotionnalAction *a)
				{
					m_actions.push_back(a);
				}

				bool removeAction(unsigned int id)
				{
					bool found = false;
					std::vector<EmotionnalAction*>::iterator it;
					for (it = m_actions.begin(); it != m_actions.end(); ++it)
					{
						if ((*it)->getID() == id)
						{
							found = true;
							break;
						}
					}
					if (found)
					{
						m_actions.erase(it, it);
					}
					return found;
				}

				void update()
				{
					std::vector<Emotion*> best;
					for (EmotionnalAction *action : m_actions)
					{
						best.push_back(action->emit());
					}
					unsigned int index = 0;
					for (unsigned int i = 1; i < best.size(); ++i)
					{
						if (best.at(i) > best.at(i - 1))
						{
							index = i;
						}
					}
					m_current = best.at(index);
				}

				EmotionnalStateMachine& operator<<(EmotionnalAction *action)
				{
					addAction(action);
					return *this;
				}

				EmotionnalStateMachine& operator>>(unsigned int id)
				{
					removeAction(id);
					return *this;
				}

			protected:
				Emotion *m_current;
				std::vector<EmotionnalAction*> m_actions;
		};
	};
};

#endif