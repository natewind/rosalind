namespace bio
{
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
