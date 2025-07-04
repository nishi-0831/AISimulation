#include "State.h"

static unsigned int stateCount = 0;

State::State():id_(stateCount++)
{
	name_ = "state:" + std::to_string(id_);
}

State::State(std::string name, unsigned int id, std::function<void(void)> func)
	:name_{name},id_{id},func_{func}
{
}

State::~State()
{
}
