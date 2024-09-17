class Disjoint{
public:
    vector<int> size, parent;

    Disjoint(int n){
        size.resize(n+1);
        parent.resize(n+1);
        for(int i = 0; i <= n; i++){
            parent[i] = i;
            size[i] = 1;
        }
    }

    int findUparent(int node){
        if(node == parent[node]) return node;
        return parent[node] = findUparent(parent[node]);
    }

    void unionBySize(int u , int v){
        int ulp_v = findUparent(v);
        int ulp_u = findUparent(u);
        if(ulp_v == ulp_u) return ;
        if(size[ulp_v] < size[ulp_u]){
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
        else{
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
    }

};
