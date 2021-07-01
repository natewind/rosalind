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


	// TODO: Get rid of the exception, use a named constructor -> std::optional
	void FASTA::Read(std::istream &stream)
	{
		if (stream.peek() != '>')
			throw std::domain_error("Not FASTA format");
		stream.get();
		std::getline(stream, id);

		std::string s;
		for (char c; (c = stream.peek()) != '>' && c != EOF; sequence += s)
			std::getline(stream, s);
	}

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

	auto Strand::ContentGC() const -> float
	{
		constexpr auto is_gc = [](auto c) { return (c == 'G') || (c == 'C'); };

		auto const count = std::count_if(begin(), end(), is_gc);
		return float(count) / size();
	}

}
