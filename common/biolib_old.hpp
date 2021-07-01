namespace bio
{
	constexpr auto pct(float frac) -> float { return 100 * frac; }



	class Strand : public std::string
	{

	public:
		using std::string::string;
		explicit Strand(FASTA const &record)
			: std::string(record.Sequence()) {}
	};

	auto distance(Strand const &lhs, Strand const &rhs) -> int
	{
		auto dist = 0;
		auto i = begin(rhs);

		for (char c : lhs)
		{
			if (c != *i)
				++dist;
			if (++i == end(rhs))
				break;
		}

		// TODO: Add remaining rhs?

		return dist;
	}

}
