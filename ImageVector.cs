using System;
using System.Linq;
using System.Text;

public class ImageVector
{
	private const int byteShift = byte.MaxValue / 2 + 1;
    private double[] dimensions;

	public int Dimensions
	{
		get { return dimensions.Length; }
	}

	public ImageVector(IntPtr start, int dataLength, int channels)
	{
		dimensions = Enumerable.Repeat<double>(0, channels).ToArray();

		unsafe
		{
			byte* startPtr = (byte*)start.ToPointer();
			byte* endPtr = startPtr + dataLength;

			for (byte* ptr = startPtr; ptr != endPtr; ptr += channels)
			{
				for (int i = 0; i < channels; ++i)
				{
					dimensions[i] += ptr[i] - byteShift;
				}
			}
		}

		unit(dimensions);
	}

	// returns a percentage (0..1) of how different the images are (0 == same, 1 == opposite)
	public double diff(ImageVector other)
	{
		if (dimensions.Length != other.dimensions.Length)
			throw new InvalidOperationException("ImageVectors must have the same number of dimensions");
		
		// vector subtraction
		double[] sub = new double[dimensions.Length];

		for (int i = 0; i < dimensions.Length; ++i)
		{
			sub[i] = dimensions[i] - other.dimensions[i];
		}

		// max length of subtracting two unit vectors is 2
		return magnitude(sub) / 2f;
	}

	public override string ToString()
	{
		StringBuilder sb = new StringBuilder();

		foreach(double d in dimensions)
		{
			sb.Append(d).Append(' ');
		}

		return sb.ToString();
	}

	private static double magnitude(double[] dims)
	{
		double total = 0;

		for (int i = 0; i < dims.Length; ++i)
		{
			total += dims[i] * dims[i];
		}

		return Math.Sqrt(total);
	}

	private static void unit(double[] dims)
	{
		double length = magnitude(dims);

		for (int i = 0; i < dims.Length; ++i)
		{
			dims[i] /= length;
		}
	}
}
