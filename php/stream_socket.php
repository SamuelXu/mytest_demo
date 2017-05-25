<?php

$fp = stream_socket_client('tcp://www.baidu.com:80', $errno, $errstr, 3);
//var_dump(stream_socket_get_name($fp, false), stream_socket_get_name($fp, true));

list($remote_ip, $remote_port) = split(":", stream_socket_get_name($fp, true));

var_dump($remote_ip);
