#include "BaseTest.h"

#include "Graph/GraphBuilder.h"


class GraphBuilderTest : public  ::testing::Test
{

};

TEST_F(GraphBuilderTest, EmptyGraph) {
    // Sets the linear coefficient of variable 0 to 0. This is needed because the model will automatically ignore variables that don't
    // have any coefficients explicitly set
    GraphBuilder b;
    std::shared_ptr<IGraph> graph(b.Build());

    EXPECT_EQ(0, graph->VertexCount());
    EXPECT_EQ(0, graph->EdgeCount());

    int manual_vertex_count = 0;
    for (Vertex v : graph->Vertices()) {
        manual_vertex_count += 1;
    }

    EXPECT_EQ(0, manual_vertex_count);

    int manual_edge_count = 0;
    for (Edge e : graph->Edges()) {
        manual_edge_count += 1;
    }

    EXPECT_EQ(0, manual_edge_count);
}

TEST_F(GraphBuilderTest, SimpleTwoVertex) {
    // Sets the linear coefficient of variable 0 to 0. This is needed because the model will automatically ignore variables that don't
    // have any coefficients explicitly set
    GraphBuilder b;

    Vertex v1 = b.AddVertex();
    Vertex v2 = b.AddVertex();
    Edge e = b.AddEdge(v1, v2);

    std::shared_ptr<IGraph> graph(b.Build());

    EXPECT_EQ(2, graph->VertexCount());
    EXPECT_EQ(1, graph->EdgeCount());

    for (const Vertex& v : graph->Vertices()) {
        
    }
}