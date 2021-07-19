#pragma once

namespace cobalt
{
	class AReceiver
	{
		public:
			virtual ~AReceiver() = default;
	};

	template<typename Type>
	class Receiver : public AReceiver
	{
		public:
			virtual ~Receiver() override = default;
	};
}
