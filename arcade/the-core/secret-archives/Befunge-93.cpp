stringstream out;
int h, w;

map<int, pair<int, int>> nextDir =
{
    {0, {-1,  0}},
    {1, { 1,  0}},
    {2, { 0, -1}},
    {3, { 0,  1}}
};


int Pop(vector<int> &stack)
{
    if(stack.empty())
    {
        return 0;
    }
    int x = stack.back();
    stack.pop_back();
    return x;
}


std::string befunge93(std::vector<std::string> program) 
{    
    bool quote = false;
    int x=0, y=0, d=3;
    
    vector<int> st;

    for(int i=0; i<program.size(); i++)
    {
        for(int j=0; j<program[i].length()-1; j++)
        {
            if(program[i][j] == '\\' && program[i][j+1] == '\\')
            {
                program[i].replace(j, 2, "~");
            }
            if(program[i][j] == '\\' && program[i][j+1] == '"')
            {
                program[i].replace(j, 2, "\"");
            }
        }
    }
    h = program.size(), w = program[0].length();
    
    for(int i=0; i < 100000 && out.str().size() < 100; i++)
    {
        if(i > 0) 
        {
            y += nextDir[d].first;
            x += nextDir[d].second;
        
            if(y >= h || y < 0) y = (y < 0) ? h-1 : 0;
            if(x >= w || x < 0) x = (x < 0) ? w-1 : 0;
        }
        
        char c = program[y][x];
        
        if(c == '?') continue;
        
        if(quote)
        {
            if(c == '"') quote = false;
            else st.push_back(c);       
            continue;
        }
        
        
        switch(c)
        {
            case '@': return out.str();
            case '#': 
            {
                y += nextDir[d].first;
                x += nextDir[d].second;
                break;            
            }
            case '"': quote = true; break;
                
            
            // Directions            
            case '>': d = 3; break;
            case '<': d = 2; break;
            case '^': d = 0; break;
            case 'v': d = 1; break;
            
               
            // Conditional
            case '_':
            {            
                d = (st.back() == 0) ? 3 : 2;
                Pop(st);
                break;
            }
                
            case '|':
            {            
                d = (st.back() == 0) ? 1 : 0;
                Pop(st);
                break;
            }
                
            // Math
            case '+': 
            case '-': 
            case '*': 
            case '/': 
            case '%': 
            {
                int a = Pop(st), b = Pop(st); 
                st.push_back
                (
                    (c=='+') ? a + b :
                    (c=='-') ? b - a :
                    (c=='*') ? a * b :
                    (c=='/') ? b / a :
                               b % a 
                ); 
                break;
            }
                
            // Output
            case '.':
            {
                int a = Pop(st);
                out << a << ' ';
                break;
            }
            case ',': 
            {                
                int a = Pop(st);
                out << (char)a;
                break;
            }
                                
            // Logical
            case '!': 
            {                     
                int a = Pop(st);
                st.push_back((a == 0) ? 1 : 0);
                break;
            }
            case '`': 
            {                
                int a = Pop(st), b = Pop(st);                    
                st.push_back((b > a) ? 1 : 0);
                break;
            }
             
            // Stack
            case ':': 
            {   
                st.push_back(st.empty() ? 0 : st.back());                 
                break;
            }
                
            case '$': Pop(st); break;
            
            case '~': 
            {
                int a = Pop(st), b = Pop(st);
                st.push_back(a);
                st.push_back(b);
                break;
            }
                
            default:
            {
                if(isdigit(c)) st.push_back(c-'0');
                break;
            }
        }
    }
    return out.str();
}
