#include<bits/stdc++.h>
#include<limits>
using namespace std;

class Segment{
public:
	vector<int> seg;
	Segment(int n) {
		seg.resize(4 * n + 1);
	}
public:
	void build(int idx, int low, int high, int arr[]){
		if(low == high) {
			seg[idx] = arr[low];
			return ;
		}

		int mid = (high + low) / 2;

		build(2 * idx + 1, low, mid, arr);
		build(2 * idx + 2, mid + 1, high, arr);

		seg[idx] = min(seg[2 * idx + 1], seg[2 * idx + 2]);
	}

	void update(int ind, int low, int high, int val, int i) {
	        if(low == high) {
	            seg[ind] = val;
	            return ;
	        }
	
	        int mid = (low + high) >> 1;
	        if(i <= mid) update(2 * ind + 1, low, mid, val, i);
	        else update(2 * ind + 2, mid + 1, high, val, i);
	
	        seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
    	}
    
	int query(int ind, int low, int high, int l , int r){
		// complete overlap 
		// the low and high will be inside l and R
		// (L low high R)

		if(low >= l && high <= r){
			return seg[ind];
		}

		// no overlap
		// l r low high || low high l r
		if(r < low || high < l ){
			return INT_MAX;
		}

		int mid = (low + high) / 2;
		int left = query(2 * ind + 1, low, mid, l, r);
		int right = query(2 * ind + 2, mid + 1, high, l, r);

		return min(left , right);
	}
};


int main(){
	int n1;
	cin>>n1;

	int arr1[n1];

	for(int i = 0 ; i < n1; i++) cin>>arr1[i];
	Segment seg1(n1);
	
	int n2;
	cin>>n2;
	int arr2[n2];
	for(int i = 0 ; i < n2; i++) cin>>arr2[i];
	Segment seg2(n2);

	seg1.build(0, 0, n1 - 1, arr1);
	seg2.build(0, 0, n2 - 1, arr2);
	// for(int i = 0; i < 4*n ; i++) cout<<seg[i]<<" ";
	int q;
	cin>>q;
	while(q--){
		int type;
		cin>> type;
		if(type == 2){
			int arrno;
			cin>>arrno;

			int val;
			int idx;
			cin>>val>>idx;
			if(arrno == 1){
				seg1.update(0, 0, n1 - 1, val,idx);
				arr1[idx] = val;
				// cout<<seg1.seg[idx]<<"test";
			}
			else{
				seg2.update(0, 0, n2 - 1, val, idx);
				arr2[idx] = val;
				// cout<<seg2.seg[idx]<<"check";
			}
			
		}
		if(type == 1){
			int l1, r1, l2, r2;
			cin>>l1>>r1>>l2>>r2;
			int min1 = seg1.query(0, 0, n1 - 1, l1 , r1);
			int min2 = seg2.query(0, 0, n2 - 1, l2 , r2);
			cout<< min(min1, min2)<<"   ";
		}

	}
	return 0;

	
}
