#ifndef HIGINE_UTILS_IDABLE
#define HIGINE_UTILS_IDABLE

namespace utils{
	class idable
	{
	private:

	protected:
		unsigned int id;

	public:
		idable();
		~idable();

		unsigned get_id();
	};

	idable::idable()
	{
	}

	idable::~idable()
	{
	}

	unsigned int idable::get_id(){
		return id;
	}
}

#endif