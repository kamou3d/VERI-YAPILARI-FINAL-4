#include "logistics.h"

void init_graph(Graph* g) {
    g->num_cities = 0;
    for (int i = 0; i < MAX_CITIES; i++) {
        g->head[i] = NULL;
    }
}

void add_city(Graph* g, const char* name) {
    if (g->num_cities < MAX_CITIES) {
        strcpy(g->city_names[g->num_cities], name);
        g->num_cities++;
    }
}

Node* create_node(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->city_index = v;
    newNode->next = NULL;
    return newNode;
}

void add_edge(Graph* g, int src, int dest) {
    // Çift yönlü bağlantı (Undirected graph)
    Node* newNode = create_node(dest);
    newNode->next = g->head[src];
    g->head[src] = newNode;

    newNode = create_node(src);
    newNode->next = g->head[dest];
    g->head[dest] = newNode;
}

// Graf Gezinme: BFS (Sondaki 6 rakamı çift olduğu için)
void bfs_traversal(Graph* g, int start_index) {
    bool visited[MAX_CITIES] = {false};
    int queue[MAX_CITIES];
    int front = 0, rear = 0;

    visited[start_index] = true;
    queue[rear++] = start_index;

    printf("Gezinme Rotası (BFS): ");

    while (front < rear) {
        int current = queue[front++];
        printf("%s -> ", g->city_names[current]);

        Node* temp = g->head[current];
        while (temp != NULL) {
            int adj_node = temp->city_index;
            if (!visited[adj_node]) {
                visited[adj_node] = true;
                queue[rear++] = adj_node;
            }
            temp = temp->next;
        }
    }
    printf("SON\n");
}
