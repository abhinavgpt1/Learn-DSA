#include <bits/stdc++.h>
using namespace std;

/**
 * Do not expose both unionBySize and unionByRank functions.
 * Keep parent, size, rank private
 * Expose functions like findParent, unionBySize/Rank only. Others mentioned are unneccessary generally.
 * eg. see NumOfProvinces(gfg_medium).cpp
 * 
 */
class DisjointSet
{
    vector<int> rank; // measures the height of tree, ith node being the root
    vector<int> size; // measures the size of tree below it including itself
    vector<int> parent;

public:
    DisjointSet(int n)
    {
        // rank = vector<int>(n, 0);
        // parent = vector<int>(n);

        // better
        rank.resize(n, 0); // 0-based indexing
        size.resize(n, 1); // 0-based indexing
        parent.resize(n);  // 0-based indexing

        // resize(n+1) will work for 1-based indexing problems as well as 0-based
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }
    int findParent(int u)
    {
        if (parent[u] == u)
            return u;
        return parent[u] = findParent(parent[u]); // path compression by assigning parent[u] to ultimate parent, otherwise its complexity is log(N)
    }
    void unionByRank(int u, int v)
    {
        int pu = findParent(u);
        int pv = findParent(v);
        if (pu == pv) // do not anything if u and v belong to same set
            return;
        int rankpu = rank[pu];
        int rankpv = rank[pv];

        if (rankpu < rankpv)
        {
            // pv is at higher level
            // parent[pu] = parent[pv]; // parent[pv] = pv, hence the call to find parent broke (and also that's the defintion of parent)
            parent[pu] = pv;
        }
        else if (rankpv < rankpu)
        {
            // pu is at higher level
            parent[pv] = pu;
        }
        else
        {
            parent[pv] = pu;
            rank[pu]++;
        }
        // rank is not a measurement of number of attachments, so it can only be updated when rank(u) == rank(v)
    }
    void unionBySize(int u, int v)
    {
        int pu = findParent(u);
        int pv = findParent(v);
        if (pu == pv) // do not anything if u and v belong to same set
            return;
        int sizepu = size[pu];
        int sizepv = size[pv];

        if (sizepu < sizepv)
        {
            parent[pu] = pv;
            size[pv] += sizepu;
        }
        else
        {
            parent[pv] = pu;
            size[pu] += sizepv;
        }
        // size of pu/pv is increased everytime, so no need of else-if
    }
    void printParentAndRankForNode()
    {
        for (int i = 0; i < parent.size(); i++)
        {
            cout << "for " << i << ", parent: " << parent[i] << ", rank: " << rank[i] << endl;
        }
    }
    void printParentAndSizeForNode()
    {
        for (int i = 0; i < parent.size(); i++)
        {
            cout << "for " << i << ", parent: " << parent[i] << ", size: " << size[i] << endl;
        }
    }
    void checkSameParent(int u, int v)
    {
        if (this->findParent(u) == this->findParent(v))
            cout << "yes, same parent: " << u << "," << v << endl;
        else
            cout << "no, not same parent: " << u << "," << v << endl;
    }
};
int main()
{
    DisjointSet ds(5);
    ds.unionByRank(1, 2);
    ds.unionByRank(3, 4);
    ds.unionByRank(1, 0);
    ds.checkSameParent(0, 4); // not same
    ds.unionByRank(0, 4);
    ds.checkSameParent(0, 4); // same
    ds.checkSameParent(2,3); // same
    ds.unionByRank(2, 3); // nothing happens here as 1,3 are already in same set
    ds.checkSameParent(2,3); //same
    ds.printParentAndRankForNode();

    DisjointSet ds2(5);
    ds2.unionBySize(1, 2);
    ds2.unionBySize(3, 4);
    ds2.unionBySize(1, 0);
    ds2.checkSameParent(0, 4); // not same
    ds2.unionBySize(0, 4);
    ds2.checkSameParent(0, 4); // same
    ds2.checkSameParent(2, 3); // same
    ds2.unionBySize(2, 3); // nothing happens here as 1,3 are already in same set
    ds2.checkSameParent(2, 3); // same
    ds2.printParentAndSizeForNode();
}
/**
 * Output:
 * -------
 * no, not same parent: 0,4
 * yes, same parent: 0,4
 * yes, same parent: 2,3
 * yes, same parent: 2,3
 * for 0, parent: 1, rank: 0
 * for 1, parent: 1, rank: 2
 * for 2, parent: 1, rank: 0
 * for 3, parent: 1, rank: 1
 * for 4, parent: 1, rank: 0
 * no, not same parent: 0,4
 * yes, same parent: 0,4
 * yes, same parent: 2,3
 * yes, same parent: 2,3
 * for 0, parent: 1, size: 1
 * for 1, parent: 1, size: 5
 * for 2, parent: 1, size: 1
 * for 3, parent: 1, size: 2
 * for 4, parent: 1, size: 1
 *
 */