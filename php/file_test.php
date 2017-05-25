<?php

//$str = file_get_contents($argv[1]);
//
//var_dump($str == False);

//mkdir("./aa/bb/cc", 0755, true);
//$p = preg_replace('#/+#','/',"////aa/bbd///s//d");
//var_dump($p);

//$a = file_get_contents("./aa", false, NULL, 0, 5);
//var_dump($a);

//$path_array = explode("/", "/aa/bb/cc/dd/false/null/0/''");
//$real_path = array_filter($path_array, "strlen");
//var_export($real_path);
//list($name1) = array_slice($real_path, -1, 1);
//var_dump($name1);
//var_dump(dirname("//aa/bb/cc/dd/"));

$a = 2;
$b = 1;
file_put_contents("./" . $a . "_" . $b, "aaa");
