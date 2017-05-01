map<char, int> M = 
{
    {'+', 0}, {'-', 0}, {'*', 1}, {'/', 1}  
};

int firstOperationCharacter(std::string expr) 
{
    if(expr.find_first_of("()") == string::npos)
    {
        int c = expr.find_first_of("*/");
        if(c != string::npos) return c;
        else return expr.find("+-");
    }
    
    stack<char> st;
    string part = "";
    vector<pair<char, pair<int, int>>> parts;
    
    expr.insert(0, 1, '(');
    expr.push_back(')');
    
    for(int i=0; i<expr.length(); i++)
    {
        char c = expr[i];
        
        switch(c)
        {
            case '(':                
                if(part.length() > 0) 
                {
                    int op = part.find_first_of("+*/");
                    parts.push_back({part[op], {i-(part.length()-op), st.size()}});
                    
                    part.clear();
                }
                st.push(c);
                break;
            
            case ')':
                st.pop();
                if(part.length() > 0) 
                {
                    int op = part.find_first_of("+*/");
                    parts.push_back({part[op], {i-(part.length()-op), st.size()}});
                    
                    part.clear();
                }               
                break;  
                
            default:
                part += c;
                break;
        }
    }
    sort(parts.begin(), parts.end(), 
         [=](pair<char, pair<int, int>> a, pair<char, pair<int, int>> b)
         {
            if(a.second.second == b.second.second) 
            {
                return (M[a.first] > M[b.first]);
            }
            return a.second.second > b.second.second;
         });
    for(auto it : parts)
    {
        cout << it.first << " | " << it.second.first-1 << ", " << it.second.second << endl;
    }
    return parts[0].second.first-1;
}
