<?php

//declare(ticks = 1);
//
//define("TVAR", 5);
//
//function func()
//{
//    $var = array(1,2,3,4);
//    return $var;
//}
//
//function func2($ret)
//{
//    var_dump(strlen($ret));
//    $ret = $ret . "1";
//    var_dump($ret);
//}

//$a = func();
//
//var_dump($a);
//
//$b = "{$a[0]}_{$a[1]}";
//var_dump($b);
//
//$c = null;
//var_dump(isset($c));
//
//$d = array();
//var_dump( $d == false);

//func2(4);
//
//var_dump(TVAR);
//var_dump(SOCKET_ESHUTDOWN);
//
//$g = array("a"=>"this", "b"=>"is", "c"=>"test");
//if ( key_exists("c", $g) && !empty($g["c"]))
//{
//    var_dump($g["c"]);
//}
//
//$h[51][1] = array("a"=>"this", "b"=>"also", "c"=>"test");
//var_dump($h);
//unset($h[51][1]);
//if (empty($h[51])) {
//    var_dump($h[51]);
//}
//
//$i = 5 . 6;
//var_dump($i);
//var_dump( 0 == False);
//
//$g1 = NULL;
//function gtest()
//{
//    global $g1;
//    var_dump($g1);
//}
//gtest();

//var_dump("0" == false);

//function f1()
//{
//}
//$a=f1();
//var_dump($a);
//

//if(empty($a))
//{
//    echo "aaa\n";
//}

//$a = 12345;
//$b = 12;
//var_dump("{$a}_{$b}");
//
//var_dump( "902" > "1010");
//var_dump(intval(FALSE));

//$a = explode(".", "1.02.003.004");
//var_dump($a);
//

//$a = array(
//    'email_data' => array(
//        'user_name' => 'duang',
//        'email' => 'duang@163.com',
//        'subject' => 'task_name成功',
//        'msg' => 'task_name成功',
//    ),
//    'num' => 1,
//    'email_kind' => 1
//);
//
//$b = array(
//    'email_data' => array(
//        'user_name' => 'duang',
//        'email' => 'duang@163.com',
//        'subject' => 'task_name成功',
//        'msg' => 'task_name成功',
//    ),
//    'task' => array(
//        'task_id' => 1,
//        'task_name' => 'file',
//        'recovery_start_time' => 1234567890
//    ),
//    'num' => 1,
//    'is_db' => 1,
//    'email_kind' => 2
//);
//var_dump(json_encode($a));
//var_dump(json_encode($b));
//

//var_dump( strcasecmp("A", "a") == 0);

$a = array("a", "b");
if(isset($a)) {
    unset($a);
    $a = 123;
}
var_dump($a);

