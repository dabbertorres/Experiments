#ifndef HASHING_HPP
#define HASHING_HPP

#include <cstdint>
#include <cstddef>

namespace dbr
{
	namespace hash
	{
		// "bytes" is a byte pointer to the data
		// "length" is the number of contiguous bytes pointed to by "bytes"
		std::uint32_t fletcher32(const std::uint8_t* bytes, std::size_t length)
		{
			// 0xffff is the max 16 bit number
			std::uint32_t sum0 = 0xffff;
			std::uint32_t sum1 = 0xffff;
	
			// divide by 2 because we are looking at 2 bytes at a time
			std::uint32_t bytesLeft = length / 2;
			const std::uint16_t* dataPtr = reinterpret_cast<const std::uint16_t*>(bytes);
	
			while(bytesLeft)
			{
				// limit bytes processed at a time to prevent overflow. 359 is the max number of additions,
				// but 0x100 is a nice 2^8
				std::uint32_t len = bytesLeft > 0x100 ? 0x100 : bytesLeft;
				bytesLeft -= len;
	
				do
				{
					sum1 += sum0 += *dataPtr++;
				}
				while(--len);
	
				sum0 = (sum0 & 0xffff) + (sum0 >> 0x10);
				sum1 = (sum1 & 0xffff) + (sum1 >> 0x10);
			}
	
			sum0 = (sum0 & 0xffff) + (sum0 >> 0x10);
			sum1 = (sum1 & 0xffff) + (sum1 >> 0x10);
	
			return sum1 << 0x10 | sum0;
		}
	
		// "bytes" is a byte pointer to the data
		// "length" is the number of contiguous bytes pointed to by "bytes"
		std::size_t fnv1a(const std::uint8_t* bytes, std::size_t length)
		{
			// FNV-1a hash (values for "prime" and "offset" from: http://isthe.com/chongo/tech/comp/fnv/#FNV-param)
			// (2 power of x) == 2 << (x - 1)
	
			// using architecture detection from nothings' stb libraries (www.github.com/nothings/stb)
	#if defined(__x86_64__) || defined(_M_X64)
			// 64 bit
			constexpr std::size_t prime = (2u << 39) + (2u << 7) + 0xb3u;
			constexpr std::size_t offset = 14695981039346656037u;
	#elif defined(__i386) || defined(_M_IX86)
			// 32 bit
			constexpr std::size_t prime = (2u << 23) + (2u << 7) + 0x93u;
			constexpr std::size_t offset = 2166136261u;
	#else
	#	error This FNV-1a hash is not implemented for non 32-bit or 64-bit architectures (Or, do you have weird compiler settings for some reason?)
	#endif
	
			auto* ptr = bytes;
			auto* end = ptr + length;
	
			std::size_t val = offset;
	
			for(; ptr != end; ++ptr)
			{
				val ^= *ptr;
				val *= prime;
			}
	
			return val;
		}
	
		// convenience functions
	
		template<typename T>
		std::uint32_t fletcher32(const T& data)
		{
			return fletcher32(reinterpret_cast<const std::uint8_t*>(&data), sizeof(T));
		}
	
		template<typename T>
		std::size_t fnv1a(const T& data)
		{
			return fnv1a(reinterpret_cast<const std::uint8_t*>(&data), sizeof(T));
		}
	}
}

#endif
