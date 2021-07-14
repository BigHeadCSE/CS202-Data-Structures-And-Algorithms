#include<bits/stdc++.h>

using namespace std;

#define ll long long int

stack<ll>st;
int main()
{
    ll n,m;
    cin>>n>>m;

    string  s;
    cin>>s;

    st.push(1);

    ll r= 0, c= 0, num= 1;

    for(int i=0; i< s.size(); i++)
    {
        if(s[i]>='0' && s[i]<='9')
        {
            ll d = s[i]-'0';
            num *= d;
            st.push(num);
        }
        else if(s[i]== '(' )
        {
            continue;
        }
        else if(s[i]== ')' )
        {
            st.pop();
            num= st.top();
        }
        else
        {
            if(s[i]=='S')
            {
                r= (r+num)%n;
            }
            else if(s[i]=='N')
            {
                r -= num;
                if( r<0 ){
                    r %= n;
                    r += n;
                }
            }
            else if(s[i]=='W')
            {
                c -= num;
                if( c<0 ){
                    c %= m;
                    c += m;
                }
            }
            else
            {
                c= (c+num)%m;
            }
        }
    }
    cout<< r <<" "<< c <<endl;

    return 0;
}

