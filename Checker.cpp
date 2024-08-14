#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll solve()
{
    //Write solution for each testcase
    //Adjust return value of solve() accordingly


}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    //finds correct output
    //Write solution here
    ll t = 1;
    cin >> t;
    vector<ll> res;
    for(ll _ = 0; _ < t; _++)
    {   
        res.push_back(solve()); 
    }
    //Change input stream to user program output file
    freopen("output.txt","r",stdin);
    vector<ll> user_res;
    for(ll _ = 0; _ < t; _++)
    {
        int tmp;
        cin >> tmp;
        user_res.push_back(tmp);
    }
    return !(res == user_res);


}
