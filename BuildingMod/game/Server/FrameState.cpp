#include "FrameState.h"

FrameState& FrameState::Instance()
{
	static FrameState frameState;

	return frameState;
}

AddToFullPackArgs* FrameState::GetState(bool isPost)
{
	return isPost ? m_ArgsPost : m_ArgsPre;
}

void FrameState::SetState(AddToFullPackArgs args, bool isPost)
{
	if (isPost)
		m_ArgsPost->SetArgs(args);
	else
		m_ArgsPre->SetArgs(args);
}

FrameState::FrameState()
{
	m_ArgsPre = new AddToFullPackArgs;
	m_ArgsPost = new AddToFullPackArgs;
}

FrameState::~FrameState()
{
}
