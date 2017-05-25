<?php

$filename = $argv[1];

$data = parse_ini_file($filename);
$data["aa"] = 1;
var_dump($data);

var_dump($data["aa"]);
