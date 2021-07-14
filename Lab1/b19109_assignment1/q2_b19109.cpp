#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

/*
    My roll number is b19109, whose last two digits 09 has only one prime factor = 3.

    Using an Algorithm which is similar to the Binary GCD Algorithm
    It uses the following identities:

	gcd(0, v) = v, because everything divides zero, and v is the largest number that divides v. Similarly, gcd(u, 0) = u.
	gcd(3u, 3v) = 3*gcd(u, v)
	gcd(3u, v) = gcd(u, v); gcd(u, 3v) = gcd(u, v); - if 3 is not a common divisor.
	gcd(u, v) = gcd(|u − v|, min(u, v)), if u and v both dont have 3 as common multiple.

*/

int main(){
    int u,v;
	cout<<"Enter the two numbers:\n";
	cin>>u>>v;

    /* GCD(0,v) == v; GCD(u,0) == u, GCD(0,0) == 0 */
    if (u == 0) {
        cout<<v<<endl;
        return 0;
    }
    if (v == 0) {
        cout<<u<<endl;
        return 0;
    }

    int mult_3 = 1;   /* storing the multipliers of 3 when both x and y are even. */

    int u2= u/3, v2= v/3;
    while ((u2*3)==u && (v2*3)==v) {
        mult_3 *=3;
        u /= 3; u2 /=3;
        v /= 3; v2 /=3;
    }

    while (u2*3 == u)
        u /= 3; u2 /=3;

    // From here on, u is always odd.
    do {
        /* remove all factors of 3 in v -- they are not common */
        while (v2*3 == v){
            v /= 3; v2 /=3;
        }
        /* Now u and v are both odd. Swap if necessary so u <= v,
            then set v = v - u (which is even).*/
        if (u > v) {
            int t = v;
            v = u; u = t; // Swap u and v.
        }

        v -= u; // Here v >= u.
    } while (v != 0);

    /* restore common factors of 2 */
    cout<< u*mult_3 <<endl;

    return 0;
}

