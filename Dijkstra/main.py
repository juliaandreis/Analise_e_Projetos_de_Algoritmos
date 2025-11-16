#Julia Andreis, Kauan Gross e Tobias Klein

import heapq

class Graph:
    def __init__(self, graph: dict | None = None):
        self.graph = graph if graph is not None else {}

    def add_edge(self, node1, node2, weight, undirected: bool = False):
        if node1 not in self.graph:
            self.graph[node1] = {}
        self.graph[node1][node2] = weight
        if undirected:
            if node2 not in self.graph:
                self.graph[node2] = {}
            self.graph[node2][node1] = weight

    def shortest_distances(self, source: str):
        nodes = set(self.graph.keys())
        for nbrs in self.graph.values():
            nodes.update(nbrs.keys())

        if source not in nodes:
            raise ValueError(f"Source {source!r} não existe no grafo.")

        distances = {node: float("inf") for node in nodes}
        prev = {node: None for node in nodes}
        distances[source] = 0

        pq = [(0, source)]
        while pq:
            current_dist, current_node = heapq.heappop(pq)

            if current_dist > distances[current_node]:
                continue

            for neighbor, weight in self.graph.get(current_node, {}).items():
                new_dist = current_dist + weight
                if new_dist < distances[neighbor]:
                    distances[neighbor] = new_dist
                    prev[neighbor] = current_node
                    heapq.heappush(pq, (new_dist, neighbor))

        return distances, prev

    def shortest_path(self, source: str, target: str):
        distances, prev = self.shortest_distances(source)

        if distances.get(target, float("inf")) == float("inf"):
            return [], float("inf")

        path = []
        cur = target
        while cur is not None:
            path.append(cur)
            cur = prev[cur]

        return list(reversed(path)), distances[target]


# ---------------------------------------------------------
#                     TESTE 1
# ---------------------------------------------------------

def teste1():
    print("\n--- TESTE 1: GRAFO MAIOR ---")

    graph1 = {
       "A": {"B": 3, "C": 3},
       "B": {"A": 3, "D": 3.5, "E": 2.8},
       "C": {"A": 3, "E": 2.8, "F": 3.5},
       "D": {"B": 3.5, "E": 3.1, "G": 10},
       "E": {"B": 2.8, "C": 2.8, "D": 3.1, "G": 7},
       "F": {"G": 2.5, "C": 3.5},
       "G": {"F": 2.5, "E": 7, "D": 10},
    }

    G = Graph(graph1)

    distances, _ = G.shortest_distances("B")

    print("Distâncias mínimas a partir do nó B:")
    for node in sorted(distances):
        d = distances[node]
        print(f"B → {node}: {d:.2f}" if d < float("inf") else f"B → {node}: ∞")

    path, dist = G.shortest_path("B", "F")

    print()
    print("Caminho mínimo B → F:")
    if path:
        print(f"{' -> '.join(path)} (distância = {dist:.2f})")
    else:
        print("Nenhum caminho encontrado.")


# ---------------------------------------------------------
#                     TESTE 2
# ---------------------------------------------------------

def teste2():
    print("\n--- TESTE 2: ARMADILHA + NÓ ISOLADO ---")

    graph2 = Graph()
    graph2.add_edge("A", "B", 2, undirected=True)
    graph2.add_edge("A", "D", 15, undirected=True)
    graph2.add_edge("B", "C", 3, undirected=True)
    graph2.add_edge("C", "D", 4, undirected=True)
    graph2.graph["F"] = {}

    source = "A"
    target = "D"

    distances, _ = graph2.shortest_distances(source)

    print("Distâncias mínimas a partir do nó A:")
    for node in sorted(distances):
        d = distances[node]
        print(f"A → {node}: {d:.2f}" if d < float("inf") else f"A → {node}: ∞")

    # Teste do caminho correto
    print("\nTeste do caminho A → D:")
    path, dist = graph2.shortest_path(source, target)
    if path == ["A", "B", "C", "D"] and dist == 9:
        print(f"Caminho encontrado: {' -> '.join(path)} (distância = {dist})")
        print("Resultado: CORRETO.")
    else:
        print(f"Caminho incorreto: {path}, distância = {dist}")
        print("Resultado: INCORRETO.")

    # Teste do nó isolado
    print("\nTeste do nó isolado F:")
    path_iso, _ = graph2.shortest_path(source, "F")
    if path_iso == []:
        print("Caminho não encontrado, como esperado. CORRETO.")
    else:
        print("Encontrou caminho onde não existe. INCORRETO.")


# ---------------------------------------------------------
#                     MAIN
# ---------------------------------------------------------

def main():
    teste1()
    teste2()


if __name__ == "__main__":
    main()
