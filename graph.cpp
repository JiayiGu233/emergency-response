#include "graph.h"

#include <vector>
#include <queue>
#include <limits>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

void Graph::insertE(int source, int target, double distance, double speed, double adjustmentFactor)
{
    // 检查边是否已存在
    auto &edges = adjList[source];
    for (auto &edge : edges)
    {
        if (edge.target == target)
        {
            // 更新已存在的边
            edge.distance = distance;
            edge.speed = speed;
            edge.adjustmentFactor = adjustmentFactor;
            return;
        }
    }
    // 如果边不存在，添加新边
    adjList[source].push_back(Edge(target, distance, speed, adjustmentFactor));
    // 由于是无向图，也需要添加反向边
    adjList[target].push_back(Edge(source, distance, speed, adjustmentFactor));
}

void Graph::load(const std::string &filename)
{
    std::ifstream file(filename); // 打开文件
    std::string line;

    while (std::getline(file, line))
    { // 逐行读取
        std::istringstream iss(line);
        int source, target;
        double distance, speed;
        if (!(iss >> source >> target >> distance >> speed))
        {
            continue; // 如果这行数据格式不正确，跳过这行
        }

        // 打印读取到的值，确保它们被正确读取
        // std::cout << source << " " << target << " " << distance << " " << speed << std::endl;
        // 使用解析出的值插入新的边
        insertE(source, target, distance, speed, 1);
    }

    file.close(); // 关闭文件
}

// 更新交通（调整因子）
bool Graph::updateA(int source, int target, double adjustmentFactor)
{
    // 更新从source到target的调整因子
    bool foundE = false;
    for (auto &edge : adjList[source])
    {
        if (edge.target == target)
        {
            edge.adjustmentFactor = adjustmentFactor;
            foundE = true;
            break; // 找到后即可退出循环
        }
    }
    // 由于是无向图，也需要更新从target到source的调整因子
    for (auto &edge : adjList[target])
    {
        if (edge.target == source)
        {
            edge.adjustmentFactor = adjustmentFactor;
            foundE = true;
            break; // 找到后即可退出循环
        }
    }
    return foundE;
}
void Graph::updateF(const std::string &filename)
{
    std::ifstream file(filename); // 打开文件
    std::string line;
    bool updated = false;

    while (std::getline(file, line))
    { // 逐行读取
        std::istringstream iss(line);
        int source, target;
        double adjustmentFactor;
        if (!(iss >> source >> target >> adjustmentFactor))
        {
            continue; // 如果这行数据格式不正确，跳过这行
        }
        // 使用解析出的值插入新的边
        if (updateA(source, target, adjustmentFactor))
        {
            updated = true;
        }
    }
    if (updated)
    {
        std::cout << "success" << std::endl;
    }
    else
    {
        std::cout << "failure" << std::endl;
    }

    file.close(); // 关闭文件
}
void Graph::printAdjV(int a)
{
    // Check if the vertex 'a' exists in the adjacency list
    if (adjList.find(a) != adjList.end())
    {
        for (const auto &edge : adjList[a])
        {
            std::cout << edge.target << " ";
        }
        std::cout << std::endl; // End the line after printing all adjacent vertices
    }
    else
    {
        std::cout << "failure" << std::endl;
    }
}

void Graph::deleteV(int a)
{
    // 首先检查顶点a是否存在于图中
    if (adjList.find(a) == adjList.end())
    {
        // 如果顶点a不存在，直接返回
        std::cout << "failure" << std::endl;
        return;
    }

    // 从图中删除顶点a及其所有出边
    adjList.erase(a);

    // 接下来，需要遍历图中的每个顶点
    for (auto &pair : adjList)
    {
        auto &edges = pair.second;
        // 在每个顶点的边列表中找到指向a的边并删除
        edges.erase(std::remove_if(edges.begin(), edges.end(),
                                   [a](const Edge &edge)
                                   { return edge.target == a; }),
                    edges.end());
    }
    std::cout << "success" << std::endl;
}

// 定义无穷大
const double INF = std::numeric_limits<double>::infinity();

// 定义用于Dijkstra算法的优先队列中的元素
using QueueElement = std::pair<double, int>; // <最短距离估计, 顶点ID>

// Dijkstra算法实现，返回前驱顶点映射和距离映射
std::pair<std::unordered_map<int, int>, std::unordered_map<int, double>> Graph::dijkstra(const Graph &graph, int source)
{
    std::priority_queue<QueueElement, std::vector<QueueElement>, std::greater<QueueElement>> queue;
    std::unordered_map<int, double> distances;
    std::unordered_map<int, int> predecessors;

    // 初始化所有顶点的距离为无穷大，前驱为-1
    for (const auto &pair : graph.adjList)
    {
        int vertex = pair.first;
        distances[vertex] = INF;
        predecessors[vertex] = -1;
    }
    distances[source] = 0.0;
    queue.push({0.0, source});

    while (!queue.empty())
    {
        int u = queue.top().second;
        queue.pop();

        for (const auto &edge : graph.adjList.at(u))
        {
            int v = edge.target;
            double weight = edge.distance / (edge.speed * edge.adjustmentFactor);
            if (distances[u] + weight < distances[v])
            {
                distances[v] = distances[u] + weight;
                predecessors[v] = u;
                queue.push({distances[v], v});
            }
        }
    }

    return {predecessors, distances};
}

// 根据前驱顶点映射重构从源顶点到目标顶点的最短路径
std::vector<int> Graph::reconstructPath(int source, int target, const std::unordered_map<int, int> &predecessors)
{
    std::vector<int> path;
    for (int at = target; at != -1; at = predecessors.at(at))
    {
        path.push_back(at);
    }
    if (path.back() != source)
    { // 如果路径的最后一个顶点不是源顶点，说明没有路径
        return {};
    }
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<int> Graph::path(int source, int target)
{

        auto [predecessors, distances] = dijkstra(*this, source);
        return reconstructPath(source, target, predecessors);
    
}

// 查询最短路径的权重
double Graph::lowest(int source, int target)
{
    auto [predecessors, distances] = dijkstra(*this, source);
    return distances[target] != INF ? distances[target] : -1.0; // 如果没有路径，则返回-1或其他标识值
}