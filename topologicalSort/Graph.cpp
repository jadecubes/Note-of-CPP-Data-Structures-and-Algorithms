#include <vector>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <queue>
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

    std::vector<int> topologicalSortDfs()
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

    std::vector<int> topologicalSortBfs()
    {
        std::vector<int> indegree(vertices.size(), 0);
        for (int u : vertices)
        {
            for (int v : adjList[u])
            {
                indegree[v]++;
            }
        }

        std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
        for (int i : vertices)
        {
            if (indegree[i] == 0)
                pq.push(i);
        }

        std::vector<int> result;
        while (!pq.empty())
        {
            int node = pq.top();
            pq.pop();
            result.push_back(node);

            for (int neighbor : adjList[node])
            {
                if (--indegree[neighbor] == 0)
                    pq.push(neighbor);
            }
        }

        return result.size() == vertices.size() ? result : (std::vector<int>{});
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