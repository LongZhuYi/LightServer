#pragma once

namespace LightServer
{
	class NonCopyAble
	{
	private:
		NonCopyAble(const NonCopyAble&) = delete;
		NonCopyAble& operator = (const NonCopyAble&) = delete;
	protected:
		NonCopyAble() = default;
		~NonCopyAble() = default;
	};
}