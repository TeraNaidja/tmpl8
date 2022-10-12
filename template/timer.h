#pragma once

namespace Tmpl8
{
	// timer
	struct Timer
	{
		Timer() { reset(); }
		//Returns elapsed time in seconds.
		[[nodiscard]] float elapsed() const;
		void reset() { start = std::chrono::high_resolution_clock::now(); }
		std::chrono::high_resolution_clock::time_point start;
	};
};