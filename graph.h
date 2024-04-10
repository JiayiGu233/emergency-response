// define your classes here...
#include <unordered_map>
#include <vector>
#include <limits>
#include <queue>
#include <utility> // for std::pair

struct Edge {
    int target;
    double distance;
    double speed;
    double adjustmentFactor;

    Edge(int t, double d, double s, double a = 1.0) : target(t), distance(d), speed(s), adjustmentFactor(a) {}
};


class Graph {
private:

    std::unordered_map<int, std::vector<Edge>> adjList;

public:

    Graph() {}

    void insertE(int source, int target, double distance, double speed, double adjustmentFactor );
    void load(const std::string& filename);
    bool updateA(int source, int target, double adjustmentFactor);
    void updateF(const std::string& filename) ;
    void printAdjV(int source);
    void deleteV(int source);
    std::vector<int> path(int source, int target) ;
    double lowest(int source, int target) ;
    std::pair<std::unordered_map<int, int>, std::unordered_map<int, double>> dijkstra(const Graph& graph, int source) ;
    std::vector<int> reconstructPath(int source, int target, const std::unordered_map<int, int>& predecessors) ;

//helper functions
     bool vertexExists(int vertex) const {
        return adjList.find(vertex) != adjList.end();
    }




};
