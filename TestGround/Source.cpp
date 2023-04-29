#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::ostream;
using std::string;
using std::getline;
using std::array;
using std::vector;

template<typename T, size_t N>
struct Vector
{
	T vars[N];

	Vector(std::initializer_list<T> items)
	{
		std::copy(items.begin(), items.end(), vars);
	}

	Vector(T value)
	{
		std::fill_n(vars, N, value);
	}

	Vector()
		:vars{ 0 }
	{}

	static int size()
	{
		return N;
	}

	static int T_size()
	{
		return sizeof(T);
	}

	friend ostream& operator<<(ostream& os, const Vector<T, N>& vec)
	{
		os << "vec" << N << "(" << vars[0];
		for (size_t i = 1; i < N; i++)
		{
			os << ", " << vars[i];
		}

		os << ")";
		return os;
	}
};

using vec2 = Vector<float, 2>;
using ivec2 = Vector<int, 2>;
using uvec2 = Vector<unsigned int, 2>;

using vec3 = Vector<float, 3>;
using ivec3 = Vector<int, 3>;
using uvec3 = Vector<unsigned int, 3>;

using vec4 = Vector<float, 4>;
using ivec4 = Vector<int, 4>;
using uvec4 = Vector<unsigned int, 4>;


template<typename T>
struct Vertex
{
	static vector<int> indices;
	vector<T> elements;

	template<size_t N, typename ... Args>
	Vertex(Vector<T, N> elements, Args&&... args)
	{
		indices.resize(0);
		indices.push_back(0);
		initialize(elements, args...);
	}

	Vertex() {}

	void initialize() {}

	template<size_t N, typename ... Args>
	void initialize(Vector<T, N> elements, Args&&... args)
	{
		this->elements.insert(this->elements.end(), elements.vars, elements.vars + N);
		Vertex<T>::indices.push_back(Vertex<T>::indices.back() + N);
		initialize(args...);
	}
};

template<typename T>
vector<int> Vertex<T>::indices = { 0 };

using vertex = Vertex<float>;

int main()
{
	vector<vertex> vertices = {
		vertex(vec3({ 1.0f,  1.0f, 0.0f})),  // top right
		vertex(vec3({ 1.0f, -1.0f, 0.0f})),  // bottom right
		vertex(vec3({-1.0f, -1.0f, 0.0f})),  // bottom left
		vertex(vec3({-1.0f,  1.0f, 0.0f}))   // top left
	};

	for (size_t i = 0; i < Vertex<int>::indices.size(); i++)
	{
		cout << Vertex<int>::indices[i] << " ";
	}

	return 0;
}