from sys import argv
import numpy as np
import networkx as nx
# see : https://networkx.github.io/
import community
# if error : see : https://python-louvain.readthedocs.io/en/latest/

import matplotlib.pyplot as plt
np.random.seed(3214)


def readGraphFromText(textFile, comments=4):
    """Reads a graph from a text file comments is the number of lines at the
    head of the file to skip
    """
    f = open(textFile, "r")
    G = nx.Graph()
    i = 0
    while i < comments:
        f.readline()
        i += 1
    for line in f:
        s_t = line.split("\t")
        s = int(s_t[0])
        t = int(s_t[1])
        G.add_edge(s, t)
    f.close()
    G = nx.relabel.convert_node_labels_to_integers(G)
    return G

# ex1


def generateRandomGraph(p, q, n_Nodes=400):
    """Generates a random graphs following the rules indicated in ex1 tp4
    """
#     f = open("graph", 'w')
    graph = nx.Graph()
    for i in range(n_Nodes):
        for j in range(i-1):
            if i//100 == j//100:  # same cluster
                if np.random.rand() <= p:
                    #                     print(f"{i} {j}",file=f)
                    graph.add_edge(i, j)
            else:
                if np.random.rand() <= q:
                    #                     print(f"{i} {j}",file=f)
                    graph.add_edge(i, j)
#     f.close()
    return graph

# ex2


def FYshuffle(ary):
    """Fisher Yates shuffle"""
    a = len(ary)
    b = a-1
    for d in range(b, 0, -1):
        e = np.random.randint(0, d)
        if e == d:
            continue
        ary[d], ary[e] = ary[e], ary[d]
    return ary


def adjacencyDict(G):
    """Takes a networkx graph and returns its adjacency dictionary"""
    adj = {}
    for n, dict in G.adjacency():
        adj[n] = list(dict.keys())

    return adj


def LabelPropagation(graph):
    """The Label propagation algorithm"""
    nodes = list(graph.nodes())
    n = len(nodes)
    adjDict = adjacencyDict(graph)
    labels = {i: i for i in graph.nodes}
    frequencies = np.ones(n)
    dontStop = True
    while dontStop:
        nodes = FYshuffle(nodes)
        dontStop = False
        for node in nodes:
            nodeAdj = adjDict[node]
            if len(nodeAdj) != 0:
                popular_neighbor = nodeAdj[np.argmax(frequencies[nodeAdj])]
                if labels[node] != labels[popular_neighbor]:
                    dontStop = True
                    labels[node] = labels[popular_neighbor]
                    frequencies[node] = max(frequencies[node]-1, 0)
                    frequencies[popular_neighbor] += 1
            else:
                frequencies[node] = n+1

    return labels


def partitionFromLabels(labels):
    """Computes communities as list of lists from a dictionary of labels"""
    outdict = {value: [] for value in set(labels.values())}
    for node in labels.keys():
        outdict[labels[node]].append(node)
    return list(outdict.values())

# ex3


def minimalDegree(G, mind=1):
    """My algorithm :
    G : networkx graph
    mind : minimum degree

    For each node it sets its labels to the label of the node that has a lowest
    degree among its neighbours with degree at least mind.
    when there is no nodes with degree greater than mind, it considers the node
    with the mawximal degree.
    """
    nodes = list(G.nodes())
    adjDict = adjacencyDict(G)
    labels = {i: i for i in G.nodes}
    degrees = {i: len(adjDict[i]) for i in G.nodes}
    dontStop = True
    while dontStop:
        nodes = FYshuffle(nodes)
        dontStop = False
        for node in nodes:
            nodeAdj = adjDict[node]
            kdegrees = np.array([degrees[k]
                                 for k in nodeAdj if degrees[k] >= mind])
            if len(kdegrees) > 0:
                specialNode = nodeAdj[np.argmin(kdegrees)]
            else:
                k_degrees = np.array([degrees[k]
                                      for k in nodeAdj if degrees[k] < mind])
                if len(k_degrees) > 0:
                    specialNode = nodeAdj[np.argmax(k_degrees)]
                else:
                    continue
            if labels[node] != labels[specialNode]:
                dontStop = True
                labels[node] = labels[specialNode]

    return labels

# ex4


def Louvain(G):
    """The Louvain algorithm using the package community compatible with
    networkx.
    For more details see :
    https://python-louvain.readthedocs.io/en/latest/
    """
    return community.best_partition(G)


for p, q in ((0.9, 0.001), (0.8, 0.01), (0.8, 0.2)):
    graph = generateRandomGraph(p, q)
    plt.figure()
    nx.draw(graph)
    plt.savefig(argv[1] + "p-q.pdf")

labels = LabelPropagation(graph)
colors = ["r", "b", "Purple", "yellow", "g", "Cyan", "grey"]

# Drawing
plt.figure(figsize=(10, 6))
G = graph
size = float(len(set(labels.values())))
pos = nx.spring_layout(G)
count = 0
for com in set(labels.values()):
    count = count + 1
    list_nodes = [nodes for nodes in labels.keys()
                  if labels[nodes] == com]
    nx.draw_networkx_nodes(G, pos, list_nodes, node_size=20,
                           node_color=colors[count])

nx.draw_networkx_edges(G, pos, alpha=0.2)
plt.savefig(argv[1] + "label_propagation.pdf")

labels2 = minimalDegree(graph)
plt.figure(figsize=(10, 6))
G = graph
size = float(len(set(labels2.values())))
pos = nx.spring_layout(G)
count = 0
for com in set(labels2.values()):
    count = count + 1
    list_nodes = [nodes for nodes in labels2.keys()
                  if labels2[nodes] == com]
    nx.draw_networkx_nodes(G, pos, list_nodes, node_size=20,
                           node_color=colors[count])

nx.draw_networkx_edges(G, pos, alpha=0.2)
plt.savefig(argv[1] + "minimal_degree.pdf")

partition = Louvain(G)

plt.figure(figsize=(10, 6))
size = float(len(set(partition.values())))
pos = nx.spring_layout(G)
count = 0
for com in set(partition.values()):
    count = count + 1
    list_nodes = [nodes for nodes in partition.keys()
                  if partition[nodes] == com]
    nx.draw_networkx_nodes(G, pos, list_nodes, node_size=20,
                           node_color=colors[count])

nx.draw_networkx_edges(G, pos, alpha=0.2)
plt.savefig(argv[1] + "louvain.pdf")
