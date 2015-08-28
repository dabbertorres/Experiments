#ifndef HASHING_HPP
#define HASHING_HPP

namespace hash
{
	using uint16 = unsigned short;
	using uint32 = unsigned int;

	template<typename T>
	uint32 fletcher32(const T& data)
	{
		uint32 sum0 = 0xffff;
		uint32 sum1 = 0xffff;

		// divide by 2 because we are looking at 2 bytes at a time
		uint32 bytesLeft = sizeof(T) / 2;
		const uint16* dataPtr = reinterpret_cast<const uint16*>(&data);

		while(bytesLeft)
		{
			uint32 len = bytesLeft > 359 ? 359 : bytesLeft;
			bytesLeft -= len;

			do
			{
				sum1 += sum0 += *dataPtr++;
			}
			while(--len);

			sum0 = (sum0 & 0xffff) + (sum0 >> 16);
			sum1 = (sum1 & 0xffff) + (sum1 >> 16);
		}

		sum0 = (sum0 & 0xffff) + (sum0 >> 16);
		sum1 = (sum1 & 0xffff) + (sum1 >> 16);

		return sum1 << 16 | sum0;
	}
}

#endif
