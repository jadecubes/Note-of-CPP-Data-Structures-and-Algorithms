#include <vector>
#include <stack>
#include <unordered_set>
#include <unordered_map>

class Graph
{
    std::unordered_map<int, std::vector<int>> adjList;
    std::vector<int> vertices;

public:
    Graph(const std::vector<int> &values) : vertices(values)
    {
        // No need to pre-initialize adjList entries
    }

    void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
    }

    std::vector<int> topologicalSort()
    {
        std::stack<int> stack;
        std::unordered_set<int> visited;
        std::unordered_set<int> visiting;

        for (int vertex : vertices)
        {
            if (visited.count(vertex) == 0)
            {
                if (!dfs(vertex, stack, visited, visiting))
                {
                    return {};
                }
            }
        }

        std::vector<int> result;
        while (!stack.empty())
        {
            result.push_back(stack.top());
            stack.pop();
        }
        return result;
    }

private:
    bool dfs(int vertex, std::stack<int> &stack,
             std::unordered_set<int> &visited,
             std::unordered_set<int> &visiting)
    {
        visiting.insert(vertex);

        for (int neighbor : adjList[vertex])
        {
            if (visited.count(neighbor) == 0)
            {
                if (visiting.count(neighbor) > 0)
                {
                    return false;
                }
                if (!dfs(neighbor, stack, visited, visiting))
                {
                    return false;
                }
            }
        }

        visiting.erase(vertex);
        visited.insert(vertex);
        stack.push(vertex);
        return true;
    }
};