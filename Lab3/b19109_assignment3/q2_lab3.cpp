#include<deque>
#include<vector>
#include<iostream>

#define ll long long int
using namespace std;

int main() {
    ll n,k;
    cin>>n>>k;

    ll nums[n];
    for(ll i=0; i<n; i++){
        cin>> nums[i];
    }

    deque<ll> dq_max, dq_min;

	for (ll i = 0; i < n; i++) {

		if (!dq_max.empty() && dq_max.front() == i - k) {
			dq_max.pop_front();
		}

		if (!dq_min.empty() && dq_min.front() == i - k) {
			dq_min.pop_front();
		}

		while (!dq_max.empty() && nums[i] > nums[dq_max.back()]) {
			dq_max.pop_back();
		}

		while (!dq_min.empty() && nums[i] < nums[dq_min.back()]) {
			dq_min.pop_back();
		}

		dq_max.push_back(i);
		dq_min.push_back(i);

		if (i >= k - 1) {
			cout << nums[dq_max.front()] - nums[dq_min.front()]<< " ";
		}
	}

	return 0;
}
