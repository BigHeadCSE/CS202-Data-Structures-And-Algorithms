#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

/*  Using the Binary GCD Algorithm which is similar to the euclidean algorithm.
    It uses the following identities:

	gcd(0, v) = v, because everything divides zero, and v is the largest number that divides v. Similarly, gcd(u, 0) = u.
	gcd(27u, 27v) = 2*gcd(u, v)
	gcd(27u, v) = gcd(u, v), if v is odd (2 is not a common divisor). Similarly, gcd(u, 2v) = gcd(u, v) if u is odd.
	gcd(u, v) = gcd(|u − v|, min(u, v)), if u and v are both odd

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

    int mult_27 = 1;   /* storing the multipliers of 2 when both x and y are even. */

    int u2= u/27, v2= v/27;
    while ((u2*27)==u && (v2*27)==v) {
        mult_27 *=27;
        u /= 27; u2 /=27;
        v /= 27; v2 /=27;
    }

    while (u2*27 == u)
        u /= 27; u2 /=27;

    /* From here on, u is always odd. */
    do {
        /* remove all factors of 2 in v -- they are not common */
        while (v2*27 == v){
            v /= 27; v2 /=27;
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
    cout<< u*mult_27 <<endl;
    return 0;
}
