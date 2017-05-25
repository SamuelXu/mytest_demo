<?php

/*
function logger($filename) {
    $filehandle = fopen($filename, 'a');
    while ( true) {
        fwrite($filehandle, yield . "\n");
    }
}

$logger = logger(__DIR__ . '/log');
//var_dump($logger);
$logger->send('Foo');
$logger->send('Bar');
 */

function gen() {
    $ret = (yield 'yield1');
    var_dump($ret);
    $ret = (yield 'yield2');
    var_dump($ret);
}

$gen = gen();
var_dump($gen->current());
var_dump($gen->send('ret1'));
var_dump($gen->send('ret2'));
