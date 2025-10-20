import heapq

class Graph:
    def __init__(self, graph: dict | None = None):
        # cria um dicionario de dicionarios
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
        # garante que todos os nós (keys e vizinhos) estejam no conjunto de nós
        nodes = set(self.graph.keys())
        for nbrs in self.graph.values():
            nodes.update(nbrs.keys())

        if source not in nodes:
            raise ValueError(f"Source {source!r} não existe no grafo.")

        # inicializa distâncias e predecessor (para reconstruir caminhos)
        distances = {node: float("inf") for node in nodes}
        prev = {node: None for node in nodes}
        distances[source] = 0

        pq = [(0, source)]
        while pq:
            current_dist, current_node = heapq.heappop(pq)

            # descarta entradas antigas na heap
            if current_dist > distances[current_node]:
                continue

            # usa get para evitar KeyError caso current_node não tenha arestas
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
            return None, float("inf")  # alvo inalcançável
        # reconstruir caminho
        path = []
        cur = target
        while cur is not None:
            path.append(cur)
            cur = prev[cur]
        path.reverse()
        return path, distances[target]

def teste1():
    graph1 = {
       "A": {"B": 3, "C": 3},
       "B": {"A": 3, "D": 3.5, "E": 2.8},
       "C": {"A": 3, "E": 2.8, "F": 3.5},
       "D": {"B": 3.5, "E": 3.1, "G": 10},
       "E": {"B": 2.8, "C": 2.8, "D": 3.1, "G": 7},
       "F": {"G": 2.5, "C": 3.5},
       "G": {"F": 2.5, "E": 7, "D": 10},
    }
    G = Graph(graph1) #teste1

    distances, _ = G.shortest_distances("B")
    print("Distâncias mínimas a partir do nó B:")
    for node in sorted(distances):
        d = distances[node]
        print(f"B → {node}: {d:.2f}" if d < float("inf") else f"B → {node}: ∞")

    path, dist = G.shortest_path("B", "F")
    print()
    if path:
        print(f"Caminho mínimo B → F: {' -> '.join(path)} (distância = {dist:.2f})")
    else:
        print("Não há caminho de B até F.")

def teste2():
    print("\n--- INÍCIO DO CASO DE TESTE 2: Armadilha e Nó Isolado ---")
    graph2 = Graph()
    graph2.add_edge("A", "B", 2, undirected = True)
    graph2.add_edge("A", "D", 15, undirected = True)
    graph2.add_edge("B", "C", 3, undirected = True)
    graph2.add_edge("C", "D", 4, undirected = True)
    graph2.graph["F"] = {}

    source = "A"
    target = "D"
    
    distances, _ = graph2.shortest_distances("D")
    print("Distâncias mínimas a partir do nó B:")
    for node in sorted(distances):
        d = distances[node]
        print(f"D → {node}: {d:.2f}" if d < float("inf") else f"D → {node}: ∞")
    
    # Teste 1: Encontrar o caminho mais curto de 'A' para 'D'
    path, dist = graph2.shortest_path(source, target)
    if path and dist < 15:
        print(f"\nCaminho encontrado: {' -> '.join(path)} (distância = {dist:.2f})")
    else:
        print("Resultado: INCORRETO.")

    # Teste 2: Tentar encontrar um caminho para o nó isolado 'F'
    print()
    path_iso, dist_iso = graph2.shortest_path(source, "F")
    print(f"Procurando caminho de {source} para F (nó isolado)")
    if not path_iso:
        print("Caminho não encontrado, como esperado.")
        print("Resultado: CORRETO.")
    else:
        print("Resultado: INCORRETO.")

def main():
    teste1();
    teste2();

if __name__ == "__main__":
    main()