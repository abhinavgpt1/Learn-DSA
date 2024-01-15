/**
 * Account Merge
 * -------------
 * Given a list of accounts where each element accounts [ i ] is a list of strings, 
 * where the first element account [ i ][ 0 ]  is a name, and the rest of the elements are emails representing emails of the account.
 * Now, we would like to merge these accounts. 
 * Two accounts definitely belong to the same person if there is some common email to both accounts. 
 * Note that even if two accounts have the same name, they may belong to different people as people could have the same name. 
 * A person can have any number of accounts initially, but all of their accounts definitely have the same name.
 * After merging the accounts, return the accounts in the following format: the first element of each account is the name, and the rest of the elements are emails in sorted order.
 * Note: Accounts themselves can be returned in any order.
 * 
 */

class DisjointSet{
    vector<int> size;
    vector<int> parent;
    public:
    DisjointSet(int n){
        size.resize(n, 1);
        parent.resize(n);
        for(int i=0; i<n; i++)
            parent[i] = i;
    }
    int findParent(int u){
        if(parent[u] == u)
            return u;
        return parent[u] = findParent(parent[u]); //path compression
    }
    void unionBySize(int u, int v){
        int pu = findParent(u);
        int pv = findParent(v);
        if(pu == pv) //account[u] and account[v] already belong to same set
            return;
        if(size[pu] < size[pv]){
            parent[pu] = pv;
            size[pv] += size[pu];
        } else {
            parent[pv] = pu;
            size[pu] += size[pv];
        }
    }
};

// Solution 1: Reduces the operations done in sol2 
class Solution{
  public:
    vector<vector<string>> accountsMerge(vector<vector<string>> &accounts) {
        // (WRONG - will require merging, hence use Disjoint set)can be solved by map and linear traversal over data in T(n) = size(unique emails)*N + size(unique accounts) ~ M*N (since #(unique accounts) < #(unique emails), S(n) = size(unique emails) + size(unique accounts)
        // no need to keep accountName in mapping
        DisjointSet ds(accounts.size()); //tracks if accounts[i] is same as account[j]
        map<string, int> emailMap; //S(n) = O(unique M)
        //O(N*M*(log(unique M) + 2c + c)
        for(int i=0; i<accounts.size(); i++){
            string accountName = accounts[i][0];
            for(int j=1; j<accounts[i].size(); j++){
                string email = accounts[i][j];
                if(emailMap.count(email)){
                    assert(accounts[emailMap[email]][0] == accountName); //given in question that it'll be same
                    
                    // union between account in emailMap and accounts[i]
                    int p1 = ds.findParent(emailMap[email]);
                    int p2 = ds.findParent(i);
                    if(p1 == p2)
                        continue; // do nothing if ultimate parent of both emails is same, though immediate parent can be different
                    ds.unionBySize(p1, p2);
                } else {
                    emailMap[email] = i;
                }
            }
        }
        // entries in this shouldn't be made before, as there will be unmerged email mappings
        // O(unique M)
        map<int, vector<string>> acctMap; // S(n) = O(unique N)
        for(auto em: emailMap){
            string email = em.first;
            int parentAccount = ds.findParent(em.second);
            acctMap[parentAccount].push_back(email); // email will be unique
        }
        // O(unique N)
        vector<vector<string>> ans;
        for(auto am: acctMap){
            sort(am.second.begin(), am.second.end());
            am.second.insert(am.second.begin(), accounts[am.first][0]);
            ans.push_back(am.second);
        }
        return ans;
    }
};
// Solution 2: Keeping accountName
class Solution{
  public:
    vector<vector<string>> accountsMerge(vector<vector<string>> &accounts) {
        // we don't have any connectivity between accounts given straightforward as graph or list of edges
        // (WRONG-needs merging hence Disjoint set)can be solved by map and linear traversal over data in T(n) = size(unique emails)*N + size(unique accounts) ~ M*N (since #(unique accounts) < #(unique emails), S(n) = size(unique emails) + size(unique accounts)
        // (2)solving by keeping {acct, <emails>} will be cumbersome i.e. merging emails
        // (3)assuming edges between all accounts with all accounts will take O(NNMlog(<depends on set you make>))
        
        DisjointSet ds(accounts.size()); //tracks if accounts[i] is same as account[j]
        map<string, pair<string, int>> emailMap;
        for(int i=0; i<accounts.size(); i++){
            string accountName = accounts[i][0];
            for(int j=1; j<accounts[i].size(); j++){
                string email = accounts[i][j];
                if(emailMap.count(email)){
                    assert(emailMap[email].first == accountName); //given in question that it'll be same
                    
                    // union between account in emailMap and accounts[i]
                    int p1 = ds.findParent(emailMap[email].second);
                    int p2 = ds.findParent(i);
                    if(p1 == p2)
                        continue; // do nothing is ultimate parent of both emails is same, though immediate parent can be different
                    ds.unionBySize(p1, p2);
                } else {
                    emailMap[email] = {accountName, i};
                }
            }
        }
        // entries in this shouldn't be made before, as it'll create gaps due to unmerged emails
        // since accountName can be same yet different accounts, hence tracking index is imp.
        map<pair<string, int>, vector<string>> acctMap;
        for(auto em: emailMap){
            string email = em.first;
            string accountName = em.second.first;
            int accountIndex = em.second.second;
            int parentAccount = ds.findParent(accountIndex);
            acctMap[{accountName, parentAccount}].push_back(email); // email will be unique
        }
        vector<vector<string>> ans;
        for(auto am: acctMap){
            sort(am.second.begin(), am.second.end());
            am.second.insert(am.second.begin(), am.first.first);
            ans.push_back(am.second);
        }
        return ans;
    }
};