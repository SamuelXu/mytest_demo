<?php
#setlocale(LC_CTYPE, "zh_CN.UTF-8");
#setlocale(LC_CTYPE, "C");

$path = iconv("UTF-8", "GB2312", "*aa\'article排序");
echo $path . " " . addcslashes($path, " \t\n*.|^$(){}~\'\"\\?") . "\n";
$p = addcslashes($path, " \t\n*.|^$(){}~\'\"\\");
exec('mkdir -p ' . $p);
file_put_contents($path . "/aa", "aaaaa");

