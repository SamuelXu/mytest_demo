<?php

function convert_win_to_unix($path)
{
    if ($path[0] == '/' || stripos($path, ":\\") != 1) {
        return $path;
    }
    $path = str_replace(':\\', '/', $path);
    $path = str_replace('\\', '/', $path);
    $path = preg_replace('/\/+/', '/', $path);
    return $path;
}
//$path = realpath($argv[1]);
//$path = str_replace(':\\', '/', $argv[1]);// Replace backslashes with forwardslashes
//$path = preg_replace('/\/+/', '/', $path);// Combine multiple slashes into a single slash

$path = convert_win_to_unix($argv[1]);
echo $path."\n";
