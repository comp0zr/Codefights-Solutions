function htmlTable(table, row, column) 
{
    var t = table.split("<tr>")
    var index = 0;
    t.shift();
   
    if(row >= t.length) return "No such cell";
    
    var line = t[row].split("<td>");
    line.shift();
    
    if(column >= line.length) return "No such cell";
    return line[column].substr(0, line[column].indexOf('<'));
}
