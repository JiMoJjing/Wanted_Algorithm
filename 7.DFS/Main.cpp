#include <iostream>
#include <stack>
#include <vector>

// �̷� Ž���� ��� �� ��ǥ ����ü.
struct Location2D
{
	Location2D(int row = 0, int col = 0)
		: row(row), col(col)
	{

	}

	// ��.
	int row;

	// ��.
	int col;
};

// �� �迭.
int mapSize = 0;
std::vector<std::vector<char>> map;

// �̵� ���� ���� �Ǵ� �Լ�.
bool IsValidLocation(int row, int col)
{
	if (row >= mapSize || col >= mapSize || row < 0 || col < 0)
	{
		return false;
	}

	return map[row][col] == '0' || map[row][col] == 'x';
}

// ���� ���� �˻� �Լ�.
void FindStartLocation(int& row, int& col)
{ 
	for (int ix = 0; ix < mapSize; ++ix)
	{
		for (int jx = 0; jx < mapSize; ++jx)
		{
			if (map[ix][jx] == 'e')
			{
				row = ix;
				col = jx;
				return;
			}
		}
	}
}

bool ParseMap(const char* path)
{
	// ���� ����.
	FILE* file = nullptr;
	fopen_s(&file, path, "r");

	// ���� ���� ���� Ȯ��.
	if (file == nullptr)
	{
		std::cout << "���� �б� ����.\n";
		return false;
	}

	char buffer[256] = { };
	char* context = nullptr;

	// ù �� �б�.
	if (!fgets(buffer, 256, file))
	{
		fclose(file);
		return false;
	}

	// �� ������ ����.
	sscanf_s(buffer, "size %d", &mapSize);

	std::vector<char> line;
	line.reserve(mapSize);

	while (fgets(buffer, 256, file))
	{
		char* context = nullptr;
		char* splitString = strtok_s(buffer, ",", &context);

		if (splitString)
		{
			line.emplace_back(splitString[0]);
		}

		while (context)
		{
			splitString = strtok_s(nullptr, ",", &context);
			if (!splitString)
			{
				break;
			}
			line.emplace_back(splitString[0]);
		}
		map.emplace_back(line);
		line.clear();
	}

	fclose(file);

	return true;
}

// �̷� Ż�� �Լ�.
void EscapeMaze()
{
	for (int ix = 0; ix < mapSize; ++ix)
	{
		for (int jx = 0; jx < mapSize; ++jx)
		{
			std::cout << map[ix][jx] << " ";
		}
		std::cout << "\n";
	}

	// ��ġ ������ ���� ����.
	int row = 0, col = 0;

	// Ž�� ������ ���� ���� ��ġ ã��.
	FindStartLocation(row, col);

	// DFS�� ���� ���� ����.
	std::stack<Location2D> stack;

	// ó�� ���� ��ġ�� ���ÿ� ����.
	stack.push(Location2D(row, col));

	// �̷� Ž��.
	while (!stack.empty())
	{
		// ���� ��ġ ��ȯ.
		Location2D current = stack.top();
		stack.pop();

		// Ž�� ��ġ ���.
		std::cout << "(" << current.row << "," << current.col << ")\n";

		// Ż�� ���� Ȯ��.
		if (map[current.row][current.col] == 'x')
		{
			std::cout << " \n �̷� Ž�� ���� \n";
			return;
		}

		// �湮�� ���� ��ġ�� ��湮 ������ ���� ǥ��.
		map[current.row][current.col] = '.';

		if (IsValidLocation(current.row - 1, current.col))
		{
			stack.push(Location2D(current.row - 1, current.col));
		}
		if (IsValidLocation(current.row + 1, current.col))
		{
			stack.push(Location2D(current.row + 1, current.col));
		}
		if (IsValidLocation(current.row, current.col + 1))
		{
			stack.push(Location2D(current.row, current.col + 1));
		}
		if (IsValidLocation(current.row, current.col - 1))
		{
			stack.push(Location2D(current.row, current.col - 1));
		}
	}

	std::cout << "\n �̷� Ž�� ���� \n";
}

// Depth First Search
int main()
{
	if (ParseMap("../Assets/Map.txt"))
	{
		EscapeMaze();
	}

	std::cin.get();
}