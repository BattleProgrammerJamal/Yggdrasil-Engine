#include "Empathic.hpp"

using namespace YG;
using namespace Empathic;

unsigned int EmotionnalState::sid = 0;
unsigned int EmotionnalAction::m_sid = 0;

std::ostream& ::operator<<(std::ostream& out, const EmotionnalState& estate)
{
	out << "EmotionnalState (id=" << estate.id << "; name=" << estate.name << ")";
	return out;
}

std::ostream& ::operator<<(std::ostream& out, const EmotionnalStates& states)
{
	for (EmotionnalState state : states.states)
	{
		out << state << std::endl;
	}
	return out;
}

std::ostream& ::operator<<(std::ostream& out, const Emotion& e)
{
	EmotionnalState em = *e.getState();
	out << "Emotion: (State=" << em << "; Value=" << e.getValue() << ")";
	return out;
}