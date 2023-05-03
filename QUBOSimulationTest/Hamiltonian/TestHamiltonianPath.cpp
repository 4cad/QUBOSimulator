#include "BaseTest.h"

#include "ModelBuilder.h"
#include "CPUBruteForceSolver.h"

class DirectedHamiltonianPathTests : public BaseTest {
public:
     
};

// This isn't directed. The only guarantee is that src < dest.
struct Edge {
    int u;
    int v;
};

struct Graph {
    std::vector<Edge> edges;
    std::map<int, std::vector<int>> edges_by_node; // No need to nitpick efficiency here. We are solving NP-Hard problems
    int node_count = 0;

    void AddEdge(int u, int v) {
        if (u > v) {
            std::swap(u, v);
        } else if (u == v) {
            throw std::exception("Graph::AddEdge - cannot add an edge with u == v.");
        }

        Edge new_edge{ u,v };

        int edge_idx = edges.size();
        edges.push_back(Edge{ u,v });
        edges_by_node[u].push_back(edge_idx);
        edges_by_node[v].push_back(edge_idx);

        node_count = std::max(std::max(node_count, u + 1), v+1);
    }
};

class DirectedHamiltonianPathSolver {
public:
    DirectedHamiltonianPathSolver(std::shared_ptr<Graph> net)
        : graph_(net)
    {}

    // Returns the array of arcs that forms a hamiltonian cycle
    std::vector<int> Solve()
    {
        ModelBuilder b;

        double z = 30;
        double y = -25;
        double x = 30;

        // c3 is a cost paid for every edge
        //Variable global_penalty_var = b.NewVar();
        //double global_penalty = c3 * graph_->edges.size();

        //  b += global_penalty_var * global_penalty;

        std::vector<Variable> active_node_var;
        std::vector<Variable> active_edge_var;
        for (short i = 0; i < graph_->node_count; i++) {


            Variable node_penalty_var = b.NewVar();
            active_node_var.push_back(node_penalty_var);
            b += node_penalty_var * x;
        }

        for (short i = 0; i < graph_->edges.size(); i++) {
            Edge edge = graph_->edges[i];

            Variable edge_var = b.NewVar();
            active_edge_var.push_back(edge_var);

            b += edge_var * active_node_var[edge.u] * y;
            b += edge_var * active_node_var[edge.v] * y;
        }

        // Now for each vertex, we want to add the quadratic coefficient that penalizes more than 1 edge being in the set.
        for (int node = 0; node < graph_->edges_by_node.size(); node++) {
            std::vector<int> edges = graph_->edges_by_node[node];
            for (int edge1 : edges) {
                for (int edge2 : edges) {
                    if (edge1 == edge2)
                        continue;

                    // Quadratic penalty for # of edges of a node in the path
                    b += active_edge_var[edge1] * active_edge_var[edge2] * z;
                }
            }
        }

        Model* model = b.Build();

        std::cout << "Solving model of " << model->variable_count << " variables" << std::endl;
        CPUBruteForceSolver cpu_solver;
        Solution solution = cpu_solver.Solve(*model);

        std::vector<int> result;
        for (short i = 0; i < graph_->edges.size(); i++) {
            Variable var = active_edge_var[i];
            if (solution[var.index]) {
                result.push_back(i);
            }
        }
        return result;
    }

private:
    std::shared_ptr<Graph> graph_;
};

using ::testing::ElementsAre;

TEST_F(DirectedHamiltonianPathTests, DISABLED_Triangle) {
    std::shared_ptr<Graph> graph(new Graph);
    graph->AddEdge(0, 1);
    graph->AddEdge(1, 2);
    graph->AddEdge(2, 0);

    DirectedHamiltonianPathSolver solver(graph);
    std::vector<int> solution = solver.Solve();

    ASSERT_THAT(solution, ElementsAre(0, 1, 2));
}

TEST_F(DirectedHamiltonianPathTests, DISABLED_ThreeVertexes_TwoArcs) {
    std::shared_ptr<Graph> graph(new Graph);
    graph->AddEdge(0, 1);
    graph->AddEdge(1, 2);

    DirectedHamiltonianPathSolver solver(graph);
    std::vector<int> solution = solver.Solve();

    ASSERT_THAT(solution, ElementsAre());
}