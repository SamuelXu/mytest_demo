<?php

$host = $argv[1];
$port = intval($argv[2]);

$socket = stream_socket_server('tcp://'.$host.':'.$port, $errno, $errstr);
if (!$socket)
{
    echo "$errstr ($errno)<br />\n";
}
else
{
    while ($conn = @stream_socket_accept($socket,$nbSecondsIdle))
    {
        $message= fread($conn, 1024);
        echo 'I have received that : '.$message;
        fputs ($conn, "OK\n");
        fclose ($conn);
    }
    fclose($socket);

    while( !feof($conn) )
    {
        $buf = fread($conn, 8192);
        if($buf === false || $buf==='')
        {
            break;
        }
        var_dump(strlen($buf));
    }
}
