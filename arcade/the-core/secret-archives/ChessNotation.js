function chessNotation(notation) 
{
    var lines = notation.split('/').reverse();
    
    for(var i=0; i<8; i++)
    {
        while(lines[i].search(/[1-8]/) !== -1)
        {
            lines[i] = lines[i].replace(/[1-8]/, new String('x').repeat(parseInt(lines[i].match(/[1-8]/))))
        }
        console.log(lines[i])
    }
    
    var ans = [];

    for(var i=0; i<8; i++)
    {          
        var count = 0;
        var line = "";

        for(var j=0; j<8; j++)
        {
            if(lines[j][i] == 'x')
            {
                count++;
            }
            else 
            {
                if(count > 0) 
                {
                    line += (count).toString();
                    count=0;
                }
                line += lines[j][i];
            }
        }
        if(count > 0) 
        {
            line += (count).toString();
            count=0;
        }
        ans.push(line);        
    }
    return ans.join('/');
}
