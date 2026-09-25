import subprocess
import sys
import re

import matplotlib.pyplot as plt
import networkx as nx


def read_matrix(filename):
    matrix = []

    with open(filename, "r") as file:
        for line in file:
            row = [int(value) for value in line.split()]
            matrix.append(row)

    return matrix


def run_tsp(input_file):
    result = subprocess.run(
        ["./output/main", input_file],
        capture_output=True,
        text=True
    )

    return result.stdout


def extract_data(output):
    cost_match = re.search(
        r"Nearest Neighbor \+ 2-opt cost:\s*(\d+)",
        output
    )

    gap_match = re.search(
        r"Gap:\s*([\d.]+)%",
        output
    )

    route_match = re.search(
        r"Route:\s*([0-9\s\->]+)",
        output
    )

    if not cost_match or not route_match:
        print("Could not read program output.")
        sys.exit(1)

    cost = int(cost_match.group(1))
    gap = float(gap_match.group(1)) if gap_match else None

    route = [
        int(vertex)
        for vertex in re.findall(r"\d+", route_match.group(1))
    ]

    # Remove repeated starting vertex
    if route[0] == route[-1]:
        route.pop()

    return cost, gap, route


def create_graph(matrix):
    graph = nx.Graph()

    n = len(matrix)

    # Vertices
    for vertex in range(n):
        graph.add_node(vertex)

    # All possible edges
    for i in range(n):
        for j in range(i + 1, n):
            graph.add_edge(
                i,
                j,
                weight=matrix[i][j]
            )

    return graph


def draw_graph(graph, route, cost, gap, filename):
    positions = nx.circular_layout(graph)

    plt.figure(figsize=(12, 10))

    # ----------------------------------------
    # Draw ALL edges
    # ----------------------------------------

    nx.draw_networkx_edges(
        graph,
        positions,
        alpha=0.10,
        width=0.5
    )

    # ----------------------------------------
    # Build best route
    # ----------------------------------------

    route_edges = []

    for i in range(len(route) - 1):
        route_edges.append(
            (route[i], route[i + 1])
        )

    # Close cycle
    route_edges.append(
        (route[-1], route[0])
    )

    # ----------------------------------------
    # Highlight best route
    # ----------------------------------------

    nx.draw_networkx_edges(
        graph,
        positions,
        edgelist=route_edges,
        width=3
    )

    # ----------------------------------------
    # Draw vertices
    # ----------------------------------------

    nx.draw_networkx_nodes(
        graph,
        positions,
        node_size=700
    )

    nx.draw_networkx_labels(
        graph,
        positions,
        font_size=9
    )

    # ----------------------------------------
    # Information
    # ----------------------------------------

    instance = filename.split("/")[-1]

    title = (
        f"TSP - {instance}\n"
        f"Nearest Neighbor + 2-opt\n"
        f"Cost: {cost}"
    )

    if gap is not None:
        title += f" | Gap: {gap:.2f}%"

    plt.title(title)

    plt.axis("off")
    plt.tight_layout()

    plt.show()


def main():
    if len(sys.argv) != 2:
        print(
            f"Usage: python {sys.argv[0]} <input_file>"
        )
        sys.exit(1)

    input_file = sys.argv[1]

    print(f"Loading {input_file}...")

    # Read complete graph
    matrix = read_matrix(input_file)

    # Execute C implementation
    output = run_tsp(input_file)

    print(output)

    # Extract heuristic solution
    cost, gap, route = extract_data(output)

    # Create complete graph
    graph = create_graph(matrix)

    # Draw
    draw_graph(
        graph,
        route,
        cost,
        gap,
        input_file
    )


if __name__ == "__main__":
    main()
