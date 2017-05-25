<?php

$d = array(
    array(0, "right", 2),
    array(1, "wrong", 3),
    array(2, "wrong", 4),
    array(0, "wrong", 5),
    array(5, "wrong", 7)
);
$b = array(0, "right", 3);
$callback = 
    function ($a) use ($b) {
//    function ($a) {
        return ($a[0] != $b[0] || $a[1] != $b[1]);
    };

$c = array_filter($d, $callback);

var_dump($c);
