#include<iostream>
#include<stack>
using namespace std;
class solution{
    public:
    bool isvalid(string str){
       stack<char> st;
        for(int i=0;i<str.size();i++){
        if(str[i]=='('||str[i]=='{'||str[i]=='['){
            st.push(str[i]);
        }
        else{
            if(st.size()==0)
            return false;
            if((str[i]==')'&& st.top()=='(' )|| (str[i]=='}'&& st.top()=='{') ||(str[i]==']'&& st.top()=='['))
            st.pop();
            else return false;
        }
       }
       if(st.size()==0)
       return true;
       return false;
    }
};

