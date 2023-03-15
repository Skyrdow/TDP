class Node
{
public:
    int izq[4];
    int der[4];
    Node *previo;
    Node(int i[4], int d[4], Node *p);
    ~Node();
};