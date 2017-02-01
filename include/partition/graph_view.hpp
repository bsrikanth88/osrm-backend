#ifndef OSRM_PARTITION_GRAPHVIEW_HPP_
#define OSRM_PARTITION_GRAPHVIEW_HPP_

#include "partition/bisection_graph.hpp"
#include "partition/recursive_bisection_state.hpp"

#include <boost/iterator/filter_iterator.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/range/iterator_range.hpp>

#include <cstddef>
#include <cstdint>

namespace osrm
{
namespace partition
{

// Non-owning immutable sub-graph view into a base graph.
// The part of the graph to select is determined by the recursive bisection state.
class GraphView
{
  public:
    using ConstNodeIterator = BisectionGraph::ConstNodeIterator;
    using NodeIterator = BisectionGraph::NodeIterator;
    using NodeT = BisectionGraph::NodeT;
    using EdgeT = BisectionGraph::EdgeT;

    // Construction either for a subrange, or for a full range
    GraphView(const BisectionGraph &graph);
    GraphView(const BisectionGraph &graph,
              const ConstNodeIterator begin,
              const ConstNodeIterator end);

    // construction from a different view, no need to keep the graph around
    GraphView(const GraphView &view, const ConstNodeIterator begin, const ConstNodeIterator end);

    // Number of nodes _in this sub-graph.
    std::size_t NumberOfNodes() const;

    // Iteration over all nodes (direct access into the node)
    ConstNodeIterator Begin() const;
    ConstNodeIterator End() const;

    // Re-Construct the ID of a node from a reference
    NodeID GetID(const NodeT &node) const;

    // Access into single nodes/Edges
    const NodeT &Node(const NodeID nid) const;
    const EdgeT &Edge(const EdgeID eid) const;

    // Access into all Edges
    auto Edges(const NodeID nid) const { return bisection_graph.Edges(*(begin + nid)); }
    auto BeginEdges(const NodeID nid) const { return bisection_graph.BeginEdges(*(begin + nid)); }
    auto EndEdges(const NodeID nid) const { return bisection_graph.EndEdges(*(begin + nid)); }

  private:
    const BisectionGraph &bisection_graph;

    const BisectionGraph::ConstNodeIterator begin;
    const BisectionGraph::ConstNodeIterator end;
};

} // namespace partition
} // namespace osrm

#endif // OSRM_PARTITION_GRAPHVIEW_HPP_