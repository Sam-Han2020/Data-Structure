class Solution
{
public:
    bool isValid(string s)
    {
        int k = 0;
        char stack[10000];
        int pos = 0;
        while (pos < s.size())
        {
            if (k >= 1)
            {
                char top = stack[k - 1];
                switch (s[pos])
                {
                case ')':
                    if (top == '(')
                        --k;
                    else
                        return false;
                    break;
                case ']':
                    if (top == '[')
                        --k;
                    else
                        return false;
                    break;
                case '}':
                    if (top == '{')
                        --k;
                    else
                        return false;
                    break;
                default:
                    stack[k++] = s[pos];
                    break;
                }
            }
            else
            {
                stack[k++] = s[pos];
            }
            ++pos;
        }
        if (k == 0)
            return true;
        else
            return false;
    }
};

// class Solution {
// public:
//     bool isValid(string s) {
//         stack<int> st;
//         for (int i = 0; i < s.size(); i++) {
//         if (s[i] == '(' || s[i] == '[' || s[i] == '{') st.push(i);
//         else {
//             if (st.empty()) return false;
//             if (s[i] == ')' && s[st.top()] != '(') return false;
//             if (s[i] == '}' && s[st.top()] != '{') return false;
//             if (s[i] == ']' && s[st.top()] != '[') return false;
//             st.pop();
//         }
//         }
//         return st.empty();
//     }
// };