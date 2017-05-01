var x_a, x_b, y_a, y_b;
var index_a = -1, index_b = -1;
var h,w;

function Reformat(line, index)
{
    var begin = (line[0]=='|') 
              ? line.split('|').slice(0, x_a+1).join('|') 
              : line.split('+').slice(0, x_a+1).join('+');
    
    var line_a, line_b;
        
    if(line[0] == '|')
    {
        line = line.split('|').slice(1);
        line_a = line.slice(x_a, x_b + 1).join(' ');
        line_b = line.slice(x_b+1).join('|')
        line = '|' + line_a + '|' + line_b;        
    }
    else
    {
        line = line.split('+').slice(1);
        
        if(index === 0 || index === h)
        {
            line_a = line.slice(x_a, x_b + 1).join('-');
            line_b = line.slice(x_b+1).join('+');
            line = '+' + line_a + '+' + line_b;
        }
        else
        {           
            line_a = line.slice(x_a, x_b + 1).join(' ');       
            line_a = " ".repeat(line_a.length);
            line_b = line.slice(x_b+1).join('+');
                        
            if(x_a === 0) line = '|' + line_a + '+' + line_b;
            else line = '+' + line_a + '+' + line_b;            
        }
    }    
    line = (begin + line).split('');    
    return line.join('');
}

function cellsJoining(table, coords) 
{
    h = table.length-1;
    w = table[0].length-1;
    x_a = coords[0][1],
    x_b = coords[1][1],
    y_a = coords[1][0],
    y_b = coords[0][0];
    index_a = -1, index_b = -1;
    
    var y_index = 0, x_index = 0;
    var lines = [];
    
    for(var i=0; i<table.length; i++)
    {
        if(y_index >= y_a && y_index <= y_b) 
        {                        
            if(index_a == -1) index_a = i;
            lines.push(table[i]);
        }        
        if(table[i][0] == '+' && i > 0) y_index++;
        if(y_index > y_b)
        {
            index_b = i;
            break;
        }
    }
    var y = index_a;
    
    for(var i=0; i<lines.length; i++)
    {        
        if(i == lines.length-1 && y !== h) continue;
        lines[i] = Reformat(lines[i], y);
                
        var p_count = table[y].split('').filter((x) => x=='+').length;
        
        if(x_b == p_count-2 && y > index_a && y < index_b)
        {
            lines[i] = lines[i].split('');
            lines[i][lines[i].length-1] = '|';
            lines[i] = lines[i].join('')
        }        
        table[y] = lines[i];
        y++;
    }
    return table;
}
